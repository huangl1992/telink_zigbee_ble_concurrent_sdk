#ifndef _LDS_DRIVER_PWM_H_
#define _LDS_DRIVER_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "lds_error_codes.h"
#include "lds_device_config.h"

void ldsDriverPwmInit(void);

lds_status_t ldsDriverPwmWrite(const float *percent);

void ldsOnOffUpdate(bool onOff);

#ifdef __cplusplus
}
#endif 

#endif // _LDS_DRIVER_PWM_H_
