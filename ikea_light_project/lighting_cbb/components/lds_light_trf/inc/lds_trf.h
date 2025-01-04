/*
 * @File: Do not edit
 * @brief: 
 * @author: huangl
 * @Date: 2024-04-28 13:55:23
 * @Copyright: Copyright (c) Leedarson 2000-2020. All rights reserved.
 * @par: History
 * @1.Date: 
 * @version: v1.0.0
 * @Modification: Create file
 */


#ifndef _LDS_TRF_H_
#define _LDS_TRF_H_

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define DEF_CURRENT_TEMP    (25)            // default current init temperature
#define DEF_ALARM_TEMP      (105)           // default alarm init temperature
#define TRF_MIN_TEMP        (20)            // Min NTC detection temperature
#define TRF_MAX_TEMP        (120)           // Max NTC detection temperature
#define SAMPLE_MAX_COUNT    (20)            // adc sample max count
#define TEMP_TEN_STEP       (10)
#define TEMP_FIVE_STEP      (5)
#define DEF_FAC_MAX         (1.0)           // fac max value
#define DEF_FAC_MIN         (0.7)           // fac min value
#define FAC_MAX_RECOVERY    (0.95)          // trigger ntc, fac max recovery
#define FAC_NINETY_PERCENT  (0.9)
#define FAC_FIVE_PERCENT    (0.05)
#define FAC_TEN_PERCENT     (0.1)

#define SCALE_VALUE         (10000)
#define FAC_MAX_VALUE       (SCALE_VALUE * DEF_FAC_MAX) 
#define FAC_9000_VALUE      (SCALE_VALUE * FAC_NINETY_PERCENT)

#define ONE_MIN_COUNT       (60 / 3)
#define FOUR_MIN_COUNT      (240 / 3)

#define TIME_10_MS          (10)
#define TIME_50_MS          (50)


typedef enum 
{
	XT_TEMPERATURE_CHANGE_EVT = 0,
	XT_TEMPERATURE_ALARM_EVT,
} xt_trf_event_e;

typedef struct
{   
    bool three_min_timeout;                 // 3min wait timeout
    uint16_t count;                         // timer count
    uint16_t three_sec_count;               //
    uint8_t current_temp;                   // current temperature
    uint8_t alarm_temp;                     // light alarm termerature
    float current_fac;                      // current fac value
    float target_fac;                       // calculated current target fac value
    float step_fac;                         // fac changes step by step in 1min
    float alarm_pwm_limit;                  // Trigger NTC alarm with minimum pwm power limit output       
    bool (*ldsGetOnoffState)(void);         // Get light onoff status
    uint16_t (*ldsGetAdcValue)(void);       // Get adc value
    void (*eventCallback)(uint8_t event, uint8_t *params);   // event callback function
} lds_trf_t;

//void ldsTrfInit(void);
void ldsTrfInit(lds_trf_t *temp);

void ldsDeivceNtcInit(void);

lds_trf_t *ldsTrfParamsGet(void);

void ldsTrfEventHandler(void);

uint8_t ldsTrfVoltageChangeTemperature(uint16_t voltage);

uint8_t ldsDeviceCurrentTemperature(void);

float ldsGetTrfCurrentFac(void);

void ldsTrfTickRun(void);

bool ldsDeviceCurrentOnoffState(void);

void ldsDeviceNtcEventCb(uint8_t event, uint8_t *param);

#ifdef __cplusplus
}
#endif
#endif
