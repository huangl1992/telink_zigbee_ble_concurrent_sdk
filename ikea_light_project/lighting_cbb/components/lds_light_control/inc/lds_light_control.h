/*
 * @Author: chenkunlin chenkunlin@leedarson.com
 * @Date: 2024-05-30 16:20:07
 * @LastEditors: chenkunlin chenkunlin@leedarson.com
 * @LastEditTime: 2024-06-07 09:58:11
 * @FilePath: /chenkl/lighting_cbb_dev/components/lds_light_control/inc/lds_light_control.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef COMPONENTS_LDS_LIGHT_CONTROL_H_
#define COMPONENTS_LDS_LIGHT_CONTROL_H_

#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include "lds_log.h"

#include "lds_device_config.h"

typedef struct 
{
#if defined(DIMMABLE_LIGHT)
    float Dim_channel;
#elif defined(COLORTEMPERATURE_LIGHT)
    float Warm_channel;
    float Cold_channel;
#elif defined(EXTENDEDCOLOR_LIGHT)
  float R_channel;
  float G_channel;
  float B_channel;
  float W_channel;
#ifdef RGBTW
  float W2_channel;
#endif
#endif
} lds_bulb_pwm_percent_t;

typedef struct 
{
#if defined(DIMMABLE_LIGHT)
    bool currentOnOff;
    uint8_t currentLevel;
    uint32_t transitionTime;
#elif defined(COLORTEMPERATURE_LIGHT)
    bool currentOnOff;
    uint8_t currentLevel;
    uint8_t currentColorMode;
    uint16_t currentColorTempMired;
    uint16_t currentX;
    uint16_t currentY;
    uint32_t transitionTime;
#elif defined(EXTENDEDCOLOR_LIGHT)
    bool currentOnOff;
    uint8_t currentLevel;
    uint8_t currentColorMode;
    uint16_t currentColorTempMired;
    uint16_t currentX;
    uint16_t currentY;
    uint16_t currentEnhanceHue;
    uint8_t currentHue;
    uint8_t currentSaturation;
    uint32_t transitionTime;
#endif
} lds_light_control_state_t;

void onoff_attribute_change_handle(uint16_t attributeID, uint8_t type, uint16_t size, uint8_t * value);
void level_attribute_change_handle(uint16_t attributeID, uint8_t type, uint16_t size, uint8_t * value);
void color_attribute_change_handle(uint16_t attributeID, uint8_t type, uint16_t size, uint8_t * value);
void init_to_startup(uint8_t endpoint, bool isFactoryNew);
void initLightControlStateDefault();
void initLightControlState(uint8_t endpoint);
void ldsBulbDriverMinitrimCtrlMoveTo(lds_light_control_state_t * state);

void ldsInitMatterStartUp();

lds_light_control_state_t* lds_light_control_state_get(void);

void lds_light_control_set(lds_light_control_state_t light_state_set);

void lds_light_control_set_currentOnOff(bool currentOnOff);
void lds_light_control_set_currentLevel(uint8_t currentLevel);

#if (defined COLORTEMPERATURE_LIGHT) || (defined EXTENDEDCOLOR_LIGHT)
void lds_light_control_set_currentColorMode(uint8_t currentColorMode);
void lds_light_control_set_currentColorTempMired(uint16_t currentColorTempMired);
void lds_light_control_set_currentX(uint16_t currentX);
void lds_light_control_set_currentY(uint16_t currentY);
#endif

#if defined(EXTENDEDCOLOR_LIGHT)
void lds_light_control_set_currentHue(uint8_t currentHue);
void lds_light_control_set_currentSaturation(uint8_t currentSaturation);
#endif

void lds_light_control_set_transitionTime(uint32_t transitionTime);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // COMPONENTS_LDS_LIGHT_CONTROL_H_


