// Copyright © Inter IKEA Systems B.V. 2023.
// All Rights Reserved.
//
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of © Inter IKEA Systems B.V.
// the contents of this file may not be disclosed to third parties, copied
// or duplicated in any form, in whole or in part, without the prior
// written permission of © Inter IKEA Systems B.V.
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>

#include "../inc/lds_color_conversion.h"

#define FLOAT_EQUAL_EPSILON ((float)(5e-4))

static const lds_xy_t g_origin_r_xy = {0.692244, 0.305968};
static const lds_xy_t g_origin_g_xy = {0.159515, 0.708639};
static const lds_xy_t g_origin_b_xy = {0.147374, 0.036486};

// xy -> hsv -> xy
static const lds_xy_t g_xy2hsv_xy_point = {0.48816, 0.33992};
static const lds_color_conversion_hsv_info_t g_xy2hsv_hsv_point_info = {1, 10, 50, 100};
static const float g_xy2hsv_hue = 10;
static const float g_xy2hsv_sat = 50;
static const float g_xy2hsv_value = 100;

// cct -> xy -> cct
static const float g_cct2xy_cct_point = 4000.0;
static const lds_xy_t g_cct2xy_xy_point = {0.380528, 0.376728};
static const lds_xy_t g_xy2cct_xy_point = {0.380528, 0.376728};
static const lds_color_conversion_cct_info_t g_xy2cct_cct_point_info = {1, 3995.902344};

// hsv -> cct -> hsv
static const float g_hsv2cct_hue = 50;
static const float g_hsv2cct_sat = 50;
static const float g_hsv2cct_value = 100;
static const lds_color_conversion_cct_info_t g_hsv2cct_cct_point_info = {1, 3821.269043};
static const float g_cct2hsv_cct_point = 3821;
static const lds_color_conversion_hsv_info_t g_cct2hsv_hsv_point_info = {1, 36.66955, 34.35596, 100};

static void test_lds_color_conversion_xy_to_hsv(void** state) {
  (void)state; /* unused */
  lds_status_t status;
  lds_color_conversion_hsv_info_t hsv_out;
  const lds_color_conversion_hsv_info_t* expected_hsv = &g_xy2hsv_hsv_point_info;
  lds_color_conversion_hsv_info_t* actual_hsv = &hsv_out;
  const lds_xy_t* p_point_xy = &g_xy2hsv_xy_point;

  status = lds_color_conversion_xy_to_hsv(&g_origin_r_xy, &g_origin_g_xy, &g_origin_b_xy, p_point_xy, &hsv_out);
  assert_true(status == LDS_SUCCESS);
  assert_float_equal(expected_hsv->hue, actual_hsv->hue, FLOAT_EQUAL_EPSILON);
  assert_float_equal(expected_hsv->saturation, actual_hsv->saturation, FLOAT_EQUAL_EPSILON);

  status = lds_color_conversion_xy_to_hsv(&g_origin_r_xy, &g_origin_g_xy, &g_origin_b_xy, p_point_xy, NULL);
  assert_true(status == LDS_ERROR_BAD_ARGUMENT);
}

static void test_lds_color_conversion_hsv_to_xy(void** state) {
  (void)state; /* unused */
  lds_status_t status;

  lds_xy_t xy_out;
  lds_xy_t* actual_xy = &xy_out;
  const lds_xy_t* expect_xy = &g_xy2hsv_xy_point;
  const lds_xy_t* p_origin_r_info = &g_origin_r_xy;
  const lds_xy_t* p_origin_g_info = &g_origin_g_xy;
  const lds_xy_t* p_origin_b_info = &g_origin_b_xy;

  const float point_hue = g_xy2hsv_hue;
  const float point_saturation = g_xy2hsv_sat;
  const float point_value = g_xy2hsv_value;

  status = lds_color_conversion_hsv_to_xy(p_origin_r_info, p_origin_g_info, p_origin_b_info, point_hue,
                                          point_saturation, point_value, &xy_out);
  assert_true(status == LDS_SUCCESS);

  assert_float_equal(actual_xy->x, expect_xy->x, FLOAT_EQUAL_EPSILON);
  assert_float_equal(actual_xy->y, expect_xy->y, FLOAT_EQUAL_EPSILON);

  status = lds_color_conversion_hsv_to_xy(p_origin_r_info, p_origin_g_info, p_origin_b_info, point_hue,
                                          point_saturation, point_value, NULL);
  assert_true(status == LDS_ERROR_BAD_ARGUMENT);

  status = lds_color_conversion_hsv_to_xy(NULL, p_origin_g_info, p_origin_b_info, point_hue, point_saturation,
                                          point_value, &xy_out);
  assert_true(status == LDS_ERROR_BAD_ARGUMENT);
}

