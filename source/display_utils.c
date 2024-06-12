/*
 * display_utils.c
 *
 *  Created on: 11.06.2024
 *      Author: patri
 */


#include "main.h"
#include <display_bitmaps.h>

extern uint32_t graph_buf[X_N];
extern int global;

//fast duty cycle 2 requires that pclk1 % (3*i2c_clk) = 0
//will not run with CH_DBG_ENABLE_ASSERTS   TRUE
static const I2CConfig i2cfg2 = {
                                 OPMODE_I2C,
                                 396825, //50000000/(3*42),
                                 FAST_DUTY_CYCLE_2, //STD_DUTY_CYCLE, FAST_DUTY_CYCLE_2, FAST_DUTY_CYCLE_16_9
};

//hw i2c
uint8_t u8x8_byte_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  static uint8_t buffer[32];        /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
  static uint8_t buf_idx;
  uint8_t *data;

  switch(msg)
  {
  case U8X8_MSG_BYTE_SEND:
    data = (uint8_t *)arg_ptr;
    while( arg_int > 0 )
    {
      buffer[buf_idx++] = *data;
      data++;
      arg_int--;
    }
    break;
  case U8X8_MSG_BYTE_INIT:
    i2cStart(&I2CD2, &i2cfg2);
    break;
  case U8X8_MSG_BYTE_SET_DC:
    /* ignored for i2c */
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    buf_idx = 0;
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    //why u8x8_GetI2CAddress(u8x8) >> 1
    i2cMasterTransmitTimeout(&I2CD2, u8x8_GetI2CAddress(u8x8) >> 1, buffer, buf_idx, NULL, 0, TIME_INFINITE);
    //debug
    global = u8x8_GetI2CAddress(u8x8) >> 1;
    break;
  default:
    return 0;
  }
  return 1;
}

uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  (void)arg_ptr; //to remove unused parameter warning

  switch(msg)
  {
  case U8X8_MSG_GPIO_AND_DELAY_INIT:
    /* only support for software I2C*/

    break;
  case U8X8_MSG_DELAY_NANO:
    /* not required for SW I2C */
    break;

  case U8X8_MSG_DELAY_10MICRO:
    /* not used at the moment */
    break;

  case U8X8_MSG_DELAY_100NANO:
    /* not used at the moment */
    break;

  case U8X8_MSG_DELAY_MILLI:
    chThdSleepMilliseconds(1);
    break;

  case U8X8_MSG_DELAY_I2C:
    /* arg_int is 1 or 4: 100KHz (5us) or 400KHz (1.25us) */

    if(arg_int == 1){
      gptPolledDelay(&GPTD6, 10);
    } else {
      gptPolledDelay(&GPTD6, 2);
      //#warning gptPolledDelay didn't work with 1MHz, 1tick wait (1tick -> 0tick)
    }
    break;

  case U8X8_MSG_GPIO_I2C_CLOCK: //arg_int=0: Output low at I2C clock pin, 1: Input dir with pullup high for I2C clock pin

    if ( arg_int == 0 )
    {
      palClearPad(GPIOB, 8);
      palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
    }
    else
    {
      palSetPadMode(GPIOB, 8, PAL_MODE_INPUT);
    }
    break;

  case U8X8_MSG_GPIO_I2C_DATA:
    if ( arg_int == 0 )
    {
      palClearPad(GPIOB, 9);
      palSetPadMode(GPIOB, 9, PAL_MODE_OUTPUT_PUSHPULL);
    }
    else
    {
      palSetPadMode(GPIOB, 9, PAL_MODE_INPUT);
    }
    break;
    /*
    case U8X8_MSG_GPIO_MENU_SELECT:
      u8x8_SetGPIOResult(u8x8, Chip_GPIO_GetPinState(LPC_GPIO, KEY_SELECT_PORT, KEY_SELECT_PIN));
      break;
    case U8X8_MSG_GPIO_MENU_NEXT:
      u8x8_SetGPIOResult(u8x8, Chip_GPIO_GetPinState(LPC_GPIO, KEY_NEXT_PORT, KEY_NEXT_PIN));
      break;
    case U8X8_MSG_GPIO_MENU_PREV:
      u8x8_SetGPIOResult(u8x8, Chip_GPIO_GetPinState(LPC_GPIO, KEY_PREV_PORT, KEY_PREV_PIN));
      break;
    case U8X8_MSG_GPIO_MENU_HOME:
      u8x8_SetGPIOResult(u8x8, Chip_GPIO_GetPinState(LPC_GPIO, KEY_HOME_PORT, KEY_HOME_PIN));
      break;
     */
  default:
    u8x8_SetGPIOResult(u8x8, 1);
    break;
  }
  return 1;
}

void plot_graph(u8g2_t* u8g2, uint32_t start, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, uint8_t y_min, uint8_t y_max){
  u8g2_DrawFrame(u8g2, x, y, w, h);
  float scale = (float)h / (float)(y_max - y_min);
  for(u8g2_uint_t i = 0; i < w; ++i){
    float y_f = (graph_buf[(start+i)%w] - y_min) * scale;
    u8g2_DrawPixel(u8g2, i + x, h - ((u8g2_uint_t) y_f) + y);
  }
}

void display_bootScreen(u8g2_t* u8g2){
u8g2_ClearBuffer(u8g2);
u8g2_DrawXBMP(u8g2, 0, 0, 128, 64, windows_logo);
u8g2_SendBuffer(u8g2);
chThdSleepMilliseconds(600);

u8g2_DrawXBMP(u8g2, 21, 56, 87, 8, bitmap_loading_bar_2_87x8);
u8g2_SendBuffer(u8g2);
chThdSleepMilliseconds(800);

u8g2_DrawXBMP(u8g2, 21, 56, 87, 8, bitmap_loading_bar_3_87x8);
u8g2_SendBuffer(u8g2);
chThdSleepMilliseconds(500);
}

void disp_rule90(u8g2_t* u8g2){
  //rule 90
  uint32_t a[4];
  a[0] = rand32();
  a[1] = rand32();
  a[2] = rand32();
  a[3] = rand32();

  u8g2_ClearBuffer(u8g2);
  //  for(uint32_t i = 0; i<128; ++i){
  //    if(a[i>>5] & 1<<(i%32)){
  //      u8g2_DrawPixel(u8g2, i, 0);
  //    }
  //  }
  //  u8g2_SendBuffer(u8g2);
  for(uint32_t j = 1; j<64; ++j){
    uint32_t b[4] = {0,0,0,0};

    for(uint32_t i = 1; i<127; ++i){
      if(((a[(i-1)>>5] & 1<<((i-1)%32))>0) != ((a[(i+1)>>5] & 1<<((i+1)%32)) > 0)){
        u8g2_DrawPixel(u8g2, i, j);
        b[i>>5] |= 1<<(i%32);
      }
    }
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    a[3] = b[3];
    u8g2_SendBuffer(u8g2);
  }
}
