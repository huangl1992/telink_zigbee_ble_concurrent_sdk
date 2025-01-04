#ifndef __LDS_DIM_ALGORITHM_H__
#define __LDS_DIM_ALGORITHM_H__

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifndef PWM_MAX_VALUE	//由IC接口定义获取PWM周期的宏 依据不同的IC平台在对应的头文件中定义，并且要把头文件包含进来
#define PWM_MAX_VALUE  0x6400
#endif
#define DIMMAX  256

typedef struct 
{
	uint16_t max_duty_cycle;
	uint16_t min_duty_cycle;
	uint16_t *curve_table;
} ts_dim_algorithm_param_t;

void ldsDimAlgorithmParamSet(uint16_t mindutycycle);	//注意 :以3%为例，只要设置为30,即30/1000
void ldsPwmLutInitTable(void);
float ldsGetDimalgorithmExpteble(uint8_t level);
void ldsSetLutExp(uint16_t* lut, uint8_t percent); 
void ldsPwmLutInit(ts_dim_algorithm_param_t* dimpwm); 
uint8_t ldsDimCurrentDutyCycleChangeCurrentLevel(uint16_t duty_cycle);
#ifdef __cplusplus
}
#endif

#endif

