/*
 * utils.c
 *
 *  Created on: 12.09.2023
 *      Author: patri
 */


#include "utils.h"
#include "main.h"

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


//https://excamera.com/sphinx/article-xorshift.html
uint32_t rand32(void)
{
  static uint32_t rseed = 2804628253;  // 100% random seed value
  rseed ^= rseed << 13;
  rseed ^= rseed >> 17;
  rseed ^= rseed << 5;
  return rseed;
}



















