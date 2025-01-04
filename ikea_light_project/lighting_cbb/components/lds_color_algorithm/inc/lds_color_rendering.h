/*
 * @Author: chenxiaoqian chenxiaoqian@leedarson.com
 * @Date: 2024-05-23 17:36:08
 * @LastEditors: chenxiaoqian chenxiaoqian@leedarson.com
 * @LastEditTime: 2024-05-27 16:18:28
 * @FilePath: /lighting_cbb/components/lds_color_algorithm/inc/lds_color_rendering.h
 * @Description: RGB algorithm module
 */
#ifndef COMPONENT_LDS_COLOR_RENDERING_INC_LDS_COLOR_RENERING_H_
#define COMPONENT_LDS_COLOR_RENDERING_INC_LDS_COLOR_RENERING_H_

#include <stdbool.h>
#include "../inc/lds_color_algorithm.h"

#ifdef __cplusplus
extern "C" {
#endif

// RGB triangle top
typedef struct {
  lds_led_info_t r;  // Red
  lds_led_info_t g;  // Green
  lds_led_info_t b;  // Blue
} lds_rgb_top_t;

// RGB PWM ratio, power and efficacy
typedef struct {
  float r_ratio;  // Red LED PWM ratio, 1.0 is 100%
  float g_ratio;  // Green
  float b_ratio;  // Blue
  float max_support_power;
  float luminous_efficacy;
} lds_rgb_pwm_t;


/**
 * @brief Convert xy coordinates to PWM
 * @param [in]  info  : Light information xyY and LED specification
 * @param [in]  point : Input CIE1931 xy coordinates
 * @param [out] pwm   : PWM output for color xy
 * @return status
 **/
lds_status_t lds_coordinates_get_pwm(const lds_light_info_t* info, const lds_xy_t* point, lds_light_pwm_t* pwm);

#ifdef __cplusplus
}
#endif

#endif //COMPONENT_LDS_COLOR_RENDERING_INC_LDS_COLOR_RENERING_H_


