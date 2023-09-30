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


extern BaseSequentialStream* bsp;


uint32_t rseed = 2804628253;  // 100% random seed value


#define TEMPSENSOR_CAL1_ADDR     ((uint16_t*) (0x1FFF7A2C)) //30°
#define TEMPSENSOR_CAL2_ADDR     ((uint16_t*) (0x1FFF7A2E)) //110°


#define MY_NUM_CH   1
#define MY_SAMPLES 10


static adcsample_t adc_buf[MY_NUM_CH * MY_SAMPLES];

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 10 samples of 1 channel, SW triggered.
 * Channels:    temp sensor.
 */
static const ADCConversionGroup adc_conv_grp_temp = {
  FALSE,                            /*NOT CIRCULAR*/
  MY_NUM_CH,                        /*NUMB OF CH*/
  NULL,                             /*NO ADC CALLBACK*/
  NULL,                             /*NO ADC ERROR CALLBACK*/
  0,                                /* CR1 */
  ADC_CR2_SWSTART,                  /* CR2 soft trigger*/
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144), /* SMPR1 144cycles*/
  0,                                /* SMPR2 */
  0,                                /* HTR */
  0,                                /* LTR */
  ADC_SQR1_NUM_CH(MY_NUM_CH),       /* SQR1 */
  0,                                /* SQR2 */
  ADC_SQR3_SQ1_N (ADC_CHANNEL_SENSOR)/* SQR3 */
};

float get_temp_internal(void){

  adcStart(&ADCD1, NULL);
  adcSTM32EnableTSVREFE();
  adcConvert(&ADCD1, &adc_conv_grp_temp, adc_buf, MY_SAMPLES); //dumy for config
  chThdSleepMilliseconds(1); //wait for temp sens startup

  adcConvert(&ADCD1, &adc_conv_grp_temp, adc_buf, MY_SAMPLES);
  adcSTM32DisableTSVREFE();

  uint32_t mean = 0;
  for(uint16_t i=0; i<MY_SAMPLES; ++i){
    //chprintf(bsp, "sample %d = %d\n", i, adc_buf[i]);
    mean += adc_buf[i];
  }

  float t = (float)mean/(float)MY_SAMPLES;
  chprintf(bsp,"mean = %f\n", t);

  float cal30 = *TEMPSENSOR_CAL1_ADDR;
  float cal110 = *TEMPSENSOR_CAL2_ADDR;
  //chprintf(bsp,"cal30 = %f, cal110 = %f\n", cal30, cal110);


  float slope = (cal110-cal30)/80.0;
  chprintf(bsp,"slope = %f [counts], %f [mv/deg]\n", slope, slope*3300/4096.0);

  float temp = (t - cal30) / slope + 30.0;
  chprintf(bsp,"temp = %f\n", temp);

  //TODO calibrate ADC full scale with vrefint
  //VREFIN_CAL, Raw data acquired at temperature of, 30 °C VDDA = 3.3 V, 0x1FFF 7A2A - 0x1FFF 7A2B
  return temp;
}

//https://excamera.com/sphinx/article-xorshift.html
uint32_t rand32(void)
{
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

