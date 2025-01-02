#ifndef _LDS_LIGHT_SOURCE_PARAMS_H_
#define _LDS_LIGHT_SOURCE_PARAMS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


typedef enum
{
	LDS_RED_SET_OPCODE = 0x0101,
	LDS_GREEN_SET_OPCODE,
	LDS_BLUE_SET_OPCODE,
	LDS_WHITE_SET_OPCODE,
	LDS_CODE_SET_OPCODE,
	LDS_TEMP_SET_OPCODE,
	LFS_MAX_SET_OPCODE
} LDS_LIGHT_SOURCE_ATTRIBUTE_E;


void ldsLightSourceAttributeCollection(uint8_t *value, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif
