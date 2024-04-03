/*
 * utils.h
 *
 *  Created on: 12.09.2023
 *      Author: patri
 */

#include <stdint.h>

#ifndef SOURCE_UTILS_H_
#define SOURCE_UTILS_H_

#define DAC_TEMP_MIN 4095u // 2^12-1, max voltage = min temp ( <0°)
#define DAC_TEMP_1 1985 // 2^12-1, max voltage = min temp ( <0°)

void heater_setTempDegC(float t);
void heater_init(void);
void heater_disable(void);
uint32_t rand32(void);
void piezo_toggle(void);


#endif /* SOURCE_UTILS_H_ */
