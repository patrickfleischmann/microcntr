/*
 * heater.c
 *
 *  Created on: 10.06.2024
 *      Author: patri
 */

#include "main.h"

#define N_AVG_TEMP 32
#define TEMPSENSOR_CAL1_ADDR     ((uint16_t*) (0x1FFF7A2C)) //30°
#define TEMPSENSOR_CAL2_ADDR     ((uint16_t*) (0x1FFF7A2E)) //110°

static uint8_t heater_setpoint = T_SETPONT;
static uint32_t cal_0mA;
static uint32_t cal_200mA;

float lmt85_volt_to_temp_deg_c(float v){
  return (v-1.567)*-120.48; //LMT85: 0°C 1.567V, -8.3mV/deg 0-100°C.
}

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

uint8_t heater_getSetpoint(void){
  return heater_setpoint;
}

void heater_init(void){

  adc_init_temp_current();
  chThdSleepMilliseconds(1);

  palClearPad(GPIOA, GPIOA_heater_enable);
  dac_init();
  heater_setTempDegC(0.0);
  chThdSleepMilliseconds(100); //wait for opamp input to settle
  //dac value MUST be set to low temperature before heater is enabled
  //To ensure soft start and no current limit overshoot
  palSetPad(GPIOA, GPIOA_heater_enable);
  chThdSleepMilliseconds(300);

  uint32_t jdr3, jdr2, jdr1;
  adc_get_temp_current(&jdr3, &jdr2, &jdr1, N_AVG_TEMP);

  cal_0mA = jdr1;

  heater_setTempDegC(60.0);
  chThdSleepMilliseconds(300);
  adc_get_temp_current(&jdr3, &jdr2, &jdr1, N_AVG_TEMP);

  cal_200mA = jdr1;

  heater_setTempDegC(T_SETPONT);
}

void heater_disable(void){
  palClearPad(GPIOA, GPIOA_heater_enable);
}

void heater_get_temp_current(float* t_heater, float* t_int, float* i_heater){
  uint32_t jdr3, jdr2, jdr1;
  adc_get_temp_current(&jdr3, &jdr2, &jdr1, N_AVG_TEMP);

  float t = (float)( jdr3);
  float cal30 = *TEMPSENSOR_CAL1_ADDR;
  float cal110 = *TEMPSENSOR_CAL2_ADDR;
  float slope = (cal110-cal30)/80.0;
  *t_int = (t - cal30) / slope + 30.0;

  //TODO average multiple conversions
  /* TODO calibrate temperature
  TS_CAL1
  TS ADC raw data acquired at temperature of 30 °C, VDDA= 3.3 V
  0x1FFF 7A2C - 0x1FFF 7A2D
  TS_CAL2
  TS ADC raw data acquired at temperature of 110 °C, VDDA= 3.3 V
  0x1FFF 7A2E - 0x1FFF 7A2F
  */

  //TODO calibrate ADC full scale with vrefint
  //VREFIN_CAL, Raw data acquired at temperature of, 30 °C VDDA = 3.3 V, 0x1FFF 7A2A - 0x1FFF 7A2B

  float v = (float)( jdr2);
  v = (v * ADC_V_MAX / ADC_BINS);
  *t_heater = lmt85_volt_to_temp_deg_c(v);

  t = cal_0mA-cal_200mA; //slope
  v = (float)( jdr1);
//  myprintf("heater_get_temp_current cal_200mA: %u\n", cal_200mA);
//  myprintf("heater_get_temp_current cal_0mA: %u\n", cal_0mA);
//  myprintf("heater_get_temp_current jdr1: %f\n", v);
  v = (1.0 - ((v-cal_200mA) / t)) * 200.0;
  *i_heater = v;
  if(*i_heater < 0.0){
    *i_heater = 0.0;
  }
}
