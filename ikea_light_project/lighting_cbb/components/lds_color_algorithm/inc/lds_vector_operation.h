/*
 * @Author: chenxiaoqian chenxiaoqian@leedarson.com
 * @Date: 2024-05-23 17:36:11
 * @LastEditors: chenxiaoqian chenxiaoqian@leedarson.com
 * @LastEditTime: 2024-05-28 11:07:43
 * @FilePath: /lighting_cbb/components/lds_math/inc/lds_vector_operation.h
 * @Description: Vector operations used by the algorithm
 */

#ifndef COMPONENTS_XLAB_MATH_INC_XLAB_VECTOR_OPERATION_H_
#define COMPONENTS_XLAB_MATH_INC_XLAB_VECTOR_OPERATION_H_

#include <stdint.h>
#include "lds_color_algorithm.h"

#ifdef __cplusplus
extern "C" {
#endif

// Type to define a line: y = ax + b
typedef struct {
  // slope
  float a;
  // intercept
  float b;
  // set error to 1 if slope is INF or invalid
  uint8_t error;
} lds_line_coeff_t;

/**
 * @brief Check point inside triangle
 * @param [in]  top_a : xy coordinates of triangle top A.
 * @param [in]  top_b : xy coordinates of triangle top B.
 * @param [in]  top_c : xy coordinates of triangle top C.
 * @param [in]  test_point : xy coordinates of test point.
 * @param [in]  deviate_value : Deviation value for float equal judgement.
 * @return Return 1 if T_Coordinates is inside the triangle , otherwise 0.
 **/
uint8_t lds_check_point_inside_triangle(const lds_xy_t* top_a, const lds_xy_t* top_b, const lds_xy_t* top_c,
                                         const lds_xy_t* test_point, float deviate_value);

/**
 * @brief Target color point replacement is performed 
 * using the intersection point of the line composed of D65 and the target color point,
 *  which intersects the triangle.
 * @param [in]  top_a : xy coordinates of triangle top A.
 * @param [in]  top_b : xy coordinates of triangle top B.
 * @param [in]  top_c : xy coordinates of triangle top C.
 * @param [in]  test_point : xy coordinates of test point.
 * @param [out] inter_point : xy coordiates of intersection point on triangle side.
 * @return status
 **/
lds_status_t lds_triangle_D65_white_points_intersection_get_for_coordinate(const lds_xy_t* top_a, const lds_xy_t* top_b,
                                                                   const lds_xy_t* top_c, const lds_xy_t* test_point,
                                                                   lds_xy_t* inter_point);

/**
 * @brief Coordinates to Line
 *        Get line coefficients for poin A and point B.
 * @param [in]  point_a : xy coordinates of point A.
 * @param [in]  point_b : xy coordinates of point B.
 * @param [out] coeff   : coefficient of line AB.
 **/
lds_status_t lds_points_to_line(const lds_xy_t* point_a, const lds_xy_t* point_b, lds_line_coeff_t* coeff);

/**
 * @brief Two Line intersection to Coordinates
 *        Get intersection point of 2 lines.
 * @param [in]  coeff_a : coefficients of line a.
 * @param [in]  coeff_b : coefficients of line b.
 * @param [out] inter_point : intersection point of line a and line b.
 * @return status
 **/
lds_status_t lds_get_lines_intersection_point(const lds_line_coeff_t* coeff_a, const lds_line_coeff_t* coeff_b,
                                               lds_xy_t* inter_point);

#ifdef __cplusplus
}
#endif

#endif  // COMPONENTS_XLAB_MATH_INC_XLAB_VECTOR_OPERATION_H_
