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
#if (__PROJECT_TL_LIGHT__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zcl_include.h"
#include "sampleLight.h"
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
	ev_timer_event_t *checkTimerEvt;
	u16 levelSum;
	u8 levelNum;
	u8 onLightNum;
	u8 offLightNum;
}lightNumCheck_t;

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
 * LOCAL VARIABLES
 */
static lightNumCheck_t lightNumCheck = {NULL, 0, 0};
static ikea_sceneInfo_t ikeaSceneInfo;

const u16 ikea_colors_CIE_1931[][2] = {
	{30015, 26870},		// 0.4580, 0.4100 : 2700K
	{25022, 24884},		// 0.3818, 0.3797 : 4000K
	{32886, 27217},		// 0.5018, 0.4153 : 2200K
#if COLOR_RGB_SUPPORT
	{35848, 26214},		// 0.5470. 0.4000 : 1780K
	{38011, 24904},		// 0.5800, 0.3800 : Warm Ambar
	{40632, 22282},		// 0.6200, 0.3400 : Dark Peach
	{32768, 15729},		// 0.5000, 0.2400 : Saturated Pink
	{22282, 12452},		// 0.3400, 0.1900 : Light Purple
	{13107, 6554},		// 0.2000, 0.1000 : Light Blue
#endif
};

/**********************************************************************
 * FUNCTIONS
 */
extern void sampleLight_moveToColorProcess(zcl_colorCtrlMoveToColorCmd_t *cmd);

static s32 private_lightNumCheckTimerCb(void *arg)
{
	printf("checkTimer:\n");

	if(lightNumCheck.onLightNum || lightNumCheck.offLightNum || lightNumCheck.levelNum){
#ifdef ZCL_LEVEL_CTRL
		if(lightNumCheck.levelNum){
			printf("lvl = %d, num = %d\n", lightNumCheck.levelSum, lightNumCheck.levelNum);

			u8 level = lightNumCheck.levelSum / lightNumCheck.levelNum;

			zcl_levelAttr_t *pLevel = zcl_levelAttrGet();
			pLevel->curLevel = level;
		}
#endif

		zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet();
		bool onOff = pOnOff->onOff;
		if(lightNumCheck.onLightNum != lightNumCheck.offLightNum){
			printf("onNum = %d, offNum = %d\n",
					lightNumCheck.onLightNum, lightNumCheck.offLightNum);

			onOff = lightNumCheck.onLightNum > lightNumCheck.offLightNum ? 1 : 0;
		}

		sampleLight_onOffUpdate(onOff);
	}

	lightNumCheck.checkTimerEvt = NULL;
	return -1;
}

#if 0
void ikea_sceneUpdate(u8 endpoint, u16 groupId)
{
	addScene_t addScene;
	TL_SETSTRUCTCONTENT(addScene, 0);

	u8 stored = 0xff;
	if(nv_flashReadNew(1, NV_MODULE_APP, NV_ITEM_APP_PRIVATE_SCENE_STORED, 1, &stored) == NV_SUCC){
		if(stored == 1){
			return;
		}
	}else{
		stored = 1;
		nv_flashWriteNew(1, NV_MODULE_APP, NV_ITEM_APP_PRIVATE_SCENE_STORED, 1, &stored);
	}

	for(u8 i = 0; i < 9; i++){
		addScene.scene.sceneId = i + 1;
		addScene.scene.groupId = groupId;

		u16 x = ikea_colors_CIE_1931[i][0];
		u16 y = ikea_colors_CIE_1931[i][1];

		u8 extLen = 0;
		addScene.scene.extField[extLen++] = LO_UINT16(ZCL_CLUSTER_LIGHTING_COLOR_CONTROL);
		addScene.scene.extField[extLen++] = HI_UINT16(ZCL_CLUSTER_LIGHTING_COLOR_CONTROL);
		addScene.scene.extField[extLen++] = ZCL_COLOR_MODE_CURRENT_X_Y;
		addScene.scene.extField[extLen++] = ZCL_COLOR_MODE_CURRENT_X_Y;
		addScene.scene.extField[extLen++] = 4;
		addScene.scene.extField[extLen++] = LO_UINT16(x);
		addScene.scene.extField[extLen++] = HI_UINT16(x);
		addScene.scene.extField[extLen++] = LO_UINT16(y);
		addScene.scene.extField[extLen++] = HI_UINT16(y);
		addScene.scene.extFieldLen = extLen;

		zcl_scene_addSceneEntry(endpoint, &addScene.scene);
	}

	extern nv_sts_t zcl_scenesSave(u8 endpoint);
	/* scenes save */
	zcl_scenesSave(endpoint);
}
#endif

