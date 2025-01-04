/**
 * @brief minitrim
 * @file lds_driver_minitrim.h
 * @version 1.0
 * @author LDS
 * @date 2024-05-09 13:28:36
 * @par Copyright:
 * Copyright (c) Leedarson 2000-2024. All rights reserved.
 *
 * @history
 * 1.Date        : 2024-05-09 13:28:36
 *   Author      : LDS
 *   Modification: Created file
 */

#ifndef _LDS_DRIVER_MINITRIM_H_
#define _LDS_DRIVER_MINITRIM_H_

#include "stdint.h"
#include "xosal_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
#if defined(DIMMABLE_LIGHT)
    PWM_ID_DIM = 0,
#elif defined(COLORTEMPERATURE_LIGHT)
    PWM_ID_WARM_WHITE = 0,
    PWM_ID_COLD_WHITE,
#elif defined(EXTENDEDCOLOR_LIGHT)
    PWM_ID_RED = 0x00,
    PWM_ID_GREEN,
    PWM_ID_BLUE,
    PWM_ID_WHITE,   // warm
#ifdef RGBTW
    PWM_ID_WHITE2,  // cold
#endif
#endif
    PWM_ID_NUM,
} tePWMID_t;

bool ldsMinitrimIsProcessing();
void ldsMinitrimStop(void);
void ldsMinitrimStart(const float *pwm, uint32_t transitionTimeMs);
void ldsMinitrimInit(void);

void ldsPwmUpdateEndFlagSet(uint8_t flag);
uint8_t ldsPwmUpdateEndFlagGet(void);

#ifdef __cplusplus
}
#endif

#endif // _LDS_DRIVER_MINITRIM_H_