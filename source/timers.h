/*
 * TIM5.h
 *
 *  Created on: 15.03.2024
 *      Author: patri
 */

#ifndef SOURCE_TIMERS_H_
#define SOURCE_TIMERS_H_

#include <stdint.h>

void TIM5_init(void);
uint32_t TIM5_get_capture_reg(void);

#endif /* SOURCE_TIMERS_H_ */
