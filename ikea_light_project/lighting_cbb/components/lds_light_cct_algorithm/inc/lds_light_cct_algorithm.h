/*
 * @Author: xiehuawei xiehuawei@leedarson.com
 * @Date: 2024-05-22 17:52:58
 * @LastEditors: xiehuawei xiehuawei@leedarson.com
 * @LastEditTime: 2024-05-23 13:44:23
 * @FilePath: /X_matter_zigbee_concurrent_lighting/esp-matter/examples/light/light_app/lds_light_cct_algorithm.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef _LDS_LIGHT_CCT_ALGORITHM_H_
#define _LDS_LIGHT_CCT_ALGORITHM_H_
#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

#include <stdint.h>

#define LDS_ARRAY_SIZE(array)           (sizeof(array)/sizeof(array[0]))    ///< Counting arrays

typedef enum {
    WARM_W_R = 0,
    COLD_W_R,
    TW_R_NUM,
} teTWAttr_t;

typedef float twAttr_t[TW_R_NUM];

#pragma pack (1)
typedef enum {
    DRV_MOS = 0,      // MOS 管驱动
    DRV_DCDC,         // DCDC 驱动
} teCCTDRVMode_t;

typedef struct {
    teCCTDRVMode_t driveMode;
    uint16_t minColorTemp;              // minimum color temperature.
    uint16_t maxColorTemp;              // maximum color temperature.
    uint16_t defaultColorTemp;          // default color temperature.
    float minLevel;
    float defaultColorTempDutyCycle;    // default color temperature duty cycle.
} tsCCTAlgorithmParam_t;

typedef struct
{
    uint16_t  color_temp;
    float     p2200;
    float     p6500;
} tsCCTPercent_t;

typedef struct {
    tsCCTAlgorithmParam_t  cctAlgParam;
    tsCCTPercent_t  CCTPercent;
} tsLightingAlgorithmParam_t;

#pragma pack ()

void ldsLightingCCTAlgorithmInit(tsCCTAlgorithmParam_t  cctAlgParam);

void ldsCalculateTWPWMFromColorTemp(const uint16_t colorTemp,
                                    const uint8_t level,
                                    twAttr_t *twPWM);

uint16_t ldsDimmerPwmValueGet(void);

uint16_t ldsCCTAlgorithmGetColorTempMin(void);

uint16_t ldsCCTAlgorithmGetColorTempMax(void);

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _LDS_LIGHT_CCT_ALGORITHM_H_




