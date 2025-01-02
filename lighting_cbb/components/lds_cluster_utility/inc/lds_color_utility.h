/*
 * @Author: chenkunlin chenkunlin@leedarson.com
 * @Date: 2024-05-28 11:12:59
 * @LastEditors: chenkunlin chenkunlin@leedarson.com
 * @LastEditTime: 2024-05-30 16:20:55
 * @FilePath: /chenkl/lighting_cbb_color_level/components/lds_cluster_utility/inc/lds_color_utility.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _COMPONENT_LDS_COLOR_UTILITY_
#define _COMPONENT_LDS_COLOR_UTILITY_

#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include "lds_error_codes.h"

#define LDS_UTIL_COLOR_CONTROL_UNDEFINED_TRANSITION_TIME 0xFFFF
#define LDS_UTIL_COLOR_CONTROL_COLOR_TEMP_LEVEL_MIN_MIREDS_DEFAULT 0x0172
#define LDS_UTIL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MIN_DEFAULT 0x00FA
#define LDS_UTIL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MAX_DEFAULT 0x01C6

lds_status_t lds_color_util_read_temp_phy_max(uint8_t endpoint, uint16_t* colorTemperatureMireds);
lds_status_t lds_color_util_read_temp_phy_min(uint8_t endpoint, uint16_t* colorTemperatureMireds);
lds_status_t lds_color_util_read_temp_couple_min(uint8_t endpoint, uint16_t* colorTemperatureMireds);
lds_status_t lds_color_util_read_temp(uint8_t endpoint, uint16_t* colorTemperatureMireds);
lds_status_t lds_color_util_write_temp(uint8_t endpoint, uint16_t colorTemperatureMireds);
lds_status_t lds_color_util_update_temp(uint8_t endpoint, uint16_t colorTemperatureMireds);
lds_status_t lds_color_util_read_xy(uint8_t endpoint, uint16_t* colorX, uint16_t* colorY);
lds_status_t lds_color_util_write_xy(uint8_t endpoint, uint16_t colorX, uint16_t colorY);
lds_status_t updateColorX(uint8_t endpoint, uint16_t colorX);
lds_status_t updateColorY(uint8_t endpoint, uint16_t colorY);
lds_status_t lds_color_util_update_xy(uint8_t endpoint, uint16_t colorX, uint16_t colorY);
lds_status_t lds_color_util_read_hue(uint8_t endpoint, uint8_t* hue);
lds_status_t lds_color_util_read_saturation(uint8_t endpoint, uint8_t* saturation);
lds_status_t lds_color_util_read_hue_saturation(uint8_t endpoint, uint8_t* hue, uint8_t* saturation);
lds_status_t lds_color_util_write_hue_saturation(uint8_t endpoint, uint8_t hue, uint8_t saturation);
lds_status_t lds_color_util_update_hue(uint8_t endpoint, uint8_t hue);
lds_status_t lds_color_util_update_saturation(uint8_t endpoint, uint8_t saturation);
lds_status_t lds_color_util_update_hue_saturation(uint8_t endpoint, uint8_t hue, uint8_t saturation);
lds_status_t lds_color_util_read_enhanced_hue(uint8_t endpoint, uint16_t* enhancedHue);
lds_status_t lds_color_util_read_enhanced_hue_saturation(uint8_t endpoint, uint16_t* enhancedHue, uint8_t* saturation);
lds_status_t lds_color_util_write_enhanced_hue_saturation(uint8_t endpoint, uint16_t enhancedHue, uint8_t saturation);
lds_status_t lds_color_util_update_enhanced_hue(uint8_t endpoint, uint16_t enhancedHue);
lds_status_t lds_color_util_update_enhanced_hue_saturation(uint8_t endpoint, uint16_t enhancedHue, uint8_t saturation);
lds_status_t lds_color_util_read_loop_active(uint8_t endpoint, uint8_t* active);
lds_status_t lds_color_util_read_loop_direction(uint8_t endpoint, uint8_t* direction);
lds_status_t lds_color_util_read_loop_time(uint8_t endpoint, uint16_t* time);
lds_status_t lds_color_util_read_loop_start_enhanced_hue(uint8_t endpoint, uint16_t* start_ehue);
lds_status_t lds_color_util_read_loop_stored_enhanced_hue(uint8_t endpoint, uint16_t* stored_ehue);
lds_status_t lds_color_util_update_loop_active(uint8_t endpoint, uint8_t active);
lds_status_t lds_color_util_update_loop_direction(uint8_t endpoint, uint8_t direction);
lds_status_t lds_color_util_update_loop_time(uint8_t endpoint, uint16_t time);
lds_status_t lds_color_util_update_loop_start_enhanced_hue(uint8_t endpoint, uint16_t start_ehue);
lds_status_t lds_color_util_update_loop_stored_enhanced_hue(uint8_t endpoint, uint16_t stored_ehue);
lds_status_t lds_color_util_read_mode_conditionally(uint8_t endpoint, uint8_t* mode);
lds_status_t lds_color_util_update_mode_conditionally(uint8_t endpoint, uint8_t mode);
lds_status_t lds_color_util_startup_read_color_temp(uint8_t endpoint, uint16_t* colorTemperatureMireds);
lds_status_t lds_color_util_startup_color_temp(uint8_t endpoint);
lds_status_t lds_color_util_read_options(uint8_t endpoint, uint8_t* options);
lds_status_t lds_color_util_read_remaining_time(uint8_t endpoint, uint16_t* remaining_time);
lds_status_t lds_color_util_update_remaining_time(uint8_t endpoint, uint16_t remaining_time);
lds_status_t lds_color_util_update_remaining_time_ms(uint8_t endpoint, uint32_t remaining_time);


#ifdef __cplusplus
}
#endif  // __cplusplus

#endif