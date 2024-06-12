/*
 * gnss.c
 *
 *  Created on: 29.03.2024
 *      Author: patri
 */

#include "main.h"

static uint8_t forwarding = 0;
static uint8_t initialized = 0;

static const char NMEA_PUBX_VTG_DISABLE[] = {0x24, 0x50, 0x55, 0x42, 0x58, 0x2C, 0x34, 0x30, 0x2C, 0x56, 0x54, 0x47, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2A, 0x35, 0x45, 0x0D, 0x0A};
static const char NMEA_PUBX_RMC_DISABLE[] = {0x24, 0x50, 0x55, 0x42, 0x58, 0x2C, 0x34, 0x30, 0x2C, 0x52, 0x4D, 0x43, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2A, 0x34, 0x37, 0x0D, 0x0A};
static const char NMEA_PUBX_GGA_DISABLE[] = {0x24, 0x50, 0x55, 0x42, 0x58, 0x2C, 0x34, 0x30, 0x2C, 0x47, 0x47, 0x41, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2A, 0x35, 0x41, 0x0D, 0x0A};
static const char NMEA_PUBX_GLL_DISABLE[] = {0x24, 0x50, 0x55, 0x42, 0x58, 0x2C, 0x34, 0x30, 0x2C, 0x47, 0x4C, 0x4C, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2A, 0x35, 0x43, 0x0D, 0x0A};
static const char NMEA_PUBX_GSV_DISABLE[] = {0x24, 0x50, 0x55, 0x42, 0x58, 0x2C, 0x34, 0x30, 0x2C, 0x47, 0x53, 0x56, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2A, 0x35, 0x39, 0x0D, 0x0A};
static const char NMEA_PUBX_GSA_DISABLE[] = {0x24, 0x50, 0x55, 0x42, 0x58, 0x2C, 0x34, 0x30, 0x2C, 0x47, 0x53, 0x41, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x2A, 0x34, 0x45, 0x0D, 0x0A};
static const char ACK[] = {0xB5, 0x62, 0x05, 0x01}; //without id and checksum
static const char CFG_BAUD230400[] = {0xB5, 0x62, 0x06, 0x8A, 0x0C, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x52, 0x40, 0x00, 0x84, 0x03, 0x00, 0xB8, 0xFB};

void configSend(const char* s, int len){
  for(int i = 0; i<len; ++i){
    sdPut(&SD1, s[i]);
  }
}

#define LEN(x)  (sizeof(x) / sizeof((x)[0]))
#define CONFSEND(x) (configSend(x, LEN(x)))

void gnssDisablePeriodics(void){
  CONFSEND(NMEA_PUBX_GSA_DISABLE);
  CONFSEND(NMEA_PUBX_GSV_DISABLE);
  CONFSEND(NMEA_PUBX_GLL_DISABLE);
  CONFSEND(NMEA_PUBX_GGA_DISABLE);
  CONFSEND(NMEA_PUBX_RMC_DISABLE);
  CONFSEND(NMEA_PUBX_VTG_DISABLE);
}

void gnssInit(void){
  static const SerialConfig my_config = {9600,0,USART_CR2_STOP1_BITS,0};
  sdStart(&SD1, &my_config);

  chThdSleepMilliseconds(5000);
  msg_t tkn = sdGetTimeout(&SD1, TIME_MS2I(200)); //dummy read
  myprintf("ThdGNSS wait for GNSS ready\n");
  do {
    tkn = sdGetTimeout(&SD1, TIME_MS2I(200));
  }while(tkn != MSG_TIMEOUT); //wait until GNSS sends something -> is ready
  myprintf("ThdGNSS GNSS ready!?\n");

  myprintf("ThdGNSS change GNSS baudrate to 230400\n");
  CONFSEND(CFG_BAUD230400);

  myprintf("ThdGNSS change GNSS baudrate to 230400 two times! why?\n");
  CONFSEND(CFG_BAUD230400);
#warning why ist two times programming necessary?

  myprintf("ThdGNSS change mcu baudrate to 230400\n");
  sdStop(&SD1);
  static const SerialConfig my_config2 = {230400,0,USART_CR2_STOP1_BITS,0};
  sdStart(&SD1, &my_config2);

  chThdSleepMilliseconds(10);
 // gnssDisablePeriodics();
  initialized = 1;

  //  char response[9] = {0};
  //  do{
  //    tkn = sdGetTimeout(&SD1, TIME_MS2I(100));
  //    if(tkn == MSG_TIMEOUT) break;
  //    response[0] = tkn;
  //  }while(response[0] != 0xB5); //synchronize to start of UBX message
  //
  //  for(int i = 1; i<8; ++i){
  //    tkn = sdGetTimeout(&SD1, TIME_MS2I(100));
  //    if(tkn == MSG_TIMEOUT) break;
  //    response[i] = tkn;
  //  }
  //  myprintf("response: %s\n", response);
  //  if(!strncmp(response, ACK, 4)) baudrateChanged = 1;
}

void ThdGNssFunc(void){
  chRegSetThreadName("GNSS");
  myprintf("ThdGNSS\n");

  gnssInit();

  while(true){
    // Getting data from Serial Driver with a timeout.
    msg_t tkn = sdGetTimeout(&SD1, TIME_MS2I(100));
    // Checking if a timeout has occurred.
    if((tkn != MSG_TIMEOUT) && forwarding) {
      // Not a timeout-> forward
      sdPut(&SD2, tkn);
    }
  }
}

void gnss_forwardingEnable(void){
  forwarding = 1;
}

void gnss_forwardingDisable(void){
  forwarding = 0;
}

uint8_t gnss_forwardingEnabled(void){
  return forwarding;
}

uint8_t gnss_initialized(void){
  return initialized;
}

uint32_t gnss_getTimepulses(void){
  return timer_getTimepulses();
}
