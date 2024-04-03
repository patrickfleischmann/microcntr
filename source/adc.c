/*
 * adc.c
 *
 *  Created on: 01.04.2024
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


Chibios driver does not support injected channels conversion!
Disabled Chibios ADC driver (HAL_USE_ADC   FALSE)
*/
#include "main.h"

float lmt85_volt_to_temp_deg_c(float v);

uint32_t adc_TAC_end_cb_counter;
uint32_t adc_TAC_error_cb_counter;


#define TEMPSENSOR_CAL1_ADDR     ((uint16_t*) (0x1FFF7A2C)) //30°
#define TEMPSENSOR_CAL2_ADDR     ((uint16_t*) (0x1FFF7A2E)) //110°


/*
 * ADC conversion group.
 * Mode:        Linear buffer, 10 samples of 1 channel, SW triggered.
 * Channels:    temp sensor.
 */

/*
#define ADC_TEMP_INT_NUM_CH   1
#define ADC_TEMP_INT_N 10
static adcsample_t adc_buf_temp_int[ADC_TEMP_INT_NUM_CH * ADC_TEMP_INT_N];

static const ADCConversionGroup adc_conv_grp_temp_int = {
  .circular =       FALSE,
  .num_channels =   ADC_TEMP_INT_NUM_CH,
  .end_cb =         NULL,
  .error_cb =       NULL,
  .cr1 =            0,
  .cr2 =            ADC_CR2_SWSTART,
  .smpr1 =          ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144),
  .smpr2 =          0,
  .htr =            0,
  .ltr =            0,
  .sqr1 =           ADC_SQR1_NUM_CH(ADC_TEMP_INT_NUM_CH),
  .sqr2 =           0,
  .sqr3 =           ADC_SQR3_SQ1_N (ADC_CHANNEL_SENSOR)
};

*/
float adc_get_temp_internal(void){
#warning todo rewrite without chibi ADC
  return 0;
/*
  adcStart(&ADCD1, NULL);
  adcSTM32EnableTSVREFE();
  adcConvert(&ADCD1, &adc_conv_grp_temp_int, adc_buf_temp_int, ADC_TEMP_INT_N); //dumy for config
  chThdSleepMilliseconds(1); //wait for temp sens startup

  adcConvert(&ADCD1, &adc_conv_grp_temp_int, adc_buf_temp_int, ADC_TEMP_INT_N);
  adcSTM32DisableTSVREFE();
  adcStop(&ADCD1);

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
  */
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 10 samples of 1 channel, SW triggered.
 * Channels:    temp sensor.
 *

#define ADC_TEMP_HEAT_NUM_CH   1
#define ADC_TEMP_HEAT_N 100
static adcsample_t adc_buf_temp_heat[ADC_TEMP_HEAT_NUM_CH * ADC_TEMP_HEAT_N];
static const ADCConversionGroup adc_conv_grp_temp_heat =
{
 .circular =       FALSE,
 .num_channels =   ADC_TEMP_HEAT_NUM_CH,
 .end_cb =         NULL,
 .error_cb =       NULL,
 .cr1 =            0,
 .cr2 =            ADC_CR2_SWSTART,
 .smpr1 =          ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144),
 .smpr2 =          0,
 .htr =            0,
 .ltr =            0,
 .sqr1 =           ADC_SQR1_NUM_CH(ADC_TEMP_HEAT_NUM_CH),
 .sqr2 =           0,
 .sqr3 =           ADC_SQR3_SQ1_N (ADC_CHANNEL_IN12)
};
*/

float adc_get_temp_heater(void){
#warning todo rewrite without chibi ADC
  return 0;
  /*
  adcStart(&ADCD1, NULL);
  adcConvert(&ADCD1, &adc_conv_grp_temp_heat, adc_buf_temp_heat, ADC_TEMP_HEAT_N); //dumy for config

  adcConvert(&ADCD1, &adc_conv_grp_temp_heat, adc_buf_temp_heat, ADC_TEMP_HEAT_N);
  adcStop(&ADCD1);

  uint32_t mean = 0;
  for(uint16_t n=0; n<ADC_TEMP_HEAT_N; ++n){
    mean += adc_buf_temp_heat[n];
  }
  float v = (((float)mean) * ADC_V_MAX / ADC_BINS) / ADC_TEMP_HEAT_N;

  //TODO calibrate ADC full scale with vrefint
  //VREFIN_CAL, Raw data acquired at temperature of, 30 °C VDDA = 3.3 V, 0x1FFF 7A2A - 0x1FFF 7A2B
  return lmt85_volt_to_temp_deg_c(v);
  */
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 10 samples of 1 channel, SW triggered.
 * Channels:    temp sensor.
 *
#define ADC_CURRENT_NUM_CH   1
#define ADC_CURRENT_N 10
static adcsample_t adc_buf_current[ADC_CURRENT_NUM_CH * ADC_CURRENT_N];

static const ADCConversionGroup adc_conv_grp_current =
{
 .circular =       FALSE,
 .num_channels =   ADC_CURRENT_NUM_CH,
 .end_cb =          NULL,
 .error_cb =       NULL,
 .cr1 =            0,
 .cr2 =            ADC_CR2_SWSTART,
 .smpr1 =          ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144),
 .smpr2 =          0,
 .htr =            0,
 .ltr =            0,
 .sqr1 =           ADC_SQR1_NUM_CH(ADC_CURRENT_NUM_CH),
 .sqr2 =           0,
 .sqr3 =           ADC_SQR3_SQ1_N (ADC_CHANNEL_IN7)
};
*/
float adc_get_current(void){
#warning todo rewrite without chibi ADC
  return 0;
  /*
  adcStart(&ADCD1, NULL);
  adcConvert(&ADCD1, &adc_conv_grp_current, adc_buf_current, ADC_CURRENT_N); //dumy for config

  adcConvert(&ADCD1, &adc_conv_grp_current, adc_buf_current, ADC_CURRENT_N);
  adcStop(&ADCD1);

  uint32_t mean = 0;
  for(uint16_t n=0; n<ADC_CURRENT_N; ++n){
    mean += adc_buf_current[n];
  }

  float v = (float)mean/(float)ADC_CURRENT_N;
  v = v*ADC_V_MAX/ADC_BINS;

  //TODO calibrate ADC full scale with vrefint
  //VREFIN_CAL, Raw data acquired at temperature of, 30 °C VDDA = 3.3 V, 0x1FFF 7A2A - 0x1FFF 7A2B
  return v;
  */
}

float lmt85_volt_to_temp_deg_c(float v){
  return (v-1.567)*-120.48; //LMT85: 0°C 1.567V, -8.3mV/deg 0-100°C. div2 on board
}


//ADC_CR2_SWSTART causes immediate start of conversion?! but then at least error callback is not called

void adc_init_TAC(){

  adc_TAC_end_cb_counter = 0;
  adc_TAC_error_cb_counter = 0;

  //ADC1->CR2 |= ADC_CR2_SWSTART;

  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN); //enable peripheral clock
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_ADCRST); //assert reset
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_ADCRST); //deassert reset -> registers should be at power up defaults


  //Defaults: Single conversion, 12bit, right aligned
  ADC1->SMPR1 = (1 << ADC_SMPR1_SMP10_Pos); //010: 15 cycles = 600ns
  ADC1->JSQR = 10 << ADC_JSQR_JSQ4_Pos; //single injected conversion, CH10, result in JDR1!
  ADC1->CR1 = ADC_CR1_JEOCIE; //JEOC interrupt enabled (injected end of conversion)
  ADC1->CR2 = ADC_CR2_ADON | ADC_CR2_JEXTEN_0 | (11 << ADC_CR2_JEXTSEL_Pos); //Enable ADC (needs 3us after this for stable conversions)
                                               //rising edge trigger, Timer 5 TRGO event

  NVIC_SetPriority(ADC_IRQn, 7);
  NVIC_EnableIRQ(ADC_IRQn);
}









