/*
 * plane.h
 *
 *  Created on: Feb 11, 2020
 *      Author: kostas
 */
#ifndef __PLANE_H
#define __PLANE_H

#define LANDING_LEFT_CH
#define LANDING_LEFT_TIM
#define LANDING_RIGHT_CH
#define LANDING_RIGHT_TIM
#define BEACON_CH
#define BEACON_TIM
#define STROBE_CH
#define STROBE_TIM
#define LOGO_CH
#define LOGO_TIM

#include <stdarg.h>

#include "tim.h"
#include "cli_static.h"
#include "cli_static_cmd.h"
#include "usbd_cdc_if.h"

typedef enum {
	airbus,
	boeing
}planeMaker_t;

typedef enum {
	pulsating,
	normal
}landingLights_t;

typedef struct {
	landingLights_t landing;
	uint8_t beacon;
	uint8_t strobe;
	uint8_t logo;
	planeMaker_t brand;
}planeType_t;

extern planeType_t myplane;
extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

void planeStart(void);
void CDCprintf(const char *fmt, ...);
void printf_valist(const char *fmt, va_list argp);

#endif