static void test_lds_color_conversion_xy_to_cct(void** state) {
  (void)state; /* unused */
  lds_status_t status;

  const lds_xy_t* p_point_xy = &g_xy2cct_xy_point;
  lds_color_conversion_cct_info_t cct_out;
  lds_color_conversion_cct_info_t* actual_cct = &cct_out;
  const lds_color_conversion_cct_info_t* expected_cct = &g_xy2cct_cct_point_info;
  status = lds_color_conversion_xy_to_cct(p_point_xy, NULL);
  assert_true(status == LDS_ERROR_BAD_ARGUMENT);

  status = lds_color_conversion_xy_to_cct(NULL, &cct_out);
  assert_true(status == LDS_ERROR_BAD_ARGUMENT);

  status = lds_color_conversion_xy_to_cct(p_point_xy, &cct_out);
  assert_true(status == LDS_SUCCESS);

  assert_float_equal(expected_cct->cct, actual_cct->cct, (float)1e-1);
}

static void test_lds_color_conversion_cct_to_xy(void** state) {
  (void)state; /* unused */
  lds_status_t status;
  lds_xy_t xy_out;

  lds_xy_t* actual_xy = &xy_out;
  const lds_xy_t* expected_xy = &g_cct2xy_xy_point;
  const float point_color_temperature = g_cct2xy_cct_point;

  status = lds_color_conversion_cct_to_xy(point_color_temperature, NULL);
  assert_true(status == LDS_ERROR_BAD_ARGUMENT);

  status = lds_color_conversion_cct_to_xy(point_color_temperature, &xy_out);
  assert_true(status == LDS_SUCCESS);
  assert_float_equal(expected_xy->x, actual_xy->x, FLOAT_EQUAL_EPSILON);
  assert_float_equal(expected_xy->y, actual_xy->y, FLOAT_EQUAL_EPSILON);
}

static void test_lds_color_conversion_hsv_to_cct(void** state) {
  (void)state; /* unused */
  uint8_t status;
  const lds_xy_t* p_origin_r_info = &g_origin_r_xy;
  const lds_xy_t* p_origin_g_info = &g_origin_g_xy;
  const lds_xy_t* p_origin_b_info = &g_origin_b_xy;

  const float point_hue = g_hsv2cct_hue;
  const float point_saturation = g_hsv2cct_sat;
  const float point_value = g_hsv2cct_value;

  lds_color_conversion_cct_info_t cct_out;
  lds_color_conversion_cct_info_t* actual_cct = &cct_out;
  const lds_color_conversion_cct_info_t* p_cct_info_const = &g_hsv2cct_cct_point_info;

  status = lds_color_conversion_hsv_to_cct(p_origin_r_info, p_origin_g_info, p_origin_b_info, point_hue,
                                           point_saturation, point_value, NULL);

  assert_true(status == LDS_ERROR_BAD_ARGUMENT);

  status = lds_color_conversion_hsv_to_cct(p_origin_r_info, p_origin_g_info, p_origin_b_info, point_hue,
                                           point_saturation, point_value, &cct_out);

  assert_float_equal(p_cct_info_const->cct, actual_cct->cct, 1e-1);
}

static void test_lds_color_conversion_cct_to_hsv(void** state) {
  (void)state; /* unused */
  uint8_t status;
  const float point_cct = g_cct2hsv_cct_point;
  const lds_xy_t* p_origin_r_info = &g_origin_r_xy;
  const lds_xy_t* p_origin_g_info = &g_origin_g_xy;
  const lds_xy_t* p_origin_b_info = &g_origin_b_xy;
  const lds_color_conversion_hsv_info_t* p_hsv_info_const = &g_cct2hsv_hsv_point_info;
  lds_color_conversion_hsv_info_t hsv_out;
  lds_color_conversion_hsv_info_t* actual_hsv = &hsv_out;

  status = lds_color_conversion_cct_to_hsv(p_origin_r_info, p_origin_g_info, p_origin_b_info, point_cct, NULL);
  assert_true(status == LDS_ERROR_BAD_ARGUMENT);

  status = lds_color_conversion_cct_to_hsv(p_origin_r_info, p_origin_g_info, p_origin_b_info, point_cct, &hsv_out);
  assert_true(status == LDS_SUCCESS);

  assert_float_equal(actual_hsv->hue, p_hsv_info_const->hue, 1e-1);
  assert_float_equal(actual_hsv->saturation, p_hsv_info_const->saturation, 1e-1);
  assert_float_equal(actual_hsv->value, p_hsv_info_const->value, 1e-1);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_lds_color_conversion_xy_to_hsv),  cmocka_unit_test(test_lds_color_conversion_hsv_to_xy),
      cmocka_unit_test(test_lds_color_conversion_xy_to_cct),  cmocka_unit_test(test_lds_color_conversion_cct_to_xy),
      cmocka_unit_test(test_lds_color_conversion_hsv_to_cct), cmocka_unit_test(test_lds_color_conversion_cct_to_hsv),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
