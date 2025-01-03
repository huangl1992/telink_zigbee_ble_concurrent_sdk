/********************************************************************************************************
 * @file    board_b92_S-LDT63S000A.h
 *
 * @brief   This is the header file for board_b92_S-LDT63S000A
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *			All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/

#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif


// LED
/***************************************************************
* LED_R			GPIO_PA0	//D4 -- red
* LED_G			GPIO_PA1	//D2 -- green
* LED_B			GPIO_PA2	//D1 -- blue
****************************************************************/
#if defined COLOR_RGB_SUPPORT && (COLOR_RGB_SUPPORT == 1)
#define LED_R						GPIO_PA0
#define LED_G						GPIO_PA1
#define LED_B						GPIO_PA2

#define PWM_R_CHANNEL				1	//PWM1
#define PWM_R_CHANNEL_SET()			do{\
										pwm_set_pin(LED_R, PWM1); \
									}while(0)

#define PWM_G_CHANNEL				3	//PWM3
#define PWM_G_CHANNEL_SET()			do{\
										pwm_set_pin(LED_G, PWM3); \
									}while(0)

#define PWM_B_CHANNEL				2	//PWM2
#define PWM_B_CHANNEL_SET()			do{\
										pwm_set_pin(LED_B, PWM2); \
									}while(0)

#define R_LIGHT_PWM_CHANNEL			PWM_R_CHANNEL
#define G_LIGHT_PWM_CHANNEL			PWM_G_CHANNEL
#define B_LIGHT_PWM_CHANNEL			PWM_B_CHANNEL
#define R_LIGHT_PWM_SET()			PWM_R_CHANNEL_SET()
#define G_LIGHT_PWM_SET()			PWM_G_CHANNEL_SET()
#define B_LIGHT_PWM_SET()			PWM_B_CHANNEL_SET()

#else
//PWM configuration, LED_R as warm light, LED_B as cool light.
#define LED_R						GPIO_PA0
#define LED_B						GPIO_PA2

#define PWM_R_CHANNEL				1	//PWM1
#define PWM_R_CHANNEL_SET()			do{\
										pwm_set_pin(LED_R, PWM1); \
									}while(0)

#define PWM_B_CHANNEL				2	//PWM2
#define PWM_B_CHANNEL_SET()			do{\
										pwm_set_pin(LED_B, PWM2); \
									}while(0)

#define WARM_LIGHT_PWM_CHANNEL		PWM_R_CHANNEL
#define COOL_LIGHT_PWM_CHANNEL		PWM_B_CHANNEL
#define WARM_LIGHT_PWM_SET()		PWM_R_CHANNEL_SET()
#define COOL_LIGHT_PWM_SET()		PWM_B_CHANNEL_SET()
#endif

#define VOLTAGE_DETECT_PIN			ADC_GPIO_PB1

// UART
#if ZBHCI_UART
	#error please configurate uart PIN!!!!!!
#endif

// DEBUG
#if (UART_PRINTF_MODE) || (TLKAPI_DEBUG_ENABLE && TLKAPI_DEBUG_CHANNEL == TLKAPI_DEBUG_CHANNEL_GSUART)
	#define	DEBUG_INFO_TX_PIN	    GPIO_PD2//print
	#define BAUDRATE				115200
#endif


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
