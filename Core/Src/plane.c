/*
 * plane.c
 *
 *  Created on: Feb 11, 2020
 *      Author: Kostas
 */

#include "plane.h"

planeType_t myplane;

static void strb(void);
static void restoreState(void);

uint8_t cli_buf[128];
uint8_t packet_ready = 0;

void planeStart(void) {

	HAL_Delay(1000);
	CDC_Transmit_FS((uint8_t *)"Starting application...\r\n", 26);
	restoreState();
	myplane.brand = boeing;

	while(1){
		if(packet_ready == 0){
			strb();
		}else{
			cli_process_command((char *)UserRxBufferFS);
			packet_ready = 0;
		}

	}
}

static void restoreState(void){
	/*
	 * ToDo: Get the default state from flash
	 */
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
}

static void strb(void){
	if(myplane.brand == boeing){
		htim3.Instance->CCR1=100;
		htim3.Instance->CCR2=0;
		HAL_Delay(50);
		htim3.Instance->CCR1=0;
		HAL_Delay(450);
		htim3.Instance->CCR2=100;
		HAL_Delay(50);
		htim3.Instance->CCR2=0;
		HAL_Delay(450);
		htim3.Instance->CCR1=100;
		HAL_Delay(50);
		htim3.Instance->CCR2=0;
		htim3.Instance->CCR1=0;
		} else if(myplane.brand == airbus){
			htim3.Instance->CCR1=100;
			htim3.Instance->CCR2=0;
			HAL_Delay(50);
			htim3.Instance->CCR1=0;
			HAL_Delay(50);
			htim3.Instance->CCR1=100;
			HAL_Delay(50);
			htim3.Instance->CCR1=0;
			HAL_Delay(350);
			htim3.Instance->CCR2=100;
			HAL_Delay(50);
			htim3.Instance->CCR2=0;
			HAL_Delay(450);
			htim3.Instance->CCR1=100;
			HAL_Delay(50);
			htim3.Instance->CCR2=0;
			htim3.Instance->CCR1=0;
		}
}

void CDCprintf(const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  printf_valist(fmt, argp);
  va_end(argp);
}

void printf_valist(const char *fmt, va_list argp) {
  char string[APP_TX_DATA_SIZE];

  if (vsprintf(string, fmt, argp) > 0) //{
	  CDC_Transmit_FS((uint8_t*)string, strlen((const char*)string));
}