void private_zclAddGroupCmdHandler(u8 endpoint, u16 srcAddr, u16 groupId)
{
	printf("rcv addGroup: ep = %x, src = %x, groupId = %x\n", endpoint, srcAddr, groupId);

#if 0
	ikea_sceneUpdate(endpoint, groupId);
#endif

	epInfo_t dstEpInfo;
	TL_SETSTRUCTCONTENT(dstEpInfo, 0);

	dstEpInfo.dstAddrMode = APS_SHORT_GROUPADDR_NOEP;
	dstEpInfo.dstAddr.shortAddr = groupId;
	dstEpInfo.profileId = HA_PROFILE_ID;

	zclReadCmd_t *pReadCmd = (zclReadCmd_t *)ev_buf_allocate(sizeof(zclReadCmd_t) + sizeof(u16));
	if(pReadCmd){
		pReadCmd->numAttr = 1;

		pReadCmd->attrID[0] = ZCL_ATTRID_ONOFF;
		zcl_sendReadCmd(SAMPLE_LIGHT_ENDPOINT, &dstEpInfo, ZCL_CLUSTER_GEN_ON_OFF, TRUE, ZCL_FRAME_CLIENT_SERVER_DIR, pReadCmd);

#ifdef ZCL_LEVEL_CTRL
		pReadCmd->attrID[0] = ZCL_ATTRID_LEVEL_CURRENT_LEVEL;
		zcl_sendReadCmd(SAMPLE_LIGHT_ENDPOINT, &dstEpInfo, ZCL_CLUSTER_GEN_LEVEL_CONTROL, TRUE, ZCL_FRAME_CLIENT_SERVER_DIR, pReadCmd);
#endif

		ev_buf_free((u8 *)pReadCmd);
	}

	lightNumCheck.onLightNum = 0;
	lightNumCheck.offLightNum = 0;
#ifdef ZCL_LEVEL_CTRL
	lightNumCheck.levelSum = 0;
	lightNumCheck.levelNum = 0;
#endif

	if(lightNumCheck.checkTimerEvt){
		TL_ZB_TIMER_CANCEL(&lightNumCheck.checkTimerEvt);
	}
	lightNumCheck.checkTimerEvt = TL_ZB_TIMER_SCHEDULE(private_lightNumCheckTimerCb, NULL, 1000);
}

void private_zclReadRspCmdHandler(u16 clusterId, zclReadRspCmd_t *pReadRspCmd)
{
    printf("rcv readRsp: cId = %x\n", clusterId);

    if((clusterId != ZCL_CLUSTER_GEN_ON_OFF) &&
       (clusterId != ZCL_CLUSTER_GEN_LEVEL_CONTROL)){
    	return;
    }

    for(u8 i = 0; i < pReadRspCmd->numAttr; i++){
    	printf("attId = %x, sta = %x\n",
    			pReadRspCmd->attrList[i].attrID,
    			pReadRspCmd->attrList[i].status);

    	if((pReadRspCmd->attrList[i].attrID == ZCL_ATTRID_ONOFF) &&
    	   (clusterId == ZCL_CLUSTER_GEN_ON_OFF)){
			if(pReadRspCmd->attrList[i].status == ZCL_STA_SUCCESS){
				//on/off
				if(pReadRspCmd->attrList[i].data[0]){
					lightNumCheck.onLightNum++;
				}else{
					lightNumCheck.offLightNum++;
				}

				printf("val = %x, onNum = %d, offNum = %d\n",
						pReadRspCmd->attrList[i].data[0],
						lightNumCheck.onLightNum, lightNumCheck.offLightNum);
			}
    	}
#ifdef ZCL_LEVEL_CTRL
    	else if((pReadRspCmd->attrList[i].attrID == ZCL_ATTRID_LEVEL_CURRENT_LEVEL) &&
    			 (clusterId == ZCL_CLUSTER_GEN_LEVEL_CONTROL)){
    		if(pReadRspCmd->attrList[i].status == ZCL_STA_SUCCESS){
    			//level
    			lightNumCheck.levelNum++;
    			lightNumCheck.levelSum += pReadRspCmd->attrList[i].data[0];

    			printf("val = %d, num = %d, sum = %d\n",
    					pReadRspCmd->attrList[i].data[0],
						lightNumCheck.levelNum, lightNumCheck.levelSum);
    		}
    	}
#endif
    }
}

static s32 ikea_sceneTimerCb(void *arg)
{
	u8 curSceneIdx = ikeaSceneInfo.sceneIdx;
	ikeaSceneInfo.sceneIdx = curSceneIdx + ikeaSceneInfo.step;
	if(ikeaSceneInfo.sceneIdx > IKEA_SCENE_IDX_MAX){
		ikeaSceneInfo.sceneIdx = 0;
	}else if(ikeaSceneInfo.sceneIdx < 0){
		ikeaSceneInfo.sceneIdx = IKEA_SCENE_IDX_MAX;
	}

	printf("moveScene: curIdx = %d, dstIdx = %d\n", curSceneIdx, ikeaSceneInfo.sceneIdx);

#if COLOR_RGB_SUPPORT
	zcl_colorCtrlMoveToColorCmd_t move2Color;

	move2Color.colorX = ikea_colors_CIE_1931[(u8)ikeaSceneInfo.sceneIdx][0];
	move2Color.colorY = ikea_colors_CIE_1931[(u8)ikeaSceneInfo.sceneIdx][1];
	move2Color.transitionTime = ikeaSceneInfo.transTime;
	move2Color.optPresent = 0;

	sampleLight_moveToColorProcess(&move2Color);
#endif

	return 0;
}

