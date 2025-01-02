/*
 * @Author: chenxiaoqian chenxiaoqian@leedarson.com
 * @Date: 2024-05-27 09:15:29
 * @LastEditors: chenxiaoqian chenxiaoqian@leedarson.com
 * @LastEditTime: 2024-11-18 15:26:52
 * @FilePath: /lighting_cbb/components/lds_color_algorithm/inc/lds_color_algorithm_config.h
 * @Description: config params for RGB algorithm
 */
#ifndef COMPONENT_LDS_COLOR_ALGORITHM_INC_LDS_COLOR_ALGORITHM_CONFIG_H_
#define COMPONENT_LDS_COLOR_ALGORITHM_INC_LDS_COLOR_ALGORITHM_CONFIG_H_

#include "../inc/lds_color_algorithm.h"
#include "lds_device_config.h"

#ifdef __cplusplus
extern "C" {
#endif

//if LDS_COLOR_ALGORITHM_RGBW_5_WAYS: config cct value of white points for algorthm
#define LIGHT_WW 2100  //WW is 2200k, but the margin needs to be reserved,  SDCM < 6
#define LIGHT_CW 7100   //CW is 6500k, but the margin needs to be reserved, SDCM < 5

static const lds_light_alg_settings_t g_light_settings_device = {
#ifdef RGBW
    .pwm_ways = LDS_COLOR_ALGORITHM_RGBW_4_WAYS,
#else
	.pwm_ways = LDS_COLOR_ALGORITHM_RGBW_5_WAYS,
#endif
    .calibration_coeff_mode = LDS_LIGHT_CALIBRATION_COEFF_MODE_DEFAULT,
    .apply_power_limit_mode = LDS_LIGHT_APPLY_POWER_LIMIT_MODE_DEFAULT};

static const lds_light_param_t g_light_param_device = {
    {{0.00008320, 0.69812176}, {-0.00008330, 0.30188201}, {-0.09364494, 29.50962949}, {LDS_R_LED, 0.516}},
    {{0.00014720, 0.14668731}, {-0.00006244, 0.74770692}, {-0.03904745, 79.94683506}, {LDS_G_LED, 0.696}},
    {{-0.00001421, 0.12903926}, {0.00010448, 0.06765313}, {0.01727374, 16.70685209}, {LDS_B_LED, 0.72}},
    {{-0.00001299, 0.38632794},{-0.00015787, 0.38842535},{-1.60629065, 1116.58459741},{LDS_W1_LED, 8.64}},  // W1 = WW
    {{0.00001759, 0.45930284}, {-0.00010609, 0.42081251}, {-1.50345404, 1086.99345163}, {LDS_W2_LED, 8.64}}, // W1 = CW
    1.932,
    8.7};  // Jetstrom CWS 

#ifdef __cplusplus
}
#endif
#endif  // COMPONENT_LDS_COLOR_ALGORITHM_INC_LDS_COLOR_ALGORITHM_CONFIG_H_
