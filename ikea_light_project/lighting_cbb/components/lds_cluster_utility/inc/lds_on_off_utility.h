#ifndef _COMPONENT_LDS_ON_OFF_UTILITY_
#define _COMPONENT_LDS_ON_OFF_UTILITY_

#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include "lds_error_codes.h"

lds_status_t lds_onoff_util_read(uint8_t endpoint, bool* onoff);
lds_status_t lds_onoff_util_write(uint8_t endpoint, bool onoff);
lds_status_t lds_onoff_util_update(uint8_t endpoint, bool onoff);
lds_status_t lds_onoff_util_startup(uint8_t endpoint);
lds_status_t lds_onoff_util_read_global_scene_control(uint8_t endpoint, bool* global_scene_control);
lds_status_t lds_onoff_util_update_global_scene_control(uint8_t endpoint, bool global_scene_control);
lds_status_t lds_onoff_util_read_on_time(uint8_t endpoint, uint16_t* on_time);
lds_status_t lds_onoff_util_update_on_time(uint8_t endpoint, uint16_t on_time);
lds_status_t lds_onoff_util_read_off_wait_time(uint8_t endpoint, uint16_t* off_wait_time);
lds_status_t lds_onoff_util_update_off_wait_time(uint8_t endpoint, uint16_t off_wait_time);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif