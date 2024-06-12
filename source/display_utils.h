/*
 * display_utils.h
 *
 *  Created on: 11.06.2024
 *      Author: patri
 */

#ifndef SOURCE_DISPLAY_UTILS_H_
#define SOURCE_DISPLAY_UTILS_H_

#include "u8g2.h"
#include "mui_u8g2.h"

#include <stdint.h>

uint8_t u8x8_byte_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void display_bootScreen(u8g2_t* u8g2);
void plot_graph(u8g2_t* u8g2, uint32_t start, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, uint8_t y_min, uint8_t y_max);
void disp_rule90(u8g2_t* u8g2);

#endif /* SOURCE_DISPLAY_UTILS_H_ */
