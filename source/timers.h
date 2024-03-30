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
void TIM1_init(void);
void TIM9_init(uint16_t delay, uint16_t width);

#endif /* SOURCE_TIMERS_H_ */
