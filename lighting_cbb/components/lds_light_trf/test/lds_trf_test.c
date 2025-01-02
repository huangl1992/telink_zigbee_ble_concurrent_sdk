/*
 * @File: Do not edit
 * @FilePath: /lighting_cbb/components/lds_light_trf/test/lds_trf_test.c
 * @Descripttion: 
 * @Author: huangl
 * @Date: 2024-05-22 15:56:04
 * @par Copyright: Copyright (c) Leedarson 2000-2020. All rights reserved.
 * @history: 
 * @ LastEditors: huangl
 * @ LastEditTime: Do not Edit
 * @ version: V1.00.00
 * @ Modification: Create file
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "../inc/lds_trf.h"

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

static void test_ldsTrfInit(void **state)
{

}

static void test_ldsUpdateVoltageAndTemperatureTable(void **state)
{

}

static void test_ldsTrfVoltageChangeTemperature(void **state)
{

}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ldsTrfInit),
        cmocka_unit_test(test_ldsUpdateVoltageAndTemperatureTable),
        cmocka_unit_test(test_ldsTrfVoltageChangeTemperature),
        cmocka_unit_test(null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}