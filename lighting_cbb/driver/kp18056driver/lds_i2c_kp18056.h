/**
 * @file    lds_i2c_kp18056.h
 * @author  simon.zheng (zhenglibin@leedarson.com)
 * @brief   KP18056
 * @version 1.0
 * @date    2024-06-04
 *
 * @copyright Copyright (c) 2024 Leedarson All Rights Reserved.
 *
 */

#ifndef __LDS_I2C_KP18056_H__
#define __LDS_I2C_KP18056_H__


#define I2C_SLAVE_WORK_ADDR     0xE1    // 从设备地址0xB0，输出时地址会左移一位，配置时先右移一位。
#define I2C_SLAVE_SLEEP_ADDR    0x81    // 从设备休眠地址0x80
#define I2C_RGB_CURRENT         0x6A    // RGB默认电流
#define I2C_TW_CURRENT          0x4B    // 

// 调光芯片输出脚位
typedef enum {
    I2C_PIN_R_DIM = 0,  // R路或DIM路
    I2C_PIN_G_CCT,      // G路或CCT路
    I2C_PIN_B,          // B路
    I2C_PIN_WARM,       // 2700K路
    I2C_PIN_COLD,       //
    I2C_PIN_ALL,     // 输出脚位总数
} I2C_PIN_E;

typedef struct {
    float           out_limit;              // RGB输出比例
    unsigned char   rgb_current;            // RGB电流，用于kp18056
    unsigned char   tw_current;             // TW电流，用于kp18056
	unsigned char   mode_config;			// 设置斩波/模拟 用于KP18056
    unsigned char   out_pin[I2C_PIN_ALL];   // I2C输出脚位信息
} I2C_CHIP_PARAM_S;

// 调光芯片控制信息
typedef enum {
    OUT_PIN_1 = 0,
    OUT_PIN_2,
    OUT_PIN_3,
    OUT_PIN_4,
    OUT_PIN_5,
    OUT_PIN_ALL,
} OUT_PIN_E;

#pragma pack (1)
typedef struct {
    unsigned char pwm_h;
    unsigned char pwm_l;
} PWM_INFO_S;

typedef struct {
    unsigned char   mode;                       // Byte1调光模式选择
    unsigned char   current_out_rgb;           // RGB最大输出电流
    unsigned char   current_out_cw;           // cw最大输出电流
    PWM_INFO_S      pwm_out[OUT_PIN_ALL];     // OUT1~5
    unsigned char   vin_threshold;           // VIN待机阈值电压设定
} I2C_DATA_S;
#pragma pack ()

#define I2C_DATA_LEN  sizeof(I2C_DATA_S)        // 传输数据字节数
// I2C调光芯片参数配置
void ldsI2cKp18056ChipParamSet(I2C_CHIP_PARAM_S chip_param);

// 将输入的PWM转换为调光芯片的数据
// input: data_len, pwm, pwm_num, power_limit
// output: i2c_data, data_len, ret_info
char ldsI2cKp18056ChipDataTransform(unsigned char *i2c_data, unsigned char *data_len,
     const float *pwm, unsigned char pwm_num, float power_limit);

#endif /* __I2C_CHIP_KP18056_H__ */