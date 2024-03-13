/*
 * ADF4156.c
 *
 *  Created on: 13.03.2024
 *      Author: patri
 */

#include "main.h"

/*
 * SPI configuration (xxMHz, CPHA=0, CPOL=0, MSb first).
 * 21 MHz with div16??
 */
const SPIConfig spicfg_adf = {
  .circular         = false,
  .slave            = false,
  .data_cb          = NULL,
  .error_cb         = NULL,
  .ssport           = GPIOB,
  .sspad            = GPIOB_ADF_LE,
  .cr1              = SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2, //111 -> fpclk/256
  .cr2              = 0U
};

#define ADF_TXBUF_LEN 4
//CC_ALIGN_DATA(32) static uint8_t adf_txbuf[ADF_TXBUF_LEN];

/**
 * @brief   Sends data over the SPI bus.
 * @details This synchronous function performs a transmit operation.
 * @pre     In order to use this function the option @p SPI_USE_WAIT must be
 *          enabled.
 * @pre     In order to use this function the driver must have been configured
 *          without callbacks (@p end_cb = @p NULL).
 * @note    The buffers are organized as uint8_t arrays for data sizes below
 *          or equal to 8 bits else it is organized as uint16_t arrays.
 *
 * @param[in] spip      pointer to the @p SPIDriver object
 * @param[in] n         number of words to send
 * @param[in] txbuf     the pointer to the transmit buffer
 *
 * @api
 */
//void spiSend(SPIDriver *spip, size_t n, const void *txbuf) {

void adf_write_reg(uint32_t data){

#warning debug trying out bitbang seems to work muxout 0 1 ok
 /* myprintf("adf_write_reg: 0x%08X\n", data);
  spiStart(&SPID2, &spicfg_adf); // Setup transfer parameters.
  spiSelect(&SPID2);            // Slave Select assertion.
  for(int i=3; i>=0; --i){
    uint8_t temp = data >> (i * 8);
    //myprintf("adf_write_ byte: 0x%X\n",temp);
    spiSend(&SPID2, 1, &temp);
  }
  spiUnselect(&SPID2);            // Slave Select deassertion.
  */

  palClearPad(GPIOB, GPIOB_ADF_DATA);
  palClearPad(GPIOB, GPIOB_ADF_CLK);
  myprintf("Bitbang adf_write_reg: 0x%08X\n", data);
  palClearPad(GPIOB, GPIOB_ADF_LE);           // Slave Select assertion.
   for(int i=3; i>=0; --i){
     uint8_t temp = data >> (i * 8);
     //myprintf("adf_write_ byte: 0x%X\n",temp);

     //MSB first
     if(temp&0x80)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);

     if(temp&0x40)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);

     if(temp&0x20)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);

     if(temp&0x20)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);

     if(temp&0x08)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);

     if(temp&0x04)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);

     if(temp&0x02)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);

     if(temp&0x01)  palSetPad(GPIOB, GPIOB_ADF_DATA);
     else           palClearPad(GPIOB, GPIOB_ADF_DATA);
     chThdSleepMilliseconds(1);
     palSetPad(GPIOB, GPIOB_ADF_CLK);
     chThdSleepMilliseconds(1);
     palClearPad(GPIOB, GPIOB_ADF_CLK);
   }
   palSetPad(GPIOB, GPIOB_ADF_LE);             // Slave Select deassertion.
}


//ADF4156
//div = 2,4,..,8190
//r = 1,2,..,32 (*2 = 2,4,..64)
//n = 23,24,..,4095 (*2 = 46,48,..,8190)
//if div > 64, n
//muxout/2 is used except when r = 1
//if r = 0: n divider is used (should be usable > 10 MHz)
//testmode = 1: muxout high, testmode = 2: muxout low

void adf_config(uint32_t div_n, uint32_t div_r, uint8_t testmode) {
  uint32_t ADF4156_reg[5] = {0,1,2,3,4}; //reg addresses

  uint32_t n = (div_n/2) & 0x0FFF;
  if(n < 23){
    n = 23; //minimum in datasheet
  }

  //R0 -----------------------------------------------------------
  uint32_t r;
  if(testmode == 1){
    ADF4156_reg[0] |= 1 << 27; // muxout high
  } else if(testmode == 2){
    ADF4156_reg[0] |= 2 << 27; // muxout low
  }else if(div_r == 0){
    ADF4156_reg[0] |= 14 << 27; // muxout Ndiv/2
    r = 1;
  } else if(div_r == 1){
    ADF4156_reg[0] |=  3 << 27; // muxout Rdiv
    r = 1;
  } else {
    ADF4156_reg[0] |=  13 << 27; // muxout Rdiv/2
    r = (div_r/2) & 0x001F;
  }

  ADF4156_reg[0] |= n << 15; //N divider, 12 bit
  //FRAC = 0 -> integer mode

  //R1 -----------------------------------------------------------
  ADF4156_reg[1] |= 1 << 3; // recommended phase value if unused

  //R2 -----------------------------------------------------------
  if(n > 75){
    ADF4156_reg[2] |= 1 << 20; //enable 8/9 prescaler. todo: recommended to use 8/9 only above 3 GHz
  }
  ADF4156_reg[2] |= r << 15; //R divider 5 bit
  ADF4156_reg[2] |= 2 << 3; //Mod = 2 (minimum)

  //R3 -----------------------------------------------------------
  ADF4156_reg[3] |= 1 << 4; //Charge pump tristate

  //R4 -----------------------------------------------------------
  //default: all 0

  //Programming sequence R4,R3,..,R0 (write to R0 transfers double buffered settings)
  adf_write_reg(ADF4156_reg[4]);
  adf_write_reg(ADF4156_reg[3]);
  adf_write_reg(ADF4156_reg[2]);
  adf_write_reg(ADF4156_reg[1]);
  adf_write_reg(ADF4156_reg[0]);
#warning debug
  /*copy of unsuccessfully tried alternate function regs below.
   * trying bitbang spi now:
   * #define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN9, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN10, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_ADF_LE, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_ADF_CLK, 5U) |         \
                                     PIN_AFIO_AF(GPIOB_LED1, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_ADF_DATA, 5U))
   */
}
