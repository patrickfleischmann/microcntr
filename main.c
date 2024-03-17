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

Drivers compatible with the platform STM32F4:
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

CHibios was using tim5 STM32_ST_USE_TIMER = 5
i need tim 5
switching to tim11
but display was using tim11
trying to use tim6 for display

 */



#include "main.h"

BaseSequentialStream* bsp2 = (BaseSequentialStream*)&SD2;
BaseSequentialStream* bsp1 = (BaseSequentialStream*)&SD1;

static mutex_t mutex_bsp2;


static uint32_t beep_ms = 200;

int myprintf(const char *fmt, ...) {
  va_list ap;
  int formatted_bytes;
  chMtxLock(&mutex_bsp2);
  va_start(ap, fmt);
  formatted_bytes = chvprintf(bsp2, fmt, ap);
  va_end(ap);
  chMtxUnlock(&mutex_bsp2);

  return formatted_bytes;
}



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

  myprintf("ThdSerial\n");

  while(true) {

    /*
    // Getting data from Serial Driver with a timeout.
    msg_t tkn = sdGetTimeout(&SD2, TIME_MS2I(100));
    // Checking if a timeout has occurred.
    if(tkn != MSG_TIMEOUT)
      sdPut(&SD1, tkn);    // Not a timeout-> forward to GNSS
    }
    */


   // myprintf(bsp2, "%.3f %.3f %.3f\n\r", adc_get_temp_internal(), adc_get_temp_heater(), adc_get_current());



   // Getting data from Serial Driver with a timeout.
    msg_t tkn = sdGetTimeout(&SD2, TIME_MS2I(1000));
    // Checking if a timeout has occurred.
    if(tkn != MSG_TIMEOUT) {
      // Not a timeout. Echoing the character to improve user experience.
      sdPut(&SD2, tkn);
      //sdWrite(&SD2, (uint8_t*)"\r\n", 2U);
      if(tkn == '0'){
        myprintf("  Disable heater\n");
        heater_disable();
      } else if(tkn == '1'){
        myprintf("Enable heater..\n");
        heater_setTempDegC(50.0);
      } else if(tkn == '2'){
        myprintf("Beep\n");
        beep_ms = 10;
      }
    }
    // No sleep needed here. This thread releases the CPU onsdGetTimeout.

  }
}


/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThdBlinker, 128);
static THD_FUNCTION(ThdBlinker, arg) {
  (void)arg;
  chRegSetThreadName("blinker");
  chThdSleepMilliseconds(100);
  myprintf("ThdBlinker\n");

  for(float i=150; i>30; i=i*0.9){
    palSetPad(GPIOB, GPIOB_LED1);
    palClearPad(GPIOC, GPIOC_LED2);
    chThdSleepMilliseconds(i);
    palClearPad(GPIOB, GPIOB_LED1);
    palSetPad(GPIOC, GPIOC_LED2);
    chThdSleepMilliseconds(i);
  }
  for(float i=30; i<150; i=i*1.1){
    palSetPad(GPIOB, GPIOB_LED1);
    palClearPad(GPIOC, GPIOC_LED2);
    chThdSleepMilliseconds(i);
    palClearPad(GPIOB, GPIOB_LED1);
    palSetPad(GPIOC, GPIOC_LED2);
    chThdSleepMilliseconds(i);
  }

  while (true) {
    palSetPad(GPIOB, GPIOB_LED1);
    palClearPad(GPIOC, GPIOC_LED2);
    chThdSleepMilliseconds(1000);
    palClearPad(GPIOB, GPIOC_LED2);
    palSetPad(GPIOC, GPIOB_LED1);
    chThdSleepMilliseconds(1000);
  }
}

/*
 * GNSS (UART1) receive and forward
 */
static THD_WORKING_AREA(waThdGNSS, 128);
static THD_FUNCTION(ThdGNSS, arg) {
  (void)arg;
  chRegSetThreadName("GNSS");
  myprintf("ThdGNSS\n");
#warning todo sent command to increase baudrate

  static const SerialConfig my_config =
  {
   9600,
   0,
   USART_CR2_STOP1_BITS,
   0
  };
  sdStart(&SD1, &my_config);


  while(true){
    /* Getting data from Serial Driver with a timeout. */
    msg_t tkn = sdGetTimeout(&SD1, TIME_MS2I(100));
    /* Checking if a timeout has occurred. */
    if(tkn != MSG_TIMEOUT) {
      /* Not a timeout-> forward*/

#warning GNSS disabled
      //sdPut(&SD2, tkn);
    }
  }
}

/*
 * Piezo beeper
 */

static THD_WORKING_AREA(waThdBeeper, 128);
static THD_FUNCTION(ThdBeeper, arg) {
  (void)arg;
  myprintf("ThdBeeper\n");

  while(true){

    if(beep_ms){
      systime_t start = chVTGetSystemTimeX();
      systime_t end = chTimeAddX(start, TIME_MS2I(beep_ms));
      while (chTimeIsInRangeX(chVTGetSystemTimeX(), start, end)) {
        piezo_toggle();
        chThdSleepMilliseconds(1);
      }
      beep_ms = 0;
    }
    chThdSleepMilliseconds(10);
  }
}

static THD_WORKING_AREA(waThdCntr, 128);
static THD_FUNCTION(ThdCntr, arg) {
  (void)arg;
  ThdCntrFunc();
}

static THD_WORKING_AREA(waThdDisp, 128);
static THD_FUNCTION(ThdDisp, arg) {
  (void)arg;
  ThdDispFunc();
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

  chMtxObjectInit(&mutex_bsp2);

  heater_init();

  /*
   * Create threads
   */

  chThdCreateStatic(waThdBlinker, sizeof(waThdBlinker), NORMALPRIO, ThdBlinker, NULL);
  chThdCreateStatic(waThdSerial, sizeof(waThdSerial), NORMALPRIO, ThdSerial, NULL);
  chThdCreateStatic(waThdBeeper, sizeof(waThdBeeper), NORMALPRIO, ThdBeeper, NULL);
  chThdCreateStatic(waThdGNSS, sizeof(waThdGNSS), NORMALPRIO, ThdGNSS, NULL);
  chThdCreateStatic(waThdCntr, sizeof(waThdCntr), NORMALPRIO, ThdCntr, NULL);
  //chThdCreateStatic(waThdDisp, sizeof(waThdDisp), NORMALPRIO, ThdDisp, NULL);



  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  myprintf("Thdmain\n");

  while (true) {
    //get_temp_internal();

    chThdSleepMilliseconds(500);
  }
}
