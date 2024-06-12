/*
 * gnss.h
 *
 *  Created on: 29.03.2024
 *      Author: patri
 */

#ifndef SOURCE_GNSS_H_
#define SOURCE_GNSS_H_

#include <stdint.h>

void gnssInit(void);
void ThdGNssFunc(void);
void gnss_forwardingEnable(void);
void gnss_forwardingDisable(void);
uint8_t gnss_forwardingEnabled(void);
uint8_t gnss_initialized(void);
uint32_t gnss_getTimepulses(void);

#endif /* SOURCE_GNSS_H_ */
