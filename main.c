/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

/* notes:
 *
 * VPN (cyberghost) hast to be disabled to connect to openocd
 *
 * # Drivers compatible with the platform STM32F4:
include $(CHIBIOS)/os/hal/ports/STM32/LLD/ADCv2/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/CANv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/CRYPv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/DACv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/DMAv2/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/EXTIv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/GPIOv2/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/I2Cv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/MACv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/OTGv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/QUADSPIv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/RTCv2/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/SPIv1/driver_v2.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/SDIOv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/SYSTICKv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/TIMv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/USARTv1/driver.mk
include $(CHIBIOS)/os/hal/ports/STM32/LLD/xWDGv1/driver.mk



 */



#include "main.h"

BaseSequentialStream* bsp = (BaseSequentialStream*)&SD2;

/* Static variable which can be seen from every function of this module. */
static uint8_t state = 0;


/*===========================================================================*/
/* ADC related code                                                          */
/*===========================================================================*/





/* Serial Manager thread. */
static THD_WORKING_AREA(waThdSerial, 2000); //256
static THD_FUNCTION(ThdSerial, arg) {
  (void) arg;
  chRegSetThreadName("Serial manager");
  static const SerialConfig my_config =
  {
   115200,
   0,
   USART_CR2_STOP1_BITS,
   0
  };
  sdStart(&SD2, &my_config);

  sdWrite(&SD2, (uint8_t*)"Hohoho\n", 8);

#warning todo connect display i2c, rst
  //  int temp = display_init();
  int temp = 0;
  chprintf(bsp, "I2C_addr = %d\n", temp);
  chprintf(bsp, "I2C_addr = 0x%x\n", temp);

  chprintf(bsp, "%f \n", 1.54);

  get_temp_internal();



  while(true) {
    /* Getting data from Serial Driver with a timeout. */
    msg_t tkn = sdGetTimeout(&SD2, TIME_MS2I(100));
    /* Checking if a timeout has occurred. */
    if(tkn != MSG_TIMEOUT) {
      /* Not a timeout. Echoing the character to improve user experience. */
      sdPut(&SD2, tkn);
      //sdWrite(&SD2, (uint8_t*)"\r\n", 2U);
      if((tkn >= '0') && (tkn <= '2')) {
        /* Allowed character: updating state. Critical zone as the variable is shared.*/
        chSysLock();
        state = tkn;
        chSysUnlock();
      }
    }
    /* No sleep needed here. This thread releases the CPU onsdGetTimeout. */
  }
}


/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    for(float i=30; i<150; i=i*1.1){
      palSetPad(GPIOB, GPIOB_LED1);
      palClearPad(GPIOC, GPIOC_LED2);
      chThdSleepMilliseconds(i);
      palClearPad(GPIOB, GPIOB_LED1);
      palSetPad(GPIOC, GPIOC_LED2);
      chThdSleepMilliseconds(i);
    }
    for(float i=150; i>30; i=i*0.9){
      palSetPad(GPIOB, GPIOB_LED1);
      palClearPad(GPIOC, GPIOC_LED2);
      chThdSleepMilliseconds(i);
      palClearPad(GPIOB, GPIOB_LED1);
      palSetPad(GPIOC, GPIOC_LED2);
      chThdSleepMilliseconds(i);
    }
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /* Creating the serial manager thread. */
  chThdCreateStatic(waThdSerial, sizeof(waThdSerial), NORMALPRIO, ThdSerial,
                    NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */




  while (true) {
    //if (!palReadPad(GPIOC, GPIOC_BUTTON)) {
    //do something
    get_temp_internal();

    chThdSleepMilliseconds(500);
  }
}
