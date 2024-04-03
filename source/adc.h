/*
 * adc.h
 *
 *  Created on: 01.04.2024
 *      Author: patri
 */

#ifndef SOURCE_ADC_H_
#define SOURCE_ADC_H_

#include <stdint.h>

#define ADC_BINS 4096
#define ADC_V_MAX 3.3

float adc_get_temp_internal(void);
float adc_get_temp_heater(void);
float adc_get_current(void);
void adc_init_TAC(void);

#endif /* SOURCE_ADC_H_ */
