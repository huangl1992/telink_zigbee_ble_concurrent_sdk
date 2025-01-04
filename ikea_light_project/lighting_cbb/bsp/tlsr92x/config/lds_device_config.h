#ifndef _LDS_DEVICE_CONFIG_H_
#define _LDS_DEVICE_CONFIG_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include "app_cfg.h"

/**********************************************
** PWM channel config
**********************************************/

/***********************************************
*** light typedef
************************************************/
#define XT_FW_VERSION			"1.1.11"
#define XT_DATACODE				"20241228"

#define XT_LIGHT_A470			0
#define XT_LIGHT_A1055_CWS		1
#define XT_LIGHT_A1055_WS		2
#define XT_LIGHT_A1521_WS		3
#define XT_LIGHT_GU10_CWS		4
#define XT_LIGHT_GU10_WS		5
#define XT_LIGHT_P45_WS			6
#define XT_LIGHT_P45_CWS		7

/***********************************************
*** light driver typedef
************************************************/

/***********************************************
*** light pwm 2MOS / DCDC typedef
************************************************/
//#define XT_LIGHT_DRIVER_PWM_2MOS    0
//#define XT_LIGHT_DRIVER_PWM_DCDC    1

#define XT_LIGHT_TYPE				XT_LIGHT_A470 //XT_LIGHT_A1055_CWS //XT_LIGHT_A470

//#define DIMMABLE_LIGHT
#define TELINK_DEVICE
#ifndef LDS_NTC_ENABLE
#define LDS_NTC_ENABLE
#endif

#ifndef LDS_I2C_CHANGE_ENABLE
//#define LDS_I2C_CHANGE_ENABLE
#endif

//#define LDS_UART_ENABLE

#if (XT_LIGHT_TYPE == XT_LIGHT_GU10_WS) || (XT_LIGHT_TYPE == XT_LIGHT_P45_WS) \
|| (XT_LIGHT_TYPE == XT_LIGHT_A1055_WS) || (XT_LIGHT_TYPE == XT_LIGHT_A1521_WS) || (XT_LIGHT_TYPE == XT_LIGHT_A470)
#define COLORTEMPERATURE_LIGHT
#if (XT_LIGHT_TYPE == XT_LIGHT_A470) || (XT_LIGHT_TYPE == XT_LIGHT_B38_WS)
#ifndef PRECHARGE_ENABLE
#define PRECHARGE_ENABLE
#endif
#endif
#elif (XT_LIGHT_TYPE == XT_LIGHT_A1055_CWS) || (XT_LIGHT_TYPE == XT_LIGHT_GU10_CWS) || (XT_LIGHT_TYPE == XT_LIGHT_P45_CWS)
#define EXTENDEDCOLOR_LIGHT
#define RGBTW
#endif

#define APP_LIGHT_USER_MODE_EN		1
//#define LDS_DEBUG					1

#if (defined EXTENDEDCOLOR_LIGHT)
#define LDS_DEFAULT_SCENES_NUMER_OF		9
#elif (defined COLORTEMPERATURE_LIGHT)
#define LDS_DEFAULT_SCENES_NUMER_OF		4
#endif

#if (defined COLORTEMPERATURE_LIGHT)
#define LED_DIM						GPIO_PA0 //GPIO_PE7//GPIO_PA2
#define LED_CCT						GPIO_PA2 //GPIO_PE6//GPIO_PA0

#define PWM_DIM_CHANNEL				1
#define PWM_DIM_CHANNEL_SET()		do {\
										pwm_set_pin(LED_DIM, PWM1); \
									} while(0)

#define PWM_CCT_CHANNEL				2
#define PWM_CCT_CHANNEL_SET()		do {\
										pwm_set_pin(LED_CCT, PWM2); \
									} while(0)

#define DIM_LIGHT_PWM_CHANNEL		PWM_DIM_CHANNEL
#define CCT_LIGHT_PWM_CHANNEL		PWM_CCT_CHANNEL

#define DIM_LIGHT_PWM_SET()			PWM_DIM_CHANNEL_SET()
#define CCT_LIGHT_PWM_SET()			PWM_CCT_CHANNEL_SET()

#elif (defined EXTENDEDCOLOR_LIGHT)
#define LED_R						GPIO_PE7
#define LED_G						GPIO_PE6		//GPIO_PD1
#define LED_B						GPIO_PD0
#define LED_DIM						GPIO_PA0

#define PWM_R_CHANNEL				1
#define PWM_R_CHANNEL_SET()			do {\
										pwm_set_pin(LED_R, PWM1); \
									} while(0)

#define PWM_G_CHANNEL				2
#define PWM_G_CHANNEL_SET()			do {\
										pwm_set_pin(LED_G, PWM2); \
									} while(0)

#define PWM_B_CHANNEL				3
#define PWM_B_CHANNEL_SET()			do {\
										pwm_set_pin(LED_B, PWM3); \
									} while(0)

#define PWM_DIM_CHANNEL				4
#define PWM_DIM_CHANNEL_SET()		do {\
										pwm_set_pin(LED_DIM, PWM4); \
									} while(0)

#if (defined RGBTW)
#define LED_CCT						GPIO_PA2

#define PWM_CCT_CHANNEL				5
#define PWM_CCT_CHANNEL_SET()		do {\
										pwm_set_pin(LED_CCT, PWM4); \
									} while(0)

#define R_LIGHT_PWM_CHANNEL			PWM_R_CHANNEL
#define G_LIGHT_PWM_CHANNEL			PWM_G_CHANNEL
#define B_LIGHT_PWM_CHANNEL			PWM_B_CHANNEL
#define DIM_LIGHT_PWM_CHANNEL		PWM_DIM_CHANNEL
#define CCT_LIGHT_PWM_CHANNEL		PWM_CCT_CHANNEL

#define R_LIGHT_PWM_SET()			PWM_R_CHANNEL_SET()
#define G_LIGHT_PWM_SET()			PWM_G_CHANNEL_SET()
#define B_LIGHT_PWM_SET()			PWM_B_CHANNEL_SET()
#define DIM_LIGHT_PWM_SET()			PWM_DIM_CHANNEL_SET()
#define CCT_LIGHT_PWM_SET()			PWM_CCT_CHANNEL_SET()
#endif
#endif

// DEBUG
#if (UART_PRINTF_MODE) || (TLKAPI_DEBUG_ENABLE && TLKAPI_DEBUG_CHANNEL == TLKAPI_DEBUG_CHANNEL_GSUART)
#if DUAL_MODE_WITH_MATTER
//	#define	DEBUG_INFO_TX_PIN	    GPIO_PB2//print
	#define	DEBUG_INFO_TX_PIN	    GPIO_PD2 // GPIO_PD2  //GPIO_PA6	//print
	#define BAUDRATE				115200
#else
	#define	DEBUG_INFO_TX_PIN	    GPIO_PE5//print
#endif
#endif

#define HAL_PWM_MAX_DUTY_CYCLE_COUNT 10000
//ADC pin set
#define XT_ADC_PIN		ADC_GPIO_PB1

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
#endif
