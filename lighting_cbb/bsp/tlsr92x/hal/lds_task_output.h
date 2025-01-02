#ifndef _LDS_TASK_OUTPUT_H_
#define _LDS_TASK_OUTPUT_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "lds_error_codes.h"
#include "lds_device_config.h"

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

//void DeviceOutputTaskUpdate(uint8_t index, float target_value, uint32_t delay_time, uint32_t tran_time, uint32_t step_time);
void ldsMinitrimStart(float *target_pwm, uint32_t transition_time_ms);

void ldsMinitrimTimerCreate(void);

#ifdef __cplusplus
}
#endif 

#endif
