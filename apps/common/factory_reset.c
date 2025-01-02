/********************************************************************************************************
 * @file    factory_reset.c
 *
 * @brief   This is the source file for factory_reset
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *			All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/

#include "tl_common.h"
#include "factory_reset.h"
#include "zb_api.h"
#include "lds_aging_test.h"
#include "lds_log.h"
//#include "lds_driver_minitrim.h"
#include "lds_light_effect.h"

#define FACTORY_RESET_POWER_CNT_THRESHOLD		6		//times
#define FTM_EXIT_AGING_TEST_CNT					6
#define EXIT_FACTORY_TEST_POWER_CNT_THRESHOLD	9
#define TRIGGER_JOIN_NETWORK_CNT				12
#define TRIGGER_JOIN_NETWORK_FLAG				0xA5
#define TRIGGER_DEFAULT_VALUE					0xFF
#define FACTORY_RESET_TIMEOUT					2500	// ms	//second
#define AGING_FACTORY_RESET_TIMEOUT				3500	// ms

ev_timer_event_t *factoryRst_timerEvt = NULL;
u8 factoryRst_powerCnt = 0;
bool factoryRst_exist = FALSE;

nv_sts_t factoryRst_powerCntSave(void){
	nv_sts_t st = NV_SUCC;
#if NV_ENABLE
	st = nv_flashWriteNew(1, NV_MODULE_APP, NV_ITEM_APP_POWER_CNT, 1, &factoryRst_powerCnt);
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
	return st;
}

nv_sts_t factoryRst_powerCntRestore(void){
	nv_sts_t st = NV_SUCC;
#if NV_ENABLE
	st = nv_flashReadNew(1, NV_MODULE_APP, NV_ITEM_APP_POWER_CNT, 1, &factoryRst_powerCnt);
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
	return st;
}

static uint8_t test = 0;
nv_sts_t lds_trigger_join_network_save(uint8_t flag)
{
	nv_sts_t st = NV_SUCC;
#if NV_ENABLE
	st = nv_flashWriteNew(1, NV_MODULE_APP, NV_ITEM_APP_JOIN_NETWORK_ENABLE, 1, &flag);
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif

	return st;
}

uint8_t lds_trigger_join_network_flag_get(void)
{
	nv_sts_t st = NV_SUCC;
//	uint8_t value = 0;

#if NV_ENABLE
	st = nv_flashReadNew(1, NV_MODULE_APP, NV_ITEM_APP_JOIN_NETWORK_ENABLE, 1, &test);
	if (st != NV_SUCC)
	{
//		printf("NV flash read fail\r\n");
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif

	return test;
//	st = (test == TRIGGER_JOIN_NETWORK_FLAG) ? NV_SUCC : NV_ENABLE_PROTECT_ERROR;
//
//	return st;
}

#if 1
#define FACTORY_TEST	1
void ldsTriggerJoinEffect(void)
{
//    ldsMinitrimInit();
//    ldsLightEffectInit();
	ldsLightTriggerJoinNetworkEnableStart();
}

static s32 factoryRst_timerCb(void *arg){
	if (ldsDeviceAgingFunctionTestDone())
	{
		if(factoryRst_powerCnt == FACTORY_RESET_POWER_CNT_THRESHOLD){
			/* here is just a mark, wait for device announce and then perform factory reset. */
			zb_factoryReset();
			uint8_t value = TRIGGER_DEFAULT_VALUE;
			test = TRIGGER_DEFAULT_VALUE;
			lds_trigger_join_network_save(value);
		}
		else if(factoryRst_powerCnt == TRIGGER_JOIN_NETWORK_CNT){
			ldsTriggerJoinEffect();
		}
	}

	LDS_LOG_I("factoryRst_timerCb test2222 :%d\n", factoryRst_powerCnt);
	factoryRst_powerCnt = 0;
	factoryRst_powerCntSave();

	factoryRst_timerEvt = NULL;
	return -1;
}

void factoryRst_handler(void){
	if(factoryRst_exist){
		factoryRst_exist = FALSE;
		zb_factoryReset();
	}
}

