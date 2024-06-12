/*
 * main.h
 *
 *  Created on: 12.09.2023
 *      Author: patri
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <display_utils.h>
#include <printf.h>
#include <thd_cntr.h>
#include <timers.h>
#include <string.h>
#include <stdint.h>
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "utils.h"
#include "display_u8g2.h"
#include "ADF4156.h"
#include "gnss.h"
#include "adc.h"
#include "heater.h"

//extern BaseSequentialStream* bsp2;
int myprintf(const char *fmt, ...);

#define T_SETPONT 50  //Default heater temperature (50 seems to work)

#define TIME_1S (100000000LL << 16)
#define TIME_RES_F ((float)(0.152587890625e-12))

#endif /* MAIN_H_ */
