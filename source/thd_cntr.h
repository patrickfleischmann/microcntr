/*
 * task_cntr.h
 *
 *  Created on: 04.03.2024
 *      Author: patri
 */

#ifndef SOURCE_THD_CNTR_H_
#define SOURCE_THD_CNTR_H_

#include <stdint.h>

#define HIST_IDX_MASK (0x0FFF)
#define HIST_BUF_LEN (4096)
#define HIST_SAMPLES_MAX (2000000)

void ThdCntrFunc(void);
uint64_t cntr_get_period_fs(void);
float cntr_get_freq_hz(void);
void cntr_start(void);
void cntr_stop(void);
int cntr_is_running(void);

#endif /* SOURCE_THD_CNTR_H_ */
