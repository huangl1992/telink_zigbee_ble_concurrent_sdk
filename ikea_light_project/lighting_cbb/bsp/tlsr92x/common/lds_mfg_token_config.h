/*
 * @File: Do not edit
 * @FilePath: /workspace/lighting_cbb/bsp/tlsr92x/common/lds_mfg_token_config.h
 * @Descripttion: 
 * @Author: huangl
 * @Date: 2024-08-10 10:12:18
 * @par Copyright: Copyright (c) Leedarson 2000-2020. All rights reserved.
 * @history: 
 * @ LastEditors: huangl
 * @ LastEditTime: Do not Edit
 * @ version: V1.00.00
 * @ Modification: Create file
 */

#ifndef _LDS_MFG_TOEKN_CONFIG_H_
#define _LDS_MFG_TOEKN_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include <stdint.h>
#include "lds_error_codes.h"
#include "lds_device_config.h"
#if (defined EXTENDEDCOLOR_LIGHT)
#include "lds_color_algorithm.h"
#endif

#define LDS_DEFAULT_VALUE		10000

#pragma pack (1)
typedef enum {
	RF_TX_POWER_0dBm = 0,
	RF_TX_POWER_1dBm,
	RF_TX_POWER_2dBm,
	RF_TX_POWER_3dBm,
	RF_TX_POWER_4dBm,
	RF_TX_POWER_5dBm,
	RF_TX_POWER_6dBm,
	RF_TX_POWER_7dBm,
	RF_TX_POWER_8dBm,
	RF_TX_POWER_9dBm,
	RF_TX_POWER_10dBm
}LDS_RF_TX_POWER_E;

//typedef struct {
//    uint8_t i2c_ww_current_max;
//    uint8_t i2c_cw_current_max;
//    uint8_t i2c_standby_mode_config;
//#if defined(DIMMABLE_LIGHT)
//    uint8_t i2c_out_pin;
//#elif defined(COLORTEMPERATURE_LIGHT)
//    uint8_t i2c_out_pin[2];
//#elif defined(EXTENDEDCOLOR_LIGHT)
//    uint8_t i2c_out_pin[5];
//#endif
//    uint8_t i2c_adjust_dimming_mode;
//#if defined(DIMMABLE_LIGHT)
//    uint8_t i2c_adjust_gray_scale;
//#elif defined(COLORTEMPERATURE_LIGHT)
//    uint8_t i2c_adjust_gray_scale[2];
//#elif defined(EXTENDEDCOLOR_LIGHT)
//    uint8_t i2c_adjust_gray_scale[5];
//#endif
//    uint8_t i2c_chopping_frequency;
//    uint8_t i2c_led_minl_threshold_setting;
//}lds_i2c_params_set;

typedef struct {
    uint8_t token_version;		// token version
    //Device Info
    uint16_t image_type;
    uint8_t key_type;			// key type 0x01:Mk, 0x02:DK
    //Driver mode
    uint8_t driver_mode;
    uint8_t driver_i2c_type;
    //Basic Cluster Info
    uint8_t model_identifier[48];
    uint8_t hardware_version;
    uint8_t product_code[16];
    uint8_t product_type;
    uint8_t device_class;
    uint8_t device_type;
    //power settings
    uint8_t zll_rssi_threshold;
    struct {
    	uint8_t low_channel : 4;
    	uint8_t high_channel : 4;
    } zigbee_tx_power;
    struct {
    	uint8_t low_channel : 4;
    	uint8_t high_channel : 4;
    } ble_tx_power;
    //PWM settings
#if defined(DIMMABLE_LIGHT)
    uint8_t pwm_port_pin;
#elif defined(COLORTEMPERATURE_LIGHT)
    uint8_t pwm_port_pin[2];
#elif defined(EXTENDEDCOLOR_LIGHT)
    uint8_t pwm_port_pin[5];
#endif
    uint16_t pwm_frequency;
    uint16_t pwm_min_duty_cycle;
    uint16_t pwm_max_duty_cycle;
    //Reset settings
    uint16_t power_toggle_counter_time_limit;
    //Protection settings
    uint8_t trf_adc_source_pin;
    uint8_t over_temperature_threshold;
    uint16_t trf_pwm_limit;
    //Color temperature percentage 
    uint8_t color_temperature_2700k_percentage;
    uint8_t color_temperature_4000k_percentage;
    //Color temperature mireds
    uint16_t color_temperature_mireds_min;
    uint16_t color_temperature_mireds_max;
    uint16_t default_color_temperature_mired;
    //CCT Driver mode
    uint8_t cct_driver_mode;
    //I2C Settings
//    lds_i2c_params_set i2c_set;
#ifndef DIMMABLE_LIGHT
#if (defined EXTENDEDCOLOR_LIGHT)
    uint8_t i2c_r_current_max;
    uint8_t i2c_g_current_max;
    uint8_t i2c_b_current_max;
#endif
    uint8_t i2c_ww_current_max;
    uint8_t i2c_cw_current_max;
    uint8_t i2c_standby_mode_config;
#if defined(DIMMABLE_LIGHT)
    uint8_t i2c_out_pin;
#elif defined(COLORTEMPERATURE_LIGHT)
    uint8_t i2c_out_pin[2];
#elif defined(EXTENDEDCOLOR_LIGHT)
    uint8_t i2c_out_pin[5];
#endif
    uint8_t i2c_adjust_dimming_mode;
    uint8_t i2c_rgb_dimming_mode;
    uint8_t i2c_otp_and_ovp_config;
#if defined(DIMMABLE_LIGHT)
    uint16_t i2c_adjust_gray_scale;
#elif defined(COLORTEMPERATURE_LIGHT)
    uint16_t i2c_adjust_gray_scale[2];
#elif defined(EXTENDEDCOLOR_LIGHT)
    uint16_t i2c_adjust_gray_scale[5];
#endif
    uint8_t i2c_chopping_frequency;
    uint8_t i2c_led_minl_threshold_setting;
#endif
    //onoff settings
    uint8_t on_transition_time_ds;
    uint8_t off_transition_time_ds;
#if defined(COLORTEMPERATURE_LIGHT)
    uint16_t ws_ww_output_limit;				// 2200K output limit
    uint16_t ws_cw_output_limit;				// 6500K output limit
    uint16_t ws_medium_output_limit;			// 4000K output limit
#endif
#if defined(EXTENDEDCOLOR_LIGHT)
    //Light source type
    uint8_t light_source_number;
    //Color param
    uint8_t cws_r_light_source_param[28];
    uint8_t cws_g_light_source_param[28];
    uint8_t cws_b_light_source_param[28];
    uint8_t cws_ww_light_source_param[28];
    uint8_t cws_cw_light_source_param[28];
    uint8_t cws_rgb_power_limit[4];
    uint8_t cws_total_power_limit[4];
    uint16_t cws_ww_output_limit;
    uint16_t cws_cw_output_limit;
    uint16_t cws_medium_output_limit;
#endif
    uint8_t freq_offset_value;
    uint8_t precharge_duty_cycle;			// Firmware optimized hardware low brightness slow startup, first high duty ratio output
	uint8_t precharge_duty_cycle_time;		// Firmware optimized hardware low brightness slow startup, first high duty ratio output time
	uint8_t precharge_duty_cycle_condition;
	uint16_t precharge_onoff_interval_time;
	uint8_t matter_dac_key;
	uint8_t onoff_transition_time;
} lds_token_info_t;
#pragma pack ()

lds_token_info_t *ldsLightTokenGet(void);

void ldsGetTokenInfoFromFlashGet(void);

bool ldsFlashFactoryResetFlagRead(void);

uint8_t *ldsMfgTokenGetModelID(void);

uint8_t ldsMfgTokenNetworkKeyGet(void);

uint8_t ldsMfgTokenZigbeeLowChannelTxPowerGet();

uint8_t ldsMfgTokenZigbeeHighChannelTxPowerGet();

uint8_t ldsMfgTokenBleLowChannelTxPowerGet();

uint8_t ldsMfgTokenBleHighChannelTxPowerGet();

uint16_t ldsMfgTokenDriverMinDutyCycle(void);

uint16_t ldsMfgTokenDriverMaxDutyCycle(void);

uint8_t ldsMfgTokenDriverOverTemperature(void);

uint8_t ldsGetMfgTokenDriverMode(void);

uint8_t ldsMfgTokenDriverI2cType(void);

uint8_t ldsMfgTokenCctDriverModeGet(void);

uint8_t ldsMfgTokenCwCurrentMaxGet(void);

uint8_t ldsMfgTokenWwCurrentMaxGet(void);

uint8_t ldsMfgTokenI2cStandbyModeConfigGet(void);

uint8_t ldsMfgTokenI2cAdjustDimmingModeGet(void);

uint8_t ldsMfgTokenI2cRgbDimmingModeGet(void);

uint8_t ldsMfgTokenI2cOtpAndOvpConfigGet(void);

lds_status_t ldsGetMfgTokenColorTemperaturePercentage(uint16_t color_temperature, uint8_t *color_temperature_percentage);

uint16_t ldsTokenWwOutputLimit(void);

uint16_t ldsTokenCwOutputLimit(void);

uint16_t ldsTokenMediumOutputLimit(void);

uint16_t ldsTokenPrechargeDutyCycle(void);

uint8_t ldsTokenPrechargeDutyCycleCondition(void);

uint16_t ldsTokenPrechangeDutyCycleOutputTime(void);

uint32_t ldsTokenPrechargeOnOffIntervalTimeMs(void);

uint16_t ldsTokenOnOffTransitionTime(void);

#if defined(EXTENDEDCOLOR_LIGHT)
lds_status_t ldsSystemCommonLightSourceParamTokenGet(lds_light_param_t * param);

lds_status_t lds_wrapper_token_get_manufacturing_data(uint32_t token, void* data, uint32_t length);
#endif

#ifdef __cplusplus
}
#endif 

#endif // _LDS_MFG_TOEKN_CONFIG_H_
