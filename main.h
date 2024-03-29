/*
 * main.h
 *
 *  Created on: 12.09.2023
 *      Author: patri
 */

#ifndef MAIN_H_
#define MAIN_H_

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

//extern BaseSequentialStream* bsp2;
int myprintf(const char *fmt, ...);

#endif /* MAIN_H_ */
