#ifndef _LDS_ATTRIBUTE_WRAPPERS_H_
#define _LDS_ATTRIBUTE_WRAPPERS_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "lds_error_codes.h"
#include <stdint.h>
#include <stdbool.h>

lds_status_t lds_wrapper_attribute_server_write(uint8_t endpoint, uint16_t cluster, uint16_t attributeID, uint8_t* dataPtr, uint8_t dataType);
lds_status_t lds_wrapper_attribute_server_read(uint8_t endpoint, uint16_t cluster, uint16_t attributeID, uint8_t* dataPtr, uint8_t readLength);
lds_status_t lds_wrapper_get_reset_info(uint8_t *reset_cause);

#ifdef __cplusplus
}
#endif 

#endif // _LDS_ATTRIBUTE_WRAPPERS_H_
