/********************************************************************************************************
 * @file    private.c
 *
 * @brief   This is the source file for private
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
 *******************************************************************************************************/
#if (__PROJECT_TL_PLUG__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zcl_include.h"
#include "samplePlug.h"
#include "private.h"

#if PRIVATE_FEAT
/**********************************************************************
 * LOCAL CONSTANTS
 */
#define IKEA_ZCL_CMD_STEP_SCENE		0x07
#define IKEA_ZCL_CMD_MOVE_SCENE		0x08
#define IKEA_ZCL_CMD_STOP_SCENE		0x09

#define IKEA_SCENE_MODE_UP			0x00
#define IKEA_SCENE_MODE_DOWN		0x01
#define IKEA_SCENE_MODE_DEFAULT		0x02

#define IKEA_SCENE_IDX_MAX			8

/**********************************************************************
 * TYPEDEFS
 */
typedef struct{
	u8 mode;
	u8 stepSize;
	u16 transTime;
}ikea_stepScene_t;

typedef struct _attribute_packed_{
	u8 mode;
	u16 transTime;
}ikea_moveScene_t;

typedef struct{
	u16 holdTime;
}ikea_stopScene_t;

typedef struct{
	ev_timer_event_t *timerEvt;
	u16 transTime;
	s8 sceneIdx;
	s8 step;
}ikea_sceneInfo_t;

/**********************************************************************
 * FUNCTIONS
 */
void private_zclAddGroupCmdHandler(u8 endpoint, u16 srcAddr, u16 groupId)
{
	printf("rcv addGroup: ep = %x, src = %x, groupId = %x\n", endpoint, srcAddr, groupId);
}

static void ikea_stepSceneReqHandler(u8 ep, ikea_stepScene_t *pStepScene)
{
	printf("stepScene: ep = %d\n", ep);
}

static void ikea_moveSceneReqHandler(u8 ep, ikea_moveScene_t *pMoveScene)
{
	printf("moveScene: ep = %d\n", ep);
}

static void ikea_stopSceneReqHandler(u8 ep, ikea_stopScene_t *pStopScene)
{
	printf("stopScene: ep = %d\n", ep);
}

status_t private_sceneReqHandler(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	status_t status = ZCL_STA_SUCCESS;

	switch(cmdId){
		case IKEA_ZCL_CMD_STEP_SCENE:
			ikea_stepSceneReqHandler(pAddrInfo->dstEp, (ikea_stepScene_t *)cmdPayload);
			break;
		case IKEA_ZCL_CMD_MOVE_SCENE:
			ikea_moveSceneReqHandler(pAddrInfo->dstEp, (ikea_moveScene_t *)cmdPayload);
			break;
		case IKEA_ZCL_CMD_STOP_SCENE:
			ikea_stopSceneReqHandler(pAddrInfo->dstEp, (ikea_stopScene_t *)cmdPayload);
			break;
		default:
			status = ZCL_STA_UNSUP_MANU_CLUSTER_COMMAND;
	}

	return status;
}
#endif

#endif	/* #if (__PROJECT_TL_PLUG__) */
