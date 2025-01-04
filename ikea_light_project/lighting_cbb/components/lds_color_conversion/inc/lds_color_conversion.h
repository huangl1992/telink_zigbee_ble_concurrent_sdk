
#ifndef COMPONENTS_LDS_COLOR_CONVERSION_INC_LDS_COLOR_CONVERSION_H_
#define COMPONENTS_LDS_COLOR_CONVERSION_INC_LDS_COLOR_CONVERSION_H_

#include <stdint.h>
#include <stdbool.h>
#include "lds_error_codes.h"
#include "lds_device_config.h"

#ifdef __cplusplus
extern "C" {
#endif


// Type for xy coordinates
typedef struct {
  float x;
  float y;
} lds_xy_t;

// conversion color temperature
typedef struct {
  uint8_t in;
  float cct;
} lds_color_conversion_cct_info_t;

/**
 * @brief
 * if cct->in =1 , x,y is in the area of the Planck curve.
 * if cct->in =0 , x,y is outside the Planck curve area.
 * @param [in]  coordinates
 * @param [out] cct   : lds_color_conversion_cct_info_t
 * @return status
 **/
lds_status_t lds_color_conversion_xy_to_cct(const lds_xy_t* coordinates, lds_color_conversion_cct_info_t* cct);

/**
 * @brief
 * @param [in]  cct
 * @param [out] coordinates   : lds_xy_t
 * @return status
 **/
lds_status_t lds_color_conversion_cct_to_xy(const float cct, lds_xy_t* coordinates);


#ifdef EXTENDEDCOLOR_LIGHT //It is distinguished by device type (CCT or RGB)

#include "lds_color_algorithm.h"

// conversion hsv
typedef struct {
  uint8_t in;  // 0=out,1=in
  float hue;
  float saturation;
  float value;
} lds_color_conversion_hsv_info_t;

/**
 * @brief  origin_r_coordinates,origin_g_coordinates,origin_b_coordinates are light data,got by specific light param
 * @param [in]  origin_r_coordinates
 * @param [in]  origin_g_coordinates
 * @param [in]  origin_b_coordinates
 * @param [in]  t_coordinates
 * @param [out] hsv   : lds_color_conversion_hsv_info_t
 * @return status
 **/
lds_status_t lds_color_conversion_xy_to_hsv(const lds_xy_t* origin_r_coordinates, const lds_xy_t* origin_g_coordinates,
                                            const lds_xy_t* origin_b_coordinates, const lds_xy_t* t_coordinates,
                                            lds_color_conversion_hsv_info_t* hsv);

/**
 * @brief
 * origin_r_coordinates,origin_g_coordinates,origin_b_coordinates are light data,got by specific light param
 * hues range(0-360) , saturation range(0-100) , value range(0-100)
 * about lds_xy_t : two cases will output 0,0
 * if Input parameter "Value" =0 => Represents it's black and white , x,y will be 0,0
 * if hues, saturation, value : Not within allowed range. x,y will be 0,0
 * @param [in]  origin_r_coordinates
 * @param [in]  origin_g_coordinates
 * @param [in]  origin_b_coordinates
 * @param [in]  hue
 * @param [in]  saturation
 * @param [in]  value
 * @param [out] point   : lds_xy_t
 * @return status
 **/
lds_status_t lds_color_conversion_hsv_to_xy(const lds_xy_t* origin_r_coordinates, const lds_xy_t* origin_g_coordinates,
                                            const lds_xy_t* origin_b_coordinates, float hue, float saturation,
                                            float value, lds_xy_t* point);



/**
 * @brief
 * r_coordinates,g_coordinates,b_coordinates are light data,got by specific light param
 * if cct->in =1 , x,y is in the area of the Planck curve.
 * if cct->in =0 , x,y is outside the Planck curve area.
 * @param [in]  r_coordinates
 * @param [in]  g_coordinates
 * @param [in]  b_coordinates
 * @param [in]  hue
 * @param [in]  saturation
 * @param [in]  value
 * @param [out] cct   : lds_color_conversion_cct_info_t
 * @return status
 **/
lds_status_t lds_color_conversion_hsv_to_cct(const lds_xy_t* r_coordinates, const lds_xy_t* g_coordinates,
                                             const lds_xy_t* b_coordinates, float hue, float saturation, float value,
                                             lds_color_conversion_cct_info_t* cct);

/**
 * @brief
 * r_coordinates,g_coordinates,b_coordinates are light data,got by specific light param
 * @param [in]  r_coordinates
 * @param [in]  g_coordinates
 * @param [in]  b_coordinates
 * @param [in]  cct
 * @param [out] hsv   : lds_color_conversion_hsv_info_t
 * @return status
 **/
lds_status_t lds_color_conversion_cct_to_hsv(const lds_xy_t* r_coordinates, const lds_xy_t* g_coordinates,
                                             const lds_xy_t* b_coordinates, float cct,
                                             lds_color_conversion_hsv_info_t* hsv);

#endif  //EXTENDEDCOLOR_LIGHT


#ifdef __cplusplus
}
#endif

#endif  // COMPONENTS_LDS_COLOR_CONVERSION_INC_LDS_COLOR_CONVERSION_H_
