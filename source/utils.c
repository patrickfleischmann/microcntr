/*
 * utils.c
 *
 *  Created on: 12.09.2023
 *      Author: patri
 */
/* notes
Temperature sensor:
define ADC_CHANNEL_SENSOR      16 //< @brief Internal temperature sensor.
                                   //      @note Available onADC1 only.

The TSVREFE bit must be set to enable the conversion of both internal channels: the
ADC1_IN18 or ADC1_IN16 (temperature sensor) and the ADC1_IN17 (VREFINT).

The temperature sensor is internally connected to ADC1_IN18 and ADC1_IN16
channels which is shared with VBAT. Only one conversion, temperature sensor or
VBAT, must be selected at a time. When the temperature sensor and VBAT conversion
are set simultaneously, only the VBAT conversion is performed.
The internal reference voltage VREFINT is connected to ADC1_IN17.

3. Select ADC1_IN18 input channel.
4. Select a sampling time greater than the minimum sampling time specified in the
datasheet.
5.Set the TSVREFE bit in the ADC_CCR register to wake up the temperature sensor
from power down mode
6. Start the ADC conversion by setting the SWSTART bit (or by external trigger)
7. Read the resulting VSENSE data in the ADC data register
8. Calculate the temperature using the following formula:
Temperature (in °C) = {(VSENSE – V25) / Avg_Slope} + 25


Slope=2.5mV/°, V_25°=0.76V, tstart_max 10us, tsamp_min=10us (1° acc.)
TS_CAL1
TS ADC raw data acquired at temperature of 30 °C, VDDA= 3.3 V
0x1FFF 7A2C - 0x1FFF 7A2D
TS_CAL2
TS ADC raw data acquired at temperature of 110 °C, VDDA= 3.3 V
0x1FFF 7A2E - 0x1FFF 7A2F


The VBATE bit in the ADC_CCR register is used to switch to the battery voltage. As the
VBAT voltage could be higher than VDDA, to ensure the correct operation of the ADC, the
VBAT pin is internally connected to a bridge divider.
When the VBATE is set, the bridge is automatically enabled to connect:
•
VBAT/4 to the ADC1_IN18 and ADC1_IN16 input channels
Note:
The VBAT and temperature sensor are connected to the same ADC internal channels
(ADC1_IN18 and ADC1_IN16). Only one conversion, either temperature sensor or VBAT,
must be selected at a time. When both conversion are enabled simultaneously, only the
VBAT conversion is performed.

#define ADC_CHANNEL_VREFINT     17  //< @brief Internal reference.
                                     //    @note Available onADC1 only.
#define ADC_CHANNEL_VBAT        18  // @brief VBAT.
                                    //     @note Available onADC1 only.

VREFINT = 1.21V nom
Internal reference voltage

Q Ratio on VBAT measurement 4

  void adcSTM32EnableTSVREFE(void);
  void adcSTM32DisableTSVREFE(void);
  void adcSTM32EnableVBATE(void);
  void adcSTM32DisableVBATE(void);
  */

#include "utils.h"
#include "main.h"

#define ADC_BINS 4096
#define ADC_V_MAX 3.3

extern BaseSequentialStream* bsp2;

void dac_init(void);


static const DACConfig dac_config = {
  .init         = DAC_TEMP_MIN,
  .datamode     = DAC_DHRM_12BIT_RIGHT,
  .cr           = 0
};

void dac_init(void){
  palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
  dacStart(&DACD1, &dac_config);
  //test dacPutChannelX(&DACD1, 0, DAC_TEMP_1);
}

void heater_setTempDegC(float t){
  float v = (1.567 - t*0.0083)*2; //LMT85: 0°C 1.567V, -8.3mV/deg 0-100°C. div2 on board
  dacPutChannelX(&DACD1, 0, v*ADC_BINS/ADC_V_MAX);
}

void heater_init(void){

  dac_init();
  heater_setTempDegC(0.0);
  chThdSleepMilliseconds(100); //wait for opamp input to settle
  //dac value MUST be set to low temperature before heater is enabled
  //To ensure soft start and no current limit overshoot
  palSetPad(GPIOA, GPIOA_heater_enable);
}

void heater_disable(void){
  palClearPad(GPIOA, GPIOA_heater_enable);
}

void piezo_toggle(void){
  palTogglePad(GPIOC, GPIOC_PIEZO_A);
  palTogglePad(GPIOC, GPIOC_PIEZO_B);
}


float lmt85_volt_to_temp_deg_c(float v){
  return (v-1.567)*-120.48; //LMT85: 0°C 1.567V, -8.3mV/deg 0-100°C. div2 on board
}


#define TEMPSENSOR_CAL1_ADDR     ((uint16_t*) (0x1FFF7A2C)) //30°
#define TEMPSENSOR_CAL2_ADDR     ((uint16_t*) (0x1FFF7A2E)) //110°


/*
 * ADC conversion group.
 * Mode:        Linear buffer, 10 samples of 1 channel, SW triggered.
 * Channels:    temp sensor.
 */
#define ADC_TEMP_INT_NUM_CH   1
#define ADC_TEMP_INT_N 10
static adcsample_t adc_buf_temp_int[ADC_TEMP_INT_NUM_CH * ADC_TEMP_INT_N];

static const ADCConversionGroup adc_conv_grp_temp_int = {
  FALSE,                            /*NOT CIRCULAR*/
  ADC_TEMP_INT_NUM_CH,                        /*NUMB OF CH*/
  NULL,                             /*NO ADC CALLBACK*/
  NULL,                             /*NO ADC ERROR CALLBACK*/
  0,                                /* CR1 */
  ADC_CR2_SWSTART,                  /* CR2 soft trigger*/
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144), /* SMPR1 144cycles*/
  0,                                /* SMPR2 */
  0,                                /* HTR */
  0,                                /* LTR */
  ADC_SQR1_NUM_CH(ADC_TEMP_INT_NUM_CH),       /* SQR1 */
  0,                                /* SQR2 */
  ADC_SQR3_SQ1_N (ADC_CHANNEL_SENSOR)/* SQR3 */
};

float adc_get_temp_internal(void){

  adcStart(&ADCD1, NULL);
  adcSTM32EnableTSVREFE();
  adcConvert(&ADCD1, &adc_conv_grp_temp_int, adc_buf_temp_int, ADC_TEMP_INT_N); //dumy for config
  chThdSleepMilliseconds(1); //wait for temp sens startup

  adcConvert(&ADCD1, &adc_conv_grp_temp_int, adc_buf_temp_int, ADC_TEMP_INT_N);
  adcSTM32DisableTSVREFE();

  uint32_t mean = 0;
  for(uint16_t n=0; n<ADC_TEMP_INT_N; ++n){
    //chprintf(bsp2, "sample %d = %d\n", i, adc_buf_temp_int[i]);
    mean += adc_buf_temp_int[n];
  }

  float t = (float)mean/(float)ADC_TEMP_INT_N;
  //chprintf(bsp2,"mean = %f\n", t);

  float cal30 = *TEMPSENSOR_CAL1_ADDR;
  float cal110 = *TEMPSENSOR_CAL2_ADDR;
  //chprintf(bsp2,"cal30 = %f, cal110 = %f\n", cal30, cal110);


  float slope = (cal110-cal30)/80.0;
  //chprintf(bsp2,"slope = %f [counts], %f [mv/deg]\n", slope, slope*3300/ADC_BINS);

  float temp = (t - cal30) / slope + 30.0;
  //chprintf(bsp2,"temp = %f\n", temp);

  //TODO calibrate ADC full scale with vrefint
  //VREFIN_CAL, Raw data acquired at temperature of, 30 °C VDDA = 3.3 V, 0x1FFF 7A2A - 0x1FFF 7A2B
  return temp;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 10 samples of 1 channel, SW triggered.
 * Channels:    temp sensor.
 */
#define ADC_TEMP_HEAT_NUM_CH   1
#define ADC_TEMP_HEAT_N 100
static adcsample_t adc_buf_temp_heat[ADC_TEMP_HEAT_NUM_CH * ADC_TEMP_HEAT_N];

static const ADCConversionGroup adc_conv_grp_temp_heat = {
  FALSE,                            /*NOT CIRCULAR*/
  ADC_TEMP_HEAT_NUM_CH,                        /*NUMB OF CH*/
  NULL,                             /*NO ADC CALLBACK*/
  NULL,                             /*NO ADC ERROR CALLBACK*/
  0,                                /* CR1 */
  ADC_CR2_SWSTART,                  /* CR2 soft trigger*/
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144), /* SMPR1 144cycles*/
  0,                                /* SMPR2 */
  0,                                /* HTR */
  0,                                /* LTR */
  ADC_SQR1_NUM_CH(ADC_TEMP_HEAT_NUM_CH),       /* SQR1 */
  0,                                /* SQR2 */
  ADC_SQR3_SQ1_N (ADC_CHANNEL_IN12)/* SQR3 */
};

float adc_get_temp_heater(void){

  adcStart(&ADCD1, NULL);
  adcConvert(&ADCD1, &adc_conv_grp_temp_heat, adc_buf_temp_heat, ADC_TEMP_HEAT_N); //dumy for config

  adcConvert(&ADCD1, &adc_conv_grp_temp_heat, adc_buf_temp_heat, ADC_TEMP_HEAT_N);

  uint32_t mean = 0;
  for(uint16_t n=0; n<ADC_TEMP_HEAT_N; ++n){
    mean += adc_buf_temp_heat[n];
  }
  float v = (((float)mean) * ADC_V_MAX / ADC_BINS) / ADC_TEMP_HEAT_N;

  //TODO calibrate ADC full scale with vrefint
  //VREFIN_CAL, Raw data acquired at temperature of, 30 °C VDDA = 3.3 V, 0x1FFF 7A2A - 0x1FFF 7A2B
  return lmt85_volt_to_temp_deg_c(v);
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 10 samples of 1 channel, SW triggered.
 * Channels:    temp sensor.
 */
#define ADC_CURRENT_NUM_CH   1
#define ADC_CURRENT_N 10
static adcsample_t adc_buf_current[ADC_CURRENT_NUM_CH * ADC_CURRENT_N];

static const ADCConversionGroup adc_conv_grp_current = {
  FALSE,                            /*NOT CIRCULAR*/
  ADC_CURRENT_NUM_CH,                        /*NUMB OF CH*/
  NULL,                             /*NO ADC CALLBACK*/
  NULL,                             /*NO ADC ERROR CALLBACK*/
  0,                                /* CR1 */
  ADC_CR2_SWSTART,                  /* CR2 soft trigger*/
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144), /* SMPR1 144cycles*/
  0,                                /* SMPR2 */
  0,                                /* HTR */
  0,                                /* LTR */
  ADC_SQR1_NUM_CH(ADC_CURRENT_NUM_CH),       /* SQR1 */
  0,                                /* SQR2 */
  ADC_SQR3_SQ1_N (ADC_CHANNEL_IN7)/* SQR3 */
};

float adc_get_current(void){

  adcStart(&ADCD1, NULL);
  adcConvert(&ADCD1, &adc_conv_grp_current, adc_buf_current, ADC_CURRENT_N); //dumy for config

  adcConvert(&ADCD1, &adc_conv_grp_current, adc_buf_current, ADC_CURRENT_N);

  uint32_t mean = 0;
  for(uint16_t n=0; n<ADC_CURRENT_N; ++n){
    mean += adc_buf_current[n];
  }

  float v = (float)mean/(float)ADC_CURRENT_N;
  v = v*ADC_V_MAX/ADC_BINS;

  //TODO calibrate ADC full scale with vrefint
  //VREFIN_CAL, Raw data acquired at temperature of, 30 °C VDDA = 3.3 V, 0x1FFF 7A2A - 0x1FFF 7A2B
  return v;
}

//https://excamera.com/sphinx/article-xorshift.html
uint32_t rand32(void)
{
  static uint32_t rseed = 2804628253;  // 100% random seed value
  rseed ^= rseed << 13;
  rseed ^= rseed >> 17;
  rseed ^= rseed << 5;
  return rseed;
}

/*
float randf(){
    return rand32()/(float)4294967295.0;
}
*/




















