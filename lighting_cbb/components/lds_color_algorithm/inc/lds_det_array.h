
#ifndef COMPONENTS_LDS_MATH_INC_LDS_DET_ARRAY_H_
#define COMPONENTS_LDS_MATH_INC_LDS_DET_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lds_color_algorithm/inc/lds_color_algorithm.h"

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

// Definition of determinant or matrix 3x3
// | A11 A12 A13 |
// | A21 A22 A23 |
// | A31 A32 A33 |
typedef struct {
  float A11;
  float A12;
  float A13;
  float A21;
  float A22;
  float A23;
  float A31;
  float A32;
  float A33;
} lds_array3x3_t;

// Definition of determinant or matrix 3x1
// | A1 |
// | A2 |
// | A3 |
typedef struct {
  float A1;
  float A2;
  float A3;
} lds_array3x1_t;

// Definition of determinant or matrix 2x2
// | A11 A12 |
// | A21 A22 |
typedef struct {
  float A11;
  float A12;
  float A21;
  float A22;
} lds_array2x2_t;

/**
 * @brief determinant , det(A)
 * @param [in]  a      : 2x2 array
 * @param [out] result : Determinant value
 * @return status
 **/
lds_status_t lds_calculate_determinant_2x2(const lds_array2x2_t* a, float* result);

/**
 * @brief determinant , det(A)
 * @param [in]  a      : 3x3 array
 * @param [out] result : Determinant value
 * @return status
 **/
lds_status_t lds_calculate_determinant_3x3(const lds_array3x3_t* a, float* result);

/**
 * @brief Inverse array
 * @param [in]  a    : 3x3 array
 * @param [out] inv_a: 3x3 array
 * @return status
 **/
lds_status_t lds_inverse_array3x3(const lds_array3x3_t* a, lds_array3x3_t* inv_a);

/**
 * @brief "matrix product" "matrix multiplication"
 * @param [in]  a      : 3x3 array
 * @param [in]  b      : 3x3 array
 * @param [out] a3x3   : 3x3 array
 * @return status
 **/
lds_status_t lds_array_3x3_3x3_dot(const lds_array3x3_t* a, const lds_array3x3_t* b, lds_array3x3_t* a3x3);

/**
 * @brief "matrix product" "matrix multiplication"
 * @param [in]  a      : 3x3 array
 * @param [in]  b      : 3x3 array
 * @param [out] a3x1   : 3x1 array
 * @return status
 **/
lds_status_t lds_array_3x3_3x1_dot(const lds_array3x3_t* a, const lds_array3x1_t* b, lds_array3x1_t* a3x1);

/**
 * @brief Calculate CbCrCb array for D65 conversion
 * @param [in]  a      : 3x3 array
 * @param [out] a3x1   : 3x1 array
 * @return status
 **/
lds_status_t lds_calculate_cbcrcb_array_for_d65_conversion(const lds_array3x3_t* a, lds_array3x1_t* a3x1);

/**
 * @brief Calculate CbCrCb array for Equal energy white conversion
 * @param [in]  a      : 3x3 array
 * @param [out] a3x1   : 3x1 array
 * @return status
 **/
lds_status_t lds_calculate_cbcrcb_array_for_equal_energy_conversion(const lds_array3x3_t* a, lds_array3x1_t* a3x1);

#ifdef __cplusplus
}
#endif

#endif  // COMPONENTS_LDS_MATH_INC_LDS_DET_ARRAY_H_
