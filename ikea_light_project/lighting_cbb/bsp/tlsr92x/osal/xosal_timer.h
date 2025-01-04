/*
 * @File: Do not edit
 * @FilePath: /workspace/lighting_cbb/osal/zephyr/xosal_timer/xosal_timer.h
 * @Descripttion: 
 * @Author: huangl
 * @Date: 2024-05-10 16:59:17
 * @par Copyright: Copyright (c) Leedarson 2000-2020. All rights reserved.
 * @history: 
 * @ LastEditors: huangl
 * @ LastEditTime: Do not Edit
 * @ version: V1.00.00
 * @ Modification: Create file
 */

#ifndef _XOSAL_TIMER_H_
#define _XOSAL_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tl_common.h"


#define MAX_DELAY   		10
#define TICK_PERIOD_MS		1

#define XTICK                (10)                /* unit:ms */
#define XMSEC                (1)                 /* 1 millisecond */
#define XSECOND              (1000 * XMSEC)      /* 1 second */
#define XMINUTE              (60 * XSECOND)      /* 1 minute */
#define XHOUR                (60 * XMINUTE)      /* 1 hour */

typedef struct ev_timer_event_t lds_timer_t;
typedef struct ev_timer_event_t lds_timer_handle_t;
typedef void (*lds_timer_callback_t)(lds_timer_handle_t callback);

/**
 * @brief: 
 * @Param: 
 * @return {*}
 * @Date: 2024-05-23 16:57:45
 * @Author: huangl
 * @Modification: Create file
 */
bool ldsTimerCreate(lds_timer_t *timer, const char * const pcTimerName, uint32_t period, uint8_t one_shot,
						void *arg, lds_timer_callback_t cb);

/**
 * @brief: 
 * @Param: 
 * @return {*}
 * @Date: 2024-05-23 16:58:08
 * @Author: huangl
 * @Modification: Create file
 * @param {lds_timer_t} *timer
 * @param {uint32_t} tick
 */
bool ldsTimerStart(lds_timer_t *timer, uint32_t xTicksToWait, uint32_t period, uint8_t one_shot);

/**
 * @brief: 
 * @Param: 
 * @return {*}
 * @Date: 2024-05-23 16:57:53
 * @Author: huangl
 * @Modification: Create file
 * @param {lds_timer_t} *timer
 */
bool ldsTimerStop(lds_timer_t *timer, uint32_t tick);

bool ldsTimerDelete(lds_timer_t *timer, uint32_t tick);

uint32_t ldsGetPeriod(lds_timer_t *timer, uint32_t tick);

uint32_t ldsTimerGetPeriod(const lds_timer_t *timer);

bool ldsTimerChangePeriod(lds_timer_t *timer, uint32_t period, uint32_t tick_wait);

/**
 * @brief: 
 * @Param: 
 * @return {*}
 * @Date: 2024-05-23 16:57:58
 * @Author: huangl
 * @Modification: Create file
 * @param {uint32_t} ms
 */
void ldsDelayTime(uint32_t delay_ms);

/**
 * @brief: 
 * @Param: 
 * @return {*}
 * @Date: 2024-05-23 16:58:02
 * @Author: huangl
 * @Modification: Create file
 */
uint32_t ldsTimeGetTick(void);

uint32_t ldsTaskGetTickCount(void);

uint32_t ldsGetCurrentTimeMs(void);

/**
 * @brief:
 * @Param:
 * @return {*}
 * @Date: 2024-05-30 16:48:17
 * @Author: huangl
 * @Modification: Create file
 * @param {lds_timer_t} *timer
 */
//void *ldsTimerGetTimerID(lds_timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif
