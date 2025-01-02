/**
 * @file    i2c_chip_kp18057.h
 * @author  simon.zheng (zhenglibin@leedarson.com)
 * @brief   KP18057
 * @version 1.0
 * @date    2024-06-04
 *
 * @copyright Copyright (c) 2024 Leedarson All Rights Reserved.
 *
 */

#ifndef __LDS_I2C_KP18057_H__
#define __LDS_I2C_KP18057_H__

#include <stdint.h>


#define I2C_KP18057_SLAVE_WORK_ADDR     0xC0    // 从设备地址0x41，最低位为奇偶校验位，写地址时奇偶校验位替换为读写位。输出时地址会左移一位，配置时先右移一位。
#define I2C_KP18057_SLAVE_SLEEP_ADDR    0x00    // 待机模式
#if defined(COLORTEMPERATURE_LIGHT)
#define I2C_KP18057_RGB_CURRENT         0x01    // RGB默认电流0.2mA
#else
#define I2C_KP18057_RGB_CURRENT         0x32    // TODO:RGB默认电流按实际电子提供设置 0x0A = 2mA
#endif
#define I2C_KP18057_TW_CURRENT          0x12    // TODO:TW默认电流按实际电子提供设置  0x0A = 10mA

// 调光芯片输出脚位
typedef enum {
    I2C_KP18057_PIN_R_DIM = 0,  // R路或DIM路
    I2C_KP18057_PIN_G_CCT,      // G路或CCT路
    I2C_KP18057_PIN_B,          // B路
    I2C_KP18057_PIN_WARM,       // 2700K或2200K路
    I2C_KP18057_PIN_COLD,       // 6500K路
    I2C_KP18057_PIN_ALL,        // 输出脚位总数
} I2C_KP18057_PIN_E;

typedef struct {
    float           out_limit;              // RGB输出比例
    unsigned char   rgb_current;            // RGB电流，用于KP18057
    unsigned char   tw_current;             // TW电流，用于KP18057
	unsigned char	led_threshold;			// LED_THRESHOLD 设置效率 用于KP18057
	unsigned char   tst_config;				// LED_THRESHOLD 设置待机钳位电压阈值设置 用于KP18057
	uint8_t			rgb_dimming_mode;		// rgb dimming mode setting, chopper frequency setting, quick start end threshold setting
	uint8_t         otp_and_ovp_config;		// OTP and OVP threshold value config set
    unsigned char   out_pin[I2C_KP18057_PIN_ALL];   // I2C输出脚位信息
} I2C_KP18057_CHIP_PARAM_S;

// 调光芯片控制信息
typedef enum {
    KP18057_OUT_PIN_1 = 0,
    KP18057_OUT_PIN_2,
    KP18057_OUT_PIN_3,
    KP18057_OUT_PIN_4,
    KP18057_OUT_PIN_5,
    KP18057_OUT_PIN_ALL,
} KP18057_OUT_PIN_E;

#pragma pack (1)
typedef struct {
    unsigned char pwm_h;
    unsigned char pwm_l;
} KP18057_PWM_INFO_S;

// KP18057调光芯片I2C通信数据结构体
typedef struct {
    unsigned char   led_threshold;
    unsigned char   current_enable;             // OUT1-OUT5输出电流使能设置
    unsigned char   current_out[KP18057_OUT_PIN_ALL];   // OUT1~OUT5最大输出电流
    KP18057_PWM_INFO_S      pwm_out[KP18057_OUT_PIN_ALL];       // OUT1~OUT5电流灰度设置
    unsigned char   reserved_config[2];
    unsigned char   mode_config;
    unsigned char   tst_config;
    unsigned char   other_config;
} I2C_KP18057_DATA_S;
#pragma pack ()

#define I2C_KP18057_DATA_LEN  sizeof(I2C_KP18057_DATA_S)        // 传输数据字节数
#define KP18057_LED_THRESHOLD_STATIC            0x69    // 不调光时配置值
// I2C调光芯片参数配置
void ldsI2cKp18057ChipParamSet(I2C_KP18057_CHIP_PARAM_S chip_param);

// 将输入的PWM转换为调光芯片的数据
// input: data_len, pwm, pwm_num, power_limit
// output: i2c_data, data_len, ret_info
//char ldsI2cKp18057ChipDataTransform(unsigned char *i2c_data, unsigned char *data_len,
//                             float *pwm, unsigned char pwm_num, float power_limit);
char ldsI2cKp18057ChipDataTransform(unsigned char *i2c_data, unsigned char *data_len,
                             float *pwm, unsigned char pwm_num, float power_limit, bool last_package_flag);

#endif /* __LDS_I2C_KP18057_H__ */