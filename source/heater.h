/*
 * heater.h
 *
 *  Created on: 10.06.2024
 *      Author: patri
 */
#include <stdint.h>

#ifndef SOURCE_HEATER_H_
#define SOURCE_HEATER_H_

#include "main.h"

#define DAC_TEMP_MIN 4095u // 2^12-1, max voltage = min temp ( <0°)
#define DAC_TEMP_1 1985 // 2^12-1, max voltage = min temp ( <0°)

void heater_setTempDegC(float t);
void heater_init(void);
void heater_disable(void);
void heater_get_temp_current(float* t_heater, float* t_int, float* i_heater);


#endif /* SOURCE_HEATER_H_ */