void factoryRst_init(void){
	uint16_t reset_timeout = FACTORY_RESET_TIMEOUT;

	factoryRst_powerCntRestore();
	factoryRst_powerCnt++;
	factoryRst_powerCntSave();

#if FACTORY_TEST
	if (ldsDeviceAgingFunctionTestDone())
	{
		if (factoryRst_powerCnt == FACTORY_RESET_POWER_CNT_THRESHOLD){
			reset_timeout = 1700;
			/* here is just a mark, wait for device announce and then perform factory reset. */
//			ldsLightEffectFactoryResetStart();
//			zb_factoryReset();
		}
		else if (factoryRst_powerCnt == TRIGGER_JOIN_NETWORK_CNT)
		{
			reset_timeout = 1200;
			uint8_t value = TRIGGER_JOIN_NETWORK_FLAG;
			lds_trigger_join_network_save(value);
		}
	}
	else
	{
		LDS_LOG_I("factoryRst_init test222: %d, %d, %d", ldsDeviceAgingFunctionTestDone(), ldsDeviceAgingTestIsDone(), factoryRst_powerCnt);

		if (!ldsDeviceAgingTestIsDone())
		{
			reset_timeout = AGING_FACTORY_RESET_TIMEOUT;
			LDS_LOG_I("factoryRst_init aging test1111: %d\r\n", factoryRst_powerCnt, reset_timeout);
			if (factoryRst_powerCnt >= EXIT_AGING_COUNT)
			{
				ldsAgingTestExit();
				factoryRst_powerCnt = 0;
				factoryRst_powerCntSave();
//				ldsTriggerJoinEffect();
			}
			else if (factoryRst_powerCnt == FACTORY_RESET_POWER_CNT_THRESHOLD)
			{
				ldsAgainEnterAgingTest();
				factoryRst_powerCntSave();
			}
		}
		else
		{
//			LDS_LOG_I("factoryRst_init function test3333: %d\r\n", factoryRst_powerCnt, reset_timeout);
			if (factoryRst_powerCnt == EXIT_FACTORY_TEST_POWER_CNT_THRESHOLD)
			{
				ldsFactoryTestExit();
				factoryRst_powerCnt = 0;
				factoryRst_powerCntSave();
			}
		}
	}
#endif

	LDS_LOG_I("factory rst init: %d, %d, %x\n", ldsDeviceAgingTestIsDone(), factoryRst_powerCnt, lds_trigger_join_network_flag_get());

	if(factoryRst_timerEvt){
		TL_ZB_TIMER_CANCEL(&factoryRst_timerEvt);
	}

	factoryRst_timerEvt = TL_ZB_TIMER_SCHEDULE(factoryRst_timerCb, NULL, reset_timeout);
//	factoryRst_timerEvt = TL_ZB_TIMER_SCHEDULE(factoryRst_timerCb, NULL, FACTORY_RESET_TIMEOUT);
}
#else
#define FACTORY_TEST	1
static s32 factoryRst_timerCb(void *arg){
	printf("factoryRst_timerCb test2222 :%d\n", factoryRst_powerCnt);
	if(factoryRst_powerCnt == FACTORY_RESET_POWER_CNT_THRESHOLD){
		/* here is just a mark, wait for device announce and then perform factory reset. */
//		factoryRst_exist = TRUE;

		ldsLightEffectFactoryResetStart();
		nv_resetToFactoryNew();
	}

	factoryRst_powerCnt = 0;
	factoryRst_powerCntSave();

	factoryRst_timerEvt = NULL;
	return -1;
}



void factoryRst_init(factoryRstCb_t cb)
{
	uint16_t reset_timeout = FACTORY_RESET_TIMEOUT;

	factoryRst_powerCntRestore();
	factoryRst_powerCnt++;
	factoryRst_powerCntSave();

#if FACTORY_TEST
	if (!ldsDeviceAgingTestIsDone())
	{
		reset_timeout = AGING_FACTORY_RESET_TIMEOUT;
//		ev_on_timer(factoryRst_timerEvt, reset_timeout);
//		printf("factoryRst_init aging test1111: %d\r\n", factoryRst_powerCnt, reset_timeout);
		if (factoryRst_powerCnt >= EXIT_AGING_COUNT)
		{
			ldsAgingTestExit();
			factoryRst_powerCnt = 0;
			factoryRst_powerCntSave();
		}
	}
	else
	{
		if (factoryRst_powerCnt == FACTORY_RESET_POWER_CNT_THRESHOLD){
			reset_timeout = 300;

//			if (cb)
//			{
//				cb();
//			}

//			nv_resetToFactoryNew();
//			factoryRst_powerCnt = 0;
//			factoryRst_powerCntSave();
		}
	}
#endif

	printf("factory rst init: %d, %d\n", ldsDeviceAgingTestIsDone(), factoryRst_powerCnt);

	if(factoryRst_timerEvt){
		TL_ZB_TIMER_CANCEL(&factoryRst_timerEvt);
	}

	factoryRst_timerEvt = TL_ZB_TIMER_SCHEDULE(factoryRst_timerCb, NULL, reset_timeout);
//	factoryRst_timerEvt = TL_ZB_TIMER_SCHEDULE(factoryRst_timerCb, NULL, FACTORY_RESET_TIMEOUT);
}
#endif
