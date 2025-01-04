/*
 * @Author: chenkunlin chenkunlin@leedarson.com
 * @Date: 2024-05-16 18:27:24
 * @LastEditors: linwanyi linwanyi@leedarson.com
 * @LastEditTime: 2024-06-05 15:53:43
 * @FilePath: /chenkl/lighting_cbb/components/lds_simple/test/lds_simple_test.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/lds_power_on_count.h"
/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

static void test_short(void **state) {
    
    int cur_tick = 600;
    power_on_count_data_save_t *test_count;
    power_on_count_data_t *test_data;
    test_count = malloc(sizeof(power_on_count_data_save_t));
    test_data = malloc(sizeof(power_on_count_data_t));
    
    test_count->index = 0;

    ldsPowerOnCountUpdate(cur_tick,test_count,test_count->index,test_data);
    // Assert
    assert_int_equal(POWER_ON_COUNT_SHORT, test_count->count_value[0]);
    assert_int_equal(1, test_count->index);
    // int result = add(2, 3);
    // assert_int_equal(result, 5);
}
static void test_long(void **state) {
    
    int cur_tick = 3500;
    power_on_count_data_save_t *test_count;
    power_on_count_data_t *test_data;
    test_count = malloc(sizeof(power_on_count_data_save_t));
    test_data = malloc(sizeof(power_on_count_data_t));

    ldsPowerOnCountUpdate(cur_tick,test_count,test_count->index,test_data);
    // Assert
    assert_int_equal(POWER_ON_COUNT_LONG, test_count->count_value[0]);
    assert_int_equal(1, test_count->index);
    // int result = add(2, 3);
    // assert_int_equal(result, 5);
}
static void test_timeout(void **state) {
    
    int cur_tick = 5000;
    power_on_count_data_save_t *test_count;
    power_on_count_data_t *test_data;
    test_count = malloc(sizeof(power_on_count_data_save_t));
    test_data = malloc(sizeof(power_on_count_data_t));
    
    test_count->index = 0;

    ldsPowerOnCountUpdate(cur_tick,test_count,test_count->index,test_data);
    // Assert
    assert_int_equal(POWER_ON_COUNT_TIMEOUT, test_count->count_value[0]);
    assert_int_equal(0, test_count->index);
    // int result = add(2, 3);
    // assert_int_equal(result, 5);
}
static void test_lds_Power_on_count_match(void **state) {
    power_on_count_data_save_t *test_count;
    power_on_count_data_t *test_data;
    test_count = malloc(sizeof(power_on_count_data_save_t));
    test_data = malloc(sizeof(power_on_count_data_t));
    test_count->index = 4;
    test_count->count_value[0] = 1;
    test_count->count_value[1] = 2;
    test_count->count_value[2] = 1;
    test_count->count_value[3] = 1;
    test_count->count_value[4] = 2;
    test_count->count_value[5] = 1;

    ldsPowerOnCountMatch(test_count,0,test_count->index);
    assert_int_equal(POWER_ON_COUNT_MATCH_SUCCESS,ismatch);
}



// static void test_add_negative(void **state) {
//     int result = add(-1, 1);
//     assert_int_equal(result, 0);
// }

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_short),
        cmocka_unit_test(test_long),
        cmocka_unit_test(test_timeout),
        cmocka_unit_test(test_lds_Power_on_count_match),
        // cmocka_unit_test(test_add_negative),
        cmocka_unit_test(null_test_success),
        
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
