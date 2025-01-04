#ifndef _LDS_AGING_TEST_H_
#define _LDS_AGING_TEST_H_

#include "lds_device_config.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define AGING_STORE_AREA			(0x3a8000)
#define FTM_RGBTW_CHECK_AREA		(0x3a9000)

#define AGING_DEFAULT_FLAG      	0xFFFFFFFF  // driving phase
#define AGING_STAGE_FLAG     		0xAA55AA55  // aging phase
#define AGING_FACTORY_TEST_FLAG		0xA5A5A5A5	// factory function test
#define AGING_TEST_FINISH_FLAG  	0x00000000  // aging finish
#define EXIT_AGING_COUNT            (13)

#define FTM_CMD_SET_BIND			0x0000
#define FTM_CMD_SET_ON				0x0101
#define FTM_CMD_SET_OFF				0x0102
#define FTM_CMD_SET_DIM				0x0201
#define FTM_CMD_SET_CCT				0x0301
#define FTM_CMD_SET_CCT_AND_DIM		0x0302
#define FTM_CMD_SET_RGB				0x0401
#define FTM_CMD_SET_RGB_XY			0x0402
#define FTM_CMD_SET_CALI_RESULT		0x0505
#define FTM_CMD_TEST_EXIT			0xA5A5
#define FTM_CMD_AGAIN_ENTER_TEST	0xA6A6

#ifdef EXTENDEDCOLOR_LIGHT
#ifdef RGBTW
#define PWM_ID_MAX					5
#else
#define PWM_ID_MAX					4
#endif
#endif

typedef enum {
    AGING_MIN_TEMPERATURE = 0,
    AGING_DEFAULT_TEMPERATURE,
    AGING_MEDIUM_TEMPERATURE,
    AGING_MAX_TEMPERATURE,
    AGING_FINISH_STAGE,
} LDS_CCT_AGING_STAGE_E;

typedef enum {
    AGING_RGBTW_STAGE = 0,
	AGING_RGB_STAGE,
	AGING_RGB_MIN_TEMPERATURE,
	AGING_RGB_DEFAULT_TEMPERATURE,
	AGING_RGB_MAX_TEMPERATURE,
	AGING_RGB_MEDIUM_TEMPERATURE,
    AGING_RGB_FINISH_STAGE,
} LDS_RGB_AGING_STAGE_E;

typedef enum {
	LDS_RGB_SET_R = 0,
	LDS_RGB_SET_G,
	LDS_RGB_SET_B,
	LDS_RGB_SET_W,
	LDS_RGB_SET_W2,
} LDS_LIGHT_RGB_SET_E;

typedef enum {
	FTM_CMD_RGB_CALI_CH_R = 0x0500,
	FTM_CMD_RGB_CALI_CH_G,
	FTM_CMD_RGB_CALI_CH_B,
	FTM_CMD_RGB_CALI_CH_W,
	FTM_CMD_RGB_CALI_CH_W2,
} LDS_FTM_CMD_LIGHT_RGB_CALI_E;

typedef enum {
	LDS_RGB_CALI_OK = 0,
	LDS_RGB_CALI_NG,
	LDS_RGB_CALI_UNDONE,
} LDS_RGB_CALI_RESULT_E;

#pragma pack (1)
typedef struct {
	uint8_t lid;
	uint8_t mac[6];
} lds_dongle_info_t;

typedef struct {
	uint32_t aging_flag;
	uint8_t aging_state;
	uint16_t  time_count;
	uint8_t rsv[9];
//	uint8_t install_code[16];
	lds_dongle_info_t info;
} lds_aging_state_t;
#pragma pack ()


bool ldsDeviceAgingFunctionTestDone(void);

bool ldsDeviceAgingTestIsDone(void);

void ldsCctDeviceSetup(uint8_t onoff, uint8_t level, uint16_t temperatureMired);

bool ldsDeviceAgingTestInit(void);

void ldsDeviceFactoryFunctionTest(uint16_t opcode, uint8_t *buf);

void ldsAgingTestExit(void);

void ldsFactoryTestExit(void);

void ldsAgainEnterAgingTest(void);

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#endif
