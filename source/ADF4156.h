/*
 * ADF4156.h
 *
 *  Created on: 13.03.2024
 *      Author: patri
 */

#ifndef SOURCE_ADF4156_H_
#define SOURCE_ADF4156_H_

#include <stdint.h>

void adf_config_div_n(uint32_t div_n);
void adf_config_div_r(uint32_t div_r);
void adf_config_testmode_muxout_low(void);
void adf_config_testmode_muxout_high(void);

#endif /* SOURCE_ADF4156_H_ */
