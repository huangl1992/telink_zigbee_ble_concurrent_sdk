/*
 * @Author: chenkunlin chenkunlin@leedarson.com
 * @Date: 2024-05-30 16:20:07
 * @LastEditors: chenkunlin chenkunlin@leedarson.com
 * @LastEditTime: 2024-05-30 16:21:02
 * @FilePath: /chenkl/lighting_cbb_dev/components/lds_cluster_utility/inc/lds_level_utility.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _COMPONENT_LDS_LEVEL_UTILITY_
#define _COMPONENT_LDS_LEVEL_UTILITY_

#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

#include "lds_error_codes.h"
#include <stdint.h>
#include <stdbool.h>

#define LDS_UTIL_LEVEL_CONTROL_MINIMUM_LEVEL 1
#define LDS_UTIL_LEVEL_CONTROL_MAXIMUM_LEVEL 254
#define LDS_UTIL_LEVEL_CONTROL_UNDEFINED_LEVEL 0xFF
#define LDS_UTIL_LEVEL_CONTROL_UNDEFINED_TRANSITION_TIME 0xFFFF


// Reads level attribute
lds_status_t lds_lvl_util_read(uint8_t endpoint, uint8_t* level);

// Writes level attibute without checking, see lds_lvl_util_update for write when needed
lds_status_t lds_lvl_util_write(uint8_t endpoint, uint8_t level);

// Updates the level attribute if needed
lds_status_t lds_lvl_util_update(uint8_t endpoint, uint8_t level);

// Reads startup level attribute
lds_status_t lds_lvl_util_read_startup(uint8_t endpoint, uint8_t* level);

// Updates current level attribute to start up level attribute if needed
lds_status_t lds_lvl_util_init_to_startup(uint8_t endpoint);

/* Read the Attribute Options belonging to Level Control Cluster
 *
 * the attribute Options of cluster Level Control is a bitmap8, 8-bit bitmap.
 * Default is 0b0000 0000, range is 0b0000 00xx.
 */
lds_status_t lds_lvl_util_read_options(uint8_t endpoint, uint8_t* options);

/*
 * Write the Attribute Options belonging to Level Control Cluster
 * the attribute Options of cluster Level Control is a bitmap8, 8-bit bitmap.
 * Default is 0b0000 0000, range is 0b0000 00xx.
 */
lds_status_t lds_lvl_util_write_options(uint8_t endpoint, uint8_t options);

// Read the Attributes for on/off transtion time
lds_status_t lds_lvl_util_read_on_off_transition_time(uint8_t endpoint, uint16_t* time);

// Sets onLevel attribute
lds_status_t lds_lvl_util_set_on(uint8_t endpoint, uint8_t level);

// Reads the onlevel attribute
lds_status_t lds_lvl_util_read_on(uint8_t endpoint, uint8_t* level);

// Read the remaining time attribute
lds_status_t lds_lvl_util_read_remaining_time(uint8_t endpoint, uint16_t* time);

// write the remaining time attribute
lds_status_t lds_lvl_util_write_remaining_time(uint8_t endpoint, uint16_t time);

// Updates the remaining time attribute if needed
lds_status_t lds_lvl_util_update_remaining_time(uint8_t endpoint, uint16_t time);

// Updates the remaining time in milli seconds to the attribute if needed
lds_status_t lds_lvl_util_update_remaining_time_ms(uint8_t endpoint, uint16_t time);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif
