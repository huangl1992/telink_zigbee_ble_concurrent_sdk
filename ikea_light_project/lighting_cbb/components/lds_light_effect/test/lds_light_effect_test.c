/*
 * @Author: chenkunlin chenkunlin@leedarson.com
 * @Date: 2024-05-16 18:27:24
 * @LastEditors: xiehuawei xiehuawei@leedarson.com
 * @LastEditTime: 2024-05-23 10:48:23
 * @FilePath: /chenkl/lighting_cbb/components/lds_simple/test/lds_simple_test.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
// #include "../inc/lds_light_effect.h"
/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

static void test_add(void **state) {
    // testLightEffect();
    // int result = add(2, 3);
    // assert_int_equal(result, 5);
}

static void test_add_negative(void **state) {
    // int result = add(-1, 1);
    // assert_int_equal(result, 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_add),
        cmocka_unit_test(test_add_negative),
        cmocka_unit_test(null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
