/*
 * @Author: zhenglibin zhenglibin@leedarson.com
 * @Date: 2024-05-16 18:27:24
 * @LastEditors: zhenglibin zhenglibin@leedarson.com
 * @LastEditTime: 2024-05-20 11:09:24
 * @FilePath: /chenkl/lighting_cbb/components/lighting_algorithm/test/lds_dim_algorithm_test.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "../inc/lds_dim_algorithm.h"


#define LDS_PWM_MAX_DUTY_CYCLE 1000
#define LDS_PWM_MIN_DUTY_CYCLE 1

static uint16_t lut_pwm0[256] = {0};

ts_dim_algorithm_param_t pwm0 = 
{
    .min_duty_cycle = LDS_PWM_MIN_DUTY_CYCLE,
    .max_duty_cycle = LDS_PWM_MAX_DUTY_CYCLE,
    .curve_table = lut_pwm0,
};


static void ldsPwmLutInitTest(void** state) 
{
	assert_in_range(pwm0.min_duty_cycle, 1, pwm0.max_duty_cycle);
	assert_in_range(pwm0.max_duty_cycle, pwm0.min_duty_cycle, 10000);
	assert_int_equal(pwm0.min_duty_cycle, 1);
	assert_int_equal(pwm0.max_duty_cycle, 1000);
	
	ldsPwmLutInitTable(&pwm0);
	ldsPwmLutInit(&pwm0);
	assert_int_equal(pwm0.curve_table[0x01], 25);
	assert_int_equal(pwm0.curve_table[0x7f], 798);
	assert_int_equal(pwm0.curve_table[0xfe], 25600);
}

static void ldsPwmLutSetTest(void** state) 
{
	// Max range check
	pwm0.min_duty_cycle = 1;
	pwm0.max_duty_cycle = 10000;
	ldsPwmLutInitTable(&pwm0);
	ldsPwmLutInit(&pwm0);
	assert_int_equal(pwm0.curve_table[0x01], 2);
	assert_int_equal(pwm0.curve_table[0x7f], 251);
	assert_int_equal(pwm0.curve_table[0xfe], 25600);
	
	// 80% range check
	pwm0.min_duty_cycle = 100;
	pwm0.max_duty_cycle = 900;
	ldsPwmLutInitTable(&pwm0);
	ldsPwmLutInit(&pwm0);
	assert_int_equal(pwm0.curve_table[0x01], 2560);
	assert_int_equal(pwm0.curve_table[0x7f], 7646);
	assert_int_equal(pwm0.curve_table[0xfe], 23040);
}

static void ldsPwmLutDutyTest(void** state) 
{
	pwm0.min_duty_cycle = 1;
	pwm0.max_duty_cycle = 1000;
	ldsPwmLutInitTable(&pwm0);
	ldsSetLutExp(pwm0.curve_table, 100);
	assert_int_equal(pwm0.curve_table[0x01], 25);
	assert_int_equal(pwm0.curve_table[0x7f], 798);
	assert_int_equal(pwm0.curve_table[0xfe], 25600);
	
	ldsSetLutExp(pwm0.curve_table, 50);
	assert_int_equal(pwm0.curve_table[0x01], 25);
	assert_int_equal(pwm0.curve_table[0x7f], 399);
	assert_int_equal(pwm0.curve_table[0xfe], 12800);
}

int main(void) 
{
	const struct CMUnitTest tests[] = {cmocka_unit_test(ldsPwmLutInitTest), cmocka_unit_test(ldsPwmLutSetTest),
										cmocka_unit_test(ldsPwmLutDutyTest)};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

