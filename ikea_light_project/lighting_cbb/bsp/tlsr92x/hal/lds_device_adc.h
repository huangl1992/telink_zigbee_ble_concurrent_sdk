#ifndef _LDS_DEVICE_ADC_H_
#define _LDS_DEVICE_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lds_includes.h"

void ldsDeviceAdcInit(void);

uint16_t ldsDeviceAdcVoltageGet(void);

void ldsRfCalibrationFreqOffsetCheck(void);

#ifdef __cplusplus
}
#endif
#endif
