/*
 * @Author: xiehuawei xiehuawei@leedarson.com
 * @Date: 2024-05-30 16:47:55
 * @LastEditors: xiehuawei xiehuawei@leedarson.com
 * @LastEditTime: 2024-06-20 16:58:30
 * @FilePath: /X_matter_zigbee_concurrent_lighting/matter_zigbee_esp32h2_light/application/lighting_cbb/bsp/common/lds_driver_common.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef _LDS_DRIVER_COMMON_H_
#define _LDS_DRIVER_COMMON_H_
#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

#include "lds_error_codes.h"
//#include "lds_power_on_count.h"
#include "lds_light_control.h"
#if defined(EXTENDEDCOLOR_LIGHT)
#include "lds_color_algorithm.h"
#endif

#ifndef LDS_DEFAULT_VALUE
#define LDS_DEFAULT_VALUE        10000
#endif

#define LDS_WEAK __attribute__ ((weak))

typedef enum {
    DRIVER_PWM = 0,
    DRIVER_I2C,
    DRIVER_NUM,
}driver_type;

LDS_WEAK uint16_t ldsTokenWwOutputLimit(void);
LDS_WEAK uint16_t ldsTokenCwOutputLimit(void);
LDS_WEAK uint16_t ldsTokenMediumOutputLimit(void);
LDS_WEAK uint16_t ldsMfgTokenDriverMaxDutyCycle(void);

lds_status_t ldsDriverCommonWrite(float *percent);
lds_status_t ldsDriverCommonInit(void);

int ldsFlashPowerOnCountCommonRead(power_on_count_data_save_t *data);
int ldsFlashPowerOnCountCommonWrite(power_on_count_data_save_t *data);
void ldsSystemCommonFactoryReset();
void ldsSystemCommonRestart();
void ldsSystemCommonMatterStartUp(lds_light_control_state_t * state);
#if (defined EXTENDEDCOLOR_LIGHT)
lds_status_t ldsSystemCommonLightSourceParamTokenGet(lds_light_param_t * param);
#endif
bool ldsGetDriverTypeIsPwm(void);

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _LDS_DRIVER_COMMON_H_