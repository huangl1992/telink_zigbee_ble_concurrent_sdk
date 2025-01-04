/*
 * @Author: xiehuawei xiehuawei@leedarson.com
 * @Date: 2024-05-30 16:47:55
 * @LastEditors: xiehuawei xiehuawei@leedarson.com
 * @LastEditTime: 2024-06-05 16:26:00
 * @FilePath: /X_matter_zigbee_concurrent_lighting/matter_zigbee_esp32h2_light/application/lighting_cbb/bsp/common/lds_driver_common.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef _LDS_DRIVER_COMMON_H_
#define _LDS_DRIVER_COMMON_H_
#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

#include "lds_error_codes.h"

#define LDS_WEAK __attribute__ ((weak))

LDS_WEAK uint16_t ldsTokenWwOutputLimit(void);

LDS_WEAK uint16_t ldsTokenCwOutputLimit(void);

LDS_WEAK uint16_t ldsTokenMediumOutputLimit(void);

LDS_WEAK uint16_t ldsDeviceAdcVoltageGet(void);

LDS_WEAK uint16_t ldsMfgTokenDriverMaxDutyCycle(void);

LDS_WEAK float ldsGetTrfCurrentFac(void);

//lds_status_t ldsDriverCommonWrite(float *percent);
lds_status_t ldsDriverCommonWrite(float *percent, bool flag);
lds_status_t ldsDriverCommonInit(void);
bool ldsGetDriverTypeIsPwm(void);

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _LDS_DRIVER_COMMON_H_
