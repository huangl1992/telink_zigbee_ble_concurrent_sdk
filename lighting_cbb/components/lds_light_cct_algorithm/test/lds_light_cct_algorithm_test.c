/*
 * @Author: chenkunlin chenkunlin@leedarson.com
 * @Date: 2024-05-16 18:27:24
 * @LastEditors: xiehuawei xiehuawei@leedarson.com
 * @LastEditTime: 2024-05-23 11:04:09
 * @FilePath: /chenkl/lighting_cbb/components/lds_simple/test/lds_simple_test.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "../inc/lds_light_cct_algorithm.h"
/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}


static void test_1(void **state) {
    uint16_t color_temp = 2700;
    uint8_t level = 100;
    twAttr_t temptwPWM;
    ldsCalculateTWPWMFromColorTemp(color_temp, level, &temptwPWM);

}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_1),
        cmocka_unit_test(null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
