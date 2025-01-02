#ifndef _LDS_DEVICE_I2C_H_
#define _LDS_DEVICE_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "lds_error_codes.h"
#include "gpio.h"
#include "tl_common.h"

typedef enum {
	KP18056 = 0,
	KP18057,
	BP5758,
	OTHER_I2C
} LDS_I2C_TYPE_E;

void ldsDriverI2cInit(void);

//void ldsDriverI2cWrite(float *pwm);
void ldsDriverI2cWrite(float *percent, bool last_flag);

void ldsI2cMasterInit(uint8_t slave_id, uint32_t i2c_clock);

//#endif
#ifdef __cplusplus
}
#endif 

#endif // _LDS_DRIVER_I2C_H_
