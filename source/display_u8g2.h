#include "u8g2.h"

#ifndef DISPLAY_U8G2_H_
#define DISPLAY_U8G2_H_
uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
int display_init (void);

#endif /* DISPLAY_U8G2_H_ */