static void ikea_sceneTimerStop(void)
{
	if(ikeaSceneInfo.timerEvt){
		TL_ZB_TIMER_CANCEL(&ikeaSceneInfo.timerEvt);
	}
}

static void ikea_stepSceneReqHandler(ikea_stepScene_t *pStepScene)
{
	if(pStepScene->mode == IKEA_SCENE_MODE_UP){
		ikeaSceneInfo.step = pStepScene->stepSize;
	}else if(pStepScene->mode == IKEA_SCENE_MODE_DOWN){
		ikeaSceneInfo.step = -pStepScene->stepSize;
	}else if(pStepScene->mode == IKEA_SCENE_MODE_DEFAULT){

	}

	u8 curSceneIdx = ikeaSceneInfo.sceneIdx;
	ikeaSceneInfo.sceneIdx = curSceneIdx + ikeaSceneInfo.step;

	if(ikeaSceneInfo.sceneIdx > IKEA_SCENE_IDX_MAX){
		ikeaSceneInfo.sceneIdx = IKEA_SCENE_IDX_MAX;
	}else if(ikeaSceneInfo.sceneIdx < 0){
		ikeaSceneInfo.sceneIdx = 0;
	}

	printf("stepScene: curIdx = %d, dstIdx = %d\n", curSceneIdx, ikeaSceneInfo.sceneIdx);

#if COLOR_RGB_SUPPORT
	zcl_colorCtrlMoveToColorCmd_t move2Color;

	move2Color.colorX = ikea_colors_CIE_1931[(u8)ikeaSceneInfo.sceneIdx][0];
	move2Color.colorY = ikea_colors_CIE_1931[(u8)ikeaSceneInfo.sceneIdx][1];
	move2Color.transitionTime = pStepScene->transTime;
	move2Color.optPresent = 0;

	sampleLight_moveToColorProcess(&move2Color);
#endif
}

static void ikea_moveSceneReqHandler(ikea_moveScene_t *pMoveScene)
{
	if(pMoveScene->mode == IKEA_SCENE_MODE_UP){
		ikeaSceneInfo.step = 1;
	}else if(pMoveScene->mode == IKEA_SCENE_MODE_DOWN){
		ikeaSceneInfo.step = -1;
	}else if(pMoveScene->mode == IKEA_SCENE_MODE_DEFAULT){

	}

	u8 curSceneIdx = ikeaSceneInfo.sceneIdx;
	ikeaSceneInfo.transTime = pMoveScene->transTime;
	ikeaSceneInfo.sceneIdx = curSceneIdx + ikeaSceneInfo.step;

	if(ikeaSceneInfo.sceneIdx > IKEA_SCENE_IDX_MAX){
		ikeaSceneInfo.sceneIdx = 0;
	}else if(ikeaSceneInfo.sceneIdx < 0){
		ikeaSceneInfo.sceneIdx = IKEA_SCENE_IDX_MAX;
	}

	printf("moveScene: curIdx = %d, dstIdx = %d\n", curSceneIdx, ikeaSceneInfo.sceneIdx);

#if COLOR_RGB_SUPPORT
	zcl_colorCtrlMoveToColorCmd_t move2Color;

	move2Color.colorX = ikea_colors_CIE_1931[(u8)ikeaSceneInfo.sceneIdx][0];
	move2Color.colorY = ikea_colors_CIE_1931[(u8)ikeaSceneInfo.sceneIdx][1];
	move2Color.transitionTime = pMoveScene->transTime;
	move2Color.optPresent = 0;

	sampleLight_moveToColorProcess(&move2Color);
#endif

	ikea_sceneTimerStop();
	ikeaSceneInfo.timerEvt = TL_ZB_TIMER_SCHEDULE(ikea_sceneTimerCb, NULL, 100);
}

static void ikea_stopSceneReqHandler(ikea_stopScene_t *pStopScene)
{
	ikea_sceneTimerStop();

	ikeaSceneInfo.transTime = 0;
	ikeaSceneInfo.step = 0;

	printf("stopScene\n");
}

status_t private_sceneReqHandler(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	status_t status = ZCL_STA_SUCCESS;

	switch(cmdId){
		case IKEA_ZCL_CMD_STEP_SCENE:
			ikea_stepSceneReqHandler((ikea_stepScene_t *)cmdPayload);
			break;
		case IKEA_ZCL_CMD_MOVE_SCENE:
			ikea_moveSceneReqHandler((ikea_moveScene_t *)cmdPayload);
			break;
		case IKEA_ZCL_CMD_STOP_SCENE:
			ikea_stopSceneReqHandler((ikea_stopScene_t *)cmdPayload);
			break;
		default:
			status = ZCL_STA_UNSUP_MANU_CLUSTER_COMMAND;
	}

	return status;
}
#endif

#endif  /* __PROJECT_TL_LIGHT__ */
