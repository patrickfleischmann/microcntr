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

void adcSTM32EnableTSVREFE(void);

float lmt85_volt_to_temp_deg_c(float v);

uint32_t adc_TAC_end_cb_counter;
uint32_t adc_TAC_error_cb_counter;


//ADC_CR2_SWSTART causes immediate start of conversion?! but then at least error callback is not called
//Sample TAC_out on CH10: T_sample 15cycles
//Sample T_heater on CH12
//maximum trigger rate: ca. 2us
void adc_init_TAC(){

  adc_TAC_end_cb_counter = 0;
  adc_TAC_error_cb_counter = 0;

  //ADC1->CR2 |= ADC_CR2_SWSTART;

  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN); //enable peripheral clock
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_ADCRST); //assert reset
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_ADCRST); //deassert reset -> registers should be at power up defaults


  //Defaults: Single conversion, 12bit, right aligned
  ADC1->SMPR1 = (1 << ADC_SMPR1_SMP10_Pos); //TAC_out: 15 cycles = 600ns
  ADC1->SMPR1 |= (2 << ADC_SMPR1_SMP12_Pos); //T_heater: 28 cycles = 1100ns
  ADC1->JSQR = (1 << ADC_JSQR_JL_Pos)|(10 << ADC_JSQR_JSQ3_Pos)|(12 << ADC_JSQR_JSQ4_Pos); //2 injected conversions: CH10(result in JDR1), CH12
  ADC1->CR1 = ADC_CR1_SCAN | ADC_CR1_JEOCIE; //Scan mode, JEOC interrupt enabled (injected end of conversion group)
  ADC1->CR2 = ADC_CR2_ADON | ADC_CR2_JEXTEN_0 | (11 << ADC_CR2_JEXTSEL_Pos); //Enable ADC (needs 3us after this for stable conversions)
                                               //rising edge trigger, Timer 5 TRGO event

  NVIC_SetPriority(ADC_IRQn, 7);
  NVIC_EnableIRQ(ADC_IRQn);
}


//Sample v_current on CH7
//Sample T_heater on CH12
//Sample T_int on CH18
//(start conversion in other function using ADC_CR2_SWSTART)
void adc_init_temp_current(){
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN); //enable peripheral clock
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_ADCRST); //assert reset
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_ADCRST); //deassert reset -> registers should be at power up defaults

  //Defaults: Single conversion, 12bit, right aligned
  ADC1->SMPR2 |= (7 << ADC_SMPR2_SMP7_Pos); //v_current: 480 cycles = 20us
  ADC1->SMPR1 |= (7 << ADC_SMPR1_SMP12_Pos); //T_heater: 480 cycles = 20us
  ADC1->SMPR1 |= (7 << ADC_SMPR1_SMP18_Pos); //T_int:    480 cycles = 20us
  //3 injected conversions: CH7 in JDR1, CH12 in JDR2, CH18 in JDR3
  ADC1->JSQR = (2 << ADC_JSQR_JL_Pos)|(7 << ADC_JSQR_JSQ2_Pos)|(12 << ADC_JSQR_JSQ3_Pos)|(18 << ADC_JSQR_JSQ4_Pos);
  ADC1->CR1 = ADC_CR1_SCAN; //Scan mode, no JEOC interrupt
  ADC1->CR2 = ADC_CR2_ADON;   //Enable ADC(needs 3us after this for stable conversions)

  ADC->CCR = ADC_CCR_TSVREFE; //enable conversion of internal sensors (needs 10us after this)
}

void adc_get_temp_current(uint32_t* jdr3, uint32_t* jdr2, uint32_t* jdr1, uint32_t n_avg){
  *jdr3 = 0;
  *jdr2 = 0;
  *jdr1 = 0;

  for(uint32_t i = 0; i < n_avg; ++i){
    CLEAR_BIT(ADC1->SR, ADC_SR_JEOC);
    ADC1->CR2 |= ADC_CR2_JSWSTART; //Start injected group
    while(!(ADC1->SR & ADC_SR_JEOC)){} //wait for end of conversion
    *jdr3 += ADC1->JDR3;
    *jdr2 += ADC1->JDR2;
    *jdr1 += ADC1->JDR1;
  }

  *jdr3 /= n_avg;
  *jdr2 /= n_avg;
  *jdr1 /= n_avg;
}








