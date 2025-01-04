/*
 * @Author: chenxiaoqian chenxiaoqian@leedarson.com
 * @Date: 2024-05-23 17:36:19
 * @LastEditors: chenxiaoqian chenxiaoqian@leedarson.com
 * @LastEditTime: 2024-11-25 14:41:11
 * @FilePath: /lighting_cbb/components/lds_color_algorithm/inc/lds_color_algorithm.h
 * @Description: RGB algorithm module 
 */

#ifndef COMPONENT_LDS_COLOR_ALGORITHM_INC_LDS_COLOR_ALGORITHM_H_
#define COMPONENT_LDS_COLOR_ALGORITHM_INC_LDS_COLOR_ALGORITHM_H_

#include <stdio.h>
#include <stdint.h>
#include "../../lds_color_conversion/inc/lds_color_conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LDS_LIGHT_CALIBRATION_COEFF_MODE_DEFAULT 0  // Default
#define LDS_LIGHT_CALIBRATION_COEFF_MODE_X 1

#define LDS_LIGHT_APPLY_POWER_LIMIT_MODE_DEFAULT 0    // Default
#define LDS_LIGHT_APPLY_POWER_LIMIT_MODE_X 1

#define LDS_COLOR_ALGORITHM_RGBW_3_WAYS 3
#define LDS_COLOR_ALGORITHM_RGBW_4_WAYS 4
#define LDS_COLOR_ALGORITHM_RGBW_5_WAYS 5

// Light PWM ratio and power calculated by light info and color point
typedef struct {
  float r_ratio;      // Red LED PWM ratio, 1.0 is 100%
  float g_ratio;      // Green
  float b_ratio;      // Blue
  float w1_ratio;     // White 1
  float w2_ratio;     // White 2
  float rgb_power;    // total power of R, G, and B LEDs
  float total_power;  // total power of all LEDs
} lds_light_pwm_t;

// LED specification
typedef struct {
  uint8_t led_type;  // led type like R LED, G LED, etc.
  float max_power;   // max power output for LED
} lds_led_spec_t;

// LED information
typedef struct {
  lds_xy_t xy;  // CIE 1931 xy
  float Y;      // brightness
  lds_led_spec_t led_spec;
} lds_led_info_t;

// calculated using light param and light calibration coefficients
typedef struct {
  lds_led_info_t r;   // Red LED info
  lds_led_info_t g;   // Green
  lds_led_info_t b;   // Blue
  lds_led_info_t w1;  // White 1
  lds_led_info_t w2;  // White 2
  float rgb_power_limit;
  float total_power_limit;
} lds_light_info_t;

// light algorithm settings
typedef struct {
  uint8_t pwm_ways;                         // 4 ways or 5 ways
  uint8_t calibration_coeff_mode;           // calibration mode, default: Leedarson Algorithm
  uint8_t apply_power_limit_mode;           // apply power limit mode, default: Leedarson
} lds_light_alg_settings_t;

// LED charateristic coefficients
typedef struct {
  float t;  // led temperature compensation coefficient
  float c;  // led color coefficient at 0 degree celsius
} lds_led_coeff_t;


typedef struct {
  lds_led_coeff_t x;  // led x coefficient in CIE1931 color space
  lds_led_coeff_t y;  // led y coefficient in CIE1931 color space
  lds_led_coeff_t Y;  // led Y coefficient (brightness)
  lds_led_spec_t led_spec;
} lds_led_attr_t;

// From linear regression analysis, data fitting, data provided by lab.
typedef struct {
  lds_led_attr_t r;   // Red LED attribute
  lds_led_attr_t g;   // Green
  lds_led_attr_t b;   // Blue
  lds_led_attr_t w1;  // White LED 1
  lds_led_attr_t w2;  // White LED 2
  float rgb_power_limit;
  float total_power_limit;
} lds_light_param_t;

// LED xyY coefficients
typedef struct {
  float x;  // x calibration coefficient
  float y;  // y calibration coefficient
  float Y;  // Y calibration coefficient
} lds_led_calibration_coeff_t;

// calculated using light param and light state
typedef struct {
  lds_led_calibration_coeff_t r_coeff;   // Red LED calibration coefficient
  lds_led_calibration_coeff_t g_coeff;   // Green
  lds_led_calibration_coeff_t b_coeff;   // Blue
  lds_led_calibration_coeff_t w1_coeff;  // White 1
  lds_led_calibration_coeff_t w2_coeff;  // White 2
} lds_light_calibration_coeff_t;

typedef struct {
  uint8_t inited;
  uint8_t type;
  const lds_light_alg_settings_t* settings;
  const lds_light_param_t* param;
  const lds_light_calibration_coeff_t* coeff;
} lds_color_light_description_t;


enum { LDS_R_LED = 0, LDS_G_LED, LDS_B_LED, LDS_W1_LED, LDS_W2_LED, LDS_MIX_LED };

lds_light_calibration_coeff_t *lds_light_calibration_coeff_get(void);

lds_light_info_t *lds_light_source_param_get(void);

/**
 * @brief Get light parameters
 * @param [out]  info: light parameters
 * @return status
 * */
lds_status_t lds_get_light_param( lds_light_info_t* info);


/**
 * @brief update light param 
 * @param [in] celsius: temperature
 * @return status.
 **/
lds_status_t lds_light_xyY_compute(const float celsius);

/**
 * @brief Get light algorithm setting
 * @param [out]  setting: RGBW light algorithm setting.
 * @return status.
 **/
lds_status_t lds_get_color_algorithm_setting(lds_light_alg_settings_t* setting);

/**
 * @brief Get RGBW light parameters from token first
 * @param [out]  param:RGBW light parameters.
 * @return status.
 **/
lds_status_t lds_rgbw_get_light_param_from_token(void* param);

/**
 * @brief Light algorithm initialization
 * @param [in]  settings: algorithm settings
 * @return status
 **/
lds_status_t lds_light_algorithm_init(const lds_light_alg_settings_t* settings);

lds_status_t lds_color_nonlinear_calibration(lds_light_pwm_t *pwm);

/**
 * @brief Convert xy coordinates to PWM
 * @param [in]  info  : Light information xyY and LED specification
 * @param [in]  point : Input CIE1931 xy coordinates
 * @param [out] pwm   : PWM output for color xy
 * @return status
 **/
lds_status_t lds_coordinates_get_pwm(const lds_light_info_t* info, const lds_xy_t* point, lds_light_pwm_t* pwm);

lds_status_t lds_get_light_param( lds_light_info_t* info);
/**
 * @brief LDS color algorithm xy to pwm conversion.
 * @param [in]  point: xy color point.
 * @param [out] pwm: output pwm.
 * @return status
 **/
lds_status_t lds_color_algorithm_xy_to_pwm(const lds_xy_t* point, lds_light_pwm_t* pwm);

/**
 * @brief LDS color algorithm init.
 * @param [in]  void.
 * @return status
 **/
lds_status_t lds_color_algorithm_init(void);

#ifdef __cplusplus
}
#endif

#endif  // COMPONENT_LDS_COLOR_ALGORITHM_INC_LDS_COLOR_ALGORITHM_H_