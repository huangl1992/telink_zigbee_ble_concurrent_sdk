/********************************************************************************************************
 * @file    zcl_sampleLightCb.c
 *
 * @brief   This is the source file for zcl_sampleLightCb
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
#include "zb_api.h"
#include "zcl_include.h"
#include "ota.h"
#include "sampleLight.h"
#include "sampleLightCtrl.h"
#include "lds_device_config.h"
#include "lds_light_effect.h"
#include "lds_aging_test.h"
#include "lds_on_off_utility.h"
#include "lds_level_utility.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */



/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * LOCAL FUNCTIONS
 */
#ifdef ZCL_READ
static void sampleLight_zclReadRspCmd(u16 clusterId, zclReadRspCmd_t *pReadRspCmd);
#endif
#ifdef ZCL_WRITE
static void sampleLight_zclWriteReqCmd(u16 clusterId, zclWriteCmd_t *pWriteReqCmd);
static void sampleLight_zclWriteRspCmd(zclWriteRspCmd_t *pWriteRspCmd);
#endif
#ifdef ZCL_REPORT
static void sampleLight_zclCfgReportCmd(zclCfgReportCmd_t *pCfgReportCmd);
static void sampleLight_zclCfgReportRspCmd(zclCfgReportRspCmd_t *pCfgReportRspCmd);
static void sampleLight_zclReportCmd(zclReportCmd_t *pReportCmd);
#endif
static void sampleLight_zclDfltRspCmd(zclDefaultRspCmd_t *pDftRspCmd);


/**********************************************************************
 * GLOBAL VARIABLES
 */


/**********************************************************************
 * LOCAL VARIABLES
 */
#ifdef ZCL_IDENTIFY
static ev_timer_event_t *identifyTimerEvt = NULL;
static ev_timer_event_t *identifyDelayTimerEvt = NULL;
#endif

#if DUAL_MODE_WITH_MATTER
#if (LDS_DEFAULT_SCENES_NUMER_OF > 4)
#define SCENE_RSP_NUM	32
#define SCENE_TOTAL_NUM	10
#else
#define SCENE_RSP_NUM	4
#define SCENE_TOTAL_NUM	4
#endif
typedef struct {
	u8 scene[SCENE_RSP_NUM];
	u8 scene_num[SCENE_TOTAL_NUM];
	u8 last_scene_id;
	u8 total_num;
}ldsSceneTable_t;

typedef struct{
	ev_timer_event_t *checkTimerEvt;
	u16 levelSum;
	u8 levelNum;
	u8 onLightNum;
	u8 offLightNum;
	ldsSceneTable_t sceneTable;
}lightNumCheck_t;

static lightNumCheck_t lightNumCheck = {NULL, 0, 0};
bool g_touchlink_flag = false; 							// touchlink effect timeout handle
#endif

/**********************************************************************
 * FUNCTIONS
 */
void sampleLight_zclIdentifyCmdHandler(u8 endpoint, u16 srcAddr, u16 identifyTime);

/*********************************************************************
 * @fn      sampleLight_zclProcessIncomingMsg
 *
 * @brief   Process ZCL Foundation incoming message.
 *
 * @param   pInMsg - pointer to the received message
 *
 * @return  None
 */
void sampleLight_zclProcessIncomingMsg(zclIncoming_t *pInHdlrMsg)
{
//	printf("sampleLight_zclProcessIncomingMsg\n");

	switch(pInHdlrMsg->hdr.cmd)
	{
#ifdef ZCL_READ
		case ZCL_CMD_READ_RSP:
			sampleLight_zclReadRspCmd(pInHdlrMsg->msg->indInfo.cluster_id, pInHdlrMsg->attrCmd);
			break;
#endif
#ifdef ZCL_WRITE
		case ZCL_CMD_WRITE:
		case ZCL_CMD_WRITE_NO_RSP:
			sampleLight_zclWriteReqCmd(pInHdlrMsg->msg->indInfo.cluster_id, pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_WRITE_RSP:
			sampleLight_zclWriteRspCmd(pInHdlrMsg->attrCmd);
			break;
#endif
#ifdef ZCL_REPORT
		case ZCL_CMD_CONFIG_REPORT:
			sampleLight_zclCfgReportCmd(pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_CONFIG_REPORT_RSP:
			sampleLight_zclCfgReportRspCmd(pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_REPORT:
			sampleLight_zclReportCmd(pInHdlrMsg->attrCmd);
			break;
#endif
		case ZCL_CMD_DEFAULT_RSP:
			sampleLight_zclDfltRspCmd(pInHdlrMsg->attrCmd);
			break;
		default:
			break;
	}
}

#ifdef ZCL_READ

static void ldsLightStateSynNumClean(void)
{
//	lightNumCheck.onLightNum = 0;
//	lightNumCheck.offLightNum = 0;
//	lightNumCheck.levelSum = 0;
//	lightNumCheck.levelNum = 0;
	//lightNumCheck.sceneTable
//	memset(&lightNumCheck.sceneTable, 0, sizeof(ldsSceneTable_t));
	memset(&lightNumCheck, 0, sizeof(lightNumCheck_t));
}

static bool ldsLightSceneHandleCheck(void)
{
	if ((lightNumCheck.onLightNum)
		|| (lightNumCheck.offLightNum)
		|| (lightNumCheck.levelNum)
		|| (lightNumCheck.sceneTable.total_num))
	{
		return true;
	}

	return false;
}

#if 0
static u16 ldsLightStateTemperatureMiredGet(void)
{
	u16 temperatureMired = 0;

	if ((lightNumCheck.tempNum.max_temperature_num > lightNumCheck.tempNum.medium_temperature_num)
			&& (lightNumCheck.tempNum.max_temperature_num > lightNumCheck.tempNum.default_temperature_num)
			&& (lightNumCheck.tempNum.max_temperature_num > lightNumCheck.tempNum.min_temperature_num))
	{
		temperatureMired = TEMPERATUREMIREDS_MAX;
	}
	else if ((lightNumCheck.tempNum.medium_temperature_num > lightNumCheck.tempNum.max_temperature_num)
			&& (lightNumCheck.tempNum.medium_temperature_num > lightNumCheck.tempNum.default_temperature_num)
			&& (lightNumCheck.tempNum.medium_temperature_num > lightNumCheck.tempNum.min_temperature_num))
	{
		temperatureMired = MEDIUM_TEMPERATUREMIREDS;
	}
	else if ((lightNumCheck.tempNum.default_temperature_num > lightNumCheck.tempNum.max_temperature_num)
			&& (lightNumCheck.tempNum.default_temperature_num > lightNumCheck.tempNum.medium_temperature_num)
			&& (lightNumCheck.tempNum.default_temperature_num > lightNumCheck.tempNum.min_temperature_num))
	{
		temperatureMired = DEFAULT_TEMPERATUREMIREDS;
	}
	else if ((lightNumCheck.tempNum.min_temperature_num > lightNumCheck.tempNum.max_temperature_num)
			&& (lightNumCheck.tempNum.min_temperature_num > lightNumCheck.tempNum.medium_temperature_num)
			&& (lightNumCheck.tempNum.min_temperature_num > lightNumCheck.tempNum.default_temperature_num))
	{
		temperatureMired = TEMPERATUREMIREDS_MIN;
	}
	else
	{
		temperatureMired = lightNumCheck.tempNum.last_temperature_mireds;
	}

	printf("ldsLightStateTemperatureMiredGet test7777: %d\n", temperatureMired);

	return temperatureMired;
}
#endif
static u8 ldsLightCurrentSceneIndexGet(void)
{
	u8 max_count = 1;
	u8 current_scene = 0;
	int last_frequen_idx = -1;

	for (u8 m = 0; m < lightNumCheck.sceneTable.total_num; m++)
	{
		current_scene = lightNumCheck.sceneTable.scene[m];
		lightNumCheck.sceneTable.scene_num[current_scene]++;

		if ((lightNumCheck.sceneTable.scene_num[current_scene] > max_count))
		{
			max_count = lightNumCheck.sceneTable.scene_num[current_scene];
			last_frequen_idx = current_scene;
		}
		else if (lightNumCheck.sceneTable.scene_num[current_scene] == max_count)
		{
			last_frequen_idx = current_scene;
		}
	}

//	printf("ldsLightCurrentSceneIndexGet test3333:%d, %d, %d, %d,%d\r\n", max_count, last_frequen_idx,current_scene, lightNumCheck.sceneTable.last_scene_id,lightNumCheck.sceneTable.total_num);

	current_scene = last_frequen_idx % LDS_DEFAULT_SCENES_NUMER_OF;

	printf("ldsLightCurrentSceneIndexGet test4444:%d, %d, %d,%d\r\n", max_count, current_scene, lightNumCheck.sceneTable.last_scene_id,lightNumCheck.sceneTable.total_num);
	return current_scene;
}

static void ldsLightSceneTableCheck(u8 scene_id)
{
	lightNumCheck.sceneTable.scene[lightNumCheck.sceneTable.total_num] = scene_id;
//	lightNumCheck.sceneTable.scene_num[scene_id]++;
	lightNumCheck.sceneTable.last_scene_id = scene_id;
	lightNumCheck.sceneTable.total_num++;
}

/*********************************************************************
 * @fn      sampleLight_zclReadRspCmd
 *
 * @brief   Handler for ZCL Read Response command.
 *
 * @param
 *
 * @return  None
 */
static void sampleLight_zclReadRspCmd(u16 clusterId, zclReadRspCmd_t *pReadRspCmd)
{
    printf("rcv readRsp: cId = %x\n", clusterId);

#if DUAL_MODE_WITH_MATTER
    if((clusterId != ZCL_CLUSTER_GEN_ON_OFF)
    	&& (clusterId != ZCL_CLUSTER_GEN_LEVEL_CONTROL)
//		&& (clusterId != ZCL_CLUSTER_LIGHTING_COLOR_CONTROL)
		&& (clusterId != ZCL_CLUSTER_GEN_SCENES)){
    	return;
    }

    for(u8 i = 0; i < pReadRspCmd->numAttr; i++){
//    	printf("attId = %x, sta = %x\n", pReadRspCmd->attrList[i].attrID, pReadRspCmd->attrList[i].status);

    	if((pReadRspCmd->attrList[i].attrID == ZCL_ATTRID_ONOFF) &&
    	   (clusterId == ZCL_CLUSTER_GEN_ON_OFF)){
			if(pReadRspCmd->attrList[i].status == ZCL_STA_SUCCESS){
				//on/off
				if(pReadRspCmd->attrList[i].data[0]){
					lightNumCheck.onLightNum++;
				}else{
					lightNumCheck.offLightNum++;
				}

//				printf("val = %x, onNum = %d, offNum = %d\n",
//						pReadRspCmd->attrList[i].data[0],
//						lightNumCheck.onLightNum, lightNumCheck.offLightNum);
			}
    	}else if((pReadRspCmd->attrList[i].attrID == ZCL_ATTRID_LEVEL_CURRENT_LEVEL) &&
    			 (clusterId == ZCL_CLUSTER_GEN_LEVEL_CONTROL)){
    		if(pReadRspCmd->attrList[i].status == ZCL_STA_SUCCESS){
    			//level
    			lightNumCheck.levelNum++;
    			lightNumCheck.levelSum += pReadRspCmd->attrList[i].data[0];

//    			printf("val = %d, num = %d, sum = %d\n",
//    					pReadRspCmd->attrList[i].data[0],
//						lightNumCheck.levelNum, lightNumCheck.levelSum);
    		}
    	}
    	else if ((clusterId == ZCL_CLUSTER_GEN_SCENES)
    			&& (pReadRspCmd->attrList[i].attrID == ZCL_ATTRID_SCENE_CURRENT_SCENE))
    	{
    		printf("zclReadRspCmd scene test: %d, %d, %d, %d, %d\n",pReadRspCmd->attrList[i].dataType, pReadRspCmd->attrList[i].data[0],
    					pReadRspCmd->attrList[i].data[1], pReadRspCmd->attrList[i].data[2], pReadRspCmd->attrList[i].data[3]);
    		ldsLightSceneTableCheck(pReadRspCmd->attrList[i].data[0]);
    	}
    }
#endif
}
#endif

#ifdef ZCL_WRITE
/*********************************************************************
 * @fn      sampleLight_zclWriteReqCmd
 *
 * @brief   Handler for ZCL Write Request command.
 *
 * @param
 *
 * @return  None
 */
static void sampleLight_zclWriteReqCmd(u16 clusterId, zclWriteCmd_t *pWriteReqCmd)
{
	u8 numAttr = pWriteReqCmd->numAttr;
	zclWriteRec_t *attr = pWriteReqCmd->attrList;

	if(clusterId == ZCL_CLUSTER_GEN_ON_OFF){
		for(u8 i = 0; i < numAttr; i++){
			if(attr[i].attrID == ZCL_ATTRID_START_UP_ONOFF){
				zcl_onOffAttr_save();
			}
		}
	}else if(clusterId == ZCL_CLUSTER_GEN_LEVEL_CONTROL){
		for(u8 i = 0; i < numAttr; i++){
			if(attr[i].attrID == ZCL_ATTRID_LEVEL_START_UP_CURRENT_LEVEL){
				zcl_levelAttr_save();
			}
		}
	}else if(clusterId == ZCL_CLUSTER_LIGHTING_COLOR_CONTROL){
		for(u8 i = 0; i < numAttr; i++){
			if(attr[i].attrID == ZCL_ATTRID_START_UP_COLOR_TEMPERATURE_MIREDS){
				zcl_colorCtrlAttr_save();
			}
		}
	}else if(clusterId == ZCL_CLUSTER_GEN_IDENTIFY){
		for(u8 i = 0; i < numAttr; i++){
			if(attr[i].attrID == ZCL_ATTRID_IDENTIFY_TIME){
				sampleLight_zclIdentifyCmdHandler(SAMPLE_LIGHT_ENDPOINT, 0xFFFE, g_zcl_identifyAttrs.identifyTime);
			}
		}
	}
}

/*********************************************************************
 * @fn      sampleLight_zclWriteRspCmd
 *
 * @brief   Handler for ZCL Write Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclWriteRspCmd(zclWriteRspCmd_t *pWriteRspCmd)
{
//    printf("sampleLight_zclWriteRspCmd\n");

}
#endif


/*********************************************************************
 * @fn      sampleLight_zclDfltRspCmd
 *
 * @brief   Handler for ZCL Default Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclDfltRspCmd(zclDefaultRspCmd_t *pDftRspCmd)
{
//  printf("sampleLight_zclDfltRspCmd\n");
#ifdef ZCL_OTA
	if( (pDftRspCmd->commandID == ZCL_CMD_OTA_UPGRADE_END_REQ) &&
		(pDftRspCmd->statusCode == ZCL_STA_ABORT) ){
		if(zcl_attr_imageUpgradeStatus == IMAGE_UPGRADE_STATUS_DOWNLOAD_COMPLETE){
			ota_upgradeAbort();
		}
	}
#endif
}

#ifdef ZCL_REPORT
/*********************************************************************
 * @fn      sampleLight_zclCfgReportCmd
 *
 * @brief   Handler for ZCL Configure Report command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclCfgReportCmd(zclCfgReportCmd_t *pCfgReportCmd)
{

}

/*********************************************************************
 * @fn      sampleLight_zclCfgReportRspCmd
 *
 * @brief   Handler for ZCL Configure Report Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclCfgReportRspCmd(zclCfgReportRspCmd_t *pCfgReportRspCmd)
{

}

/*********************************************************************
 * @fn      sampleLight_zclReportCmd
 *
 * @brief   Handler for ZCL Report command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclReportCmd(zclReportCmd_t *pReportCmd)
{

}
#endif

#ifdef ZCL_BASIC
/*********************************************************************
 * @fn      sampleLight_basicCb
 *
 * @brief   Handler for ZCL Basic Reset command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t sampleLight_basicCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	if(cmdId == ZCL_CMD_BASIC_RESET_FAC_DEFAULT){
		//Reset all the attributes of all its clusters to factory defaults
		//zcl_nv_attr_reset();
	}

	//return ZCL_STA_SUCCESS;
	return ZCL_STA_UNSUP_CLUSTER_COMMAND;
}
#endif

#ifdef ZCL_IDENTIFY
static uint8_t g_identify_count = 0;
static bool g_identify_start_flag = false;
static bool g_factory_reset_flag = false;

void ldsFactoryResetFlagSet(bool flag)
{
	g_factory_reset_flag = flag;
}

bool ldsFactoryResetFlagGet(void)
{
	return g_factory_reset_flag;
}

void ldsTouchlinkPassFlagSet(bool flag)
{
	g_touchlink_flag = flag;
}

bool ldsTouchlinkPassFlagGet(void)
{
	return g_touchlink_flag;
}

void ldsTouchlinkStartFlagSet(bool flag)
{
	g_identify_start_flag = flag;
}

bool ldsTouchlinkStartFlagGet(void)
{
	return g_identify_start_flag;
}

s32 ldsZclIdentifyLightEffectTimerCb(void *arg)
{
	g_identify_count++;
	if (g_identify_count >= 8)
	{
		if (g_touchlink_flag)
		{
			if (ldsFactoryResetFlagGet())
			{
				g_factory_reset_flag = false;
				ldsLightEffectJionNetworkStart();
			}
			else
			{
				ldsLightEffectFactoryResetStart();
			}

			g_identify_count = 0;
			g_touchlink_flag = false;

			identifyDelayTimerEvt = NULL;
			return -1;
		}
	}

	if (g_identify_count >= 37)
	{
		g_identify_count = 0;

		identifyDelayTimerEvt = NULL;
		return -1;
	}

//	printf("ldsZclIdentifyLightEffectTimerCb count: %d\n", g_identify_count);

	return 0;
}

void ldsZclIdentifyLightEffectDelayHandler(void)
{
	g_identify_start_flag = true;
	ldsLightEffectTouchlinkInitiatedStart();

	if (!identifyDelayTimerEvt){
		identifyDelayTimerEvt = TL_ZB_TIMER_SCHEDULE(ldsZclIdentifyLightEffectTimerCb, NULL, 800);
	}
}

s32 sampleLight_zclIdentifyTimerCb(void *arg)
{
	if(g_zcl_identifyAttrs.identifyTime <= 0){
		identifyTimerEvt = NULL;
		return -1;
	}
	g_zcl_identifyAttrs.identifyTime--;
	return 0;
}

void sampleLight_zclIdentifyTimerStop(void)
{
	if(identifyTimerEvt){
		TL_ZB_TIMER_CANCEL(&identifyTimerEvt);
	}
}

/*********************************************************************
 * @fn      sampleLight_zclIdentifyCmdHandler
 *
 * @brief   Handler for ZCL Identify command. This function will set blink LED.
 *
 * @param   endpoint
 * @param   srcAddr
 * @param   identifyTime - identify time
 *
 * @return  None
 */
void sampleLight_zclIdentifyCmdHandler(u8 endpoint, u16 srcAddr, u16 identifyTime)
{
	g_zcl_identifyAttrs.identifyTime = identifyTime;

	if(identifyTime == 0){
		sampleLight_zclIdentifyTimerStop();
		ldsLightEffectTouchlinkInitiatedStop();
	}else{
		if(!identifyTimerEvt){
			identifyTimerEvt = TL_ZB_TIMER_SCHEDULE(sampleLight_zclIdentifyTimerCb, NULL, 1000);
		}
	}
}

void sampleLight_zclCommissioningIdentifyCmdHandler(u8 endpoint, u16 srcAddr, u16 identifyTime)
{
	g_zcl_identifyAttrs.identifyTime = identifyTime;

	if(identifyTime == 0){
		sampleLight_zclIdentifyTimerStop();
	}else{
		if(!identifyTimerEvt){
			identifyTimerEvt = TL_ZB_TIMER_SCHEDULE(sampleLight_zclIdentifyTimerCb, NULL, 1000);
		}
	}
}
/*********************************************************************
 * @fn      sampleLight_zcltriggerCmdHandler
 *
 * @brief   Handler for ZCL trigger command.
 *
 * @param   pTriggerEffect
 *
 * @return  None
 */
static void sampleLight_zcltriggerCmdHandler(zcl_triggerEffect_t *pTriggerEffect)
{
	u8 effectId = pTriggerEffect->effectId;
//	u8 effectVariant = pTriggerEffect->effectVariant;

	switch(effectId){
		case IDENTIFY_EFFECT_BLINK:
//			ldsLightEffectJionNetworkStart();
//			ldsLightEffectIdentifyOneBlink();
			break;
		case IDENTIFY_EFFECT_BREATHE:
//			light_blink_start(15, 300, 700);
			break;
		case IDENTIFY_EFFECT_OKAY:
//			light_blink_start(2, 250, 250);
			break;
		case IDENTIFY_EFFECT_CHANNEL_CHANGE:
//			light_blink_start(1, 500, 7500);
			break;
		case IDENTIFY_EFFECT_FINISH_EFFECT:
//			light_blink_start(1, 300, 700);
			break;
		case IDENTIFY_EFFECT_STOP_EFFECT:
			ldsLightEffectTouchlinkInitiatedStop();
			break;
		default:
			break;
	}
}

/*********************************************************************
 * @fn      sampleLight_identifyCb
 *
 * @brief   Handler for ZCL Identify command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t sampleLight_identifyCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	//printf("sampleLight_identifyCb test3333: %x, %d, %d\n", cmdId, ((zcl_identifyCmd_t *)cmdPayload)->identifyTime, pAddrInfo->dstEp);

	if (!ldsDeviceAgingFunctionTestDone())
	{
		ldsAgingTestExit();
//		ldsLightFactoryReset();
		sleep_ms(2000);

		SYSTEM_RESET();
		return ZCL_STA_FAILURE;
	}

	if(pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			switch(cmdId){
				case ZCL_CMD_IDENTIFY:
					ldsLightEffectTouchlinkIdentify(((zcl_identifyCmd_t *)cmdPayload)->identifyTime);
					sampleLight_zclIdentifyCmdHandler(pAddrInfo->dstEp, pAddrInfo->srcAddr, ((zcl_identifyCmd_t *)cmdPayload)->identifyTime);
					break;
				case ZCL_CMD_ZLL_COMMISSIONING_IDENTIFY:
					ldsZclIdentifyLightEffectDelayHandler();
					sampleLight_zclCommissioningIdentifyCmdHandler(pAddrInfo->dstEp, pAddrInfo->srcAddr, ((zcl_identifyCmd_t *)cmdPayload)->identifyTime);
					break;
				case ZCL_CMD_TRIGGER_EFFECT:
					sampleLight_zcltriggerCmdHandler((zcl_triggerEffect_t *)cmdPayload);
					break;
				default:
					break;
			}
		}
	}

	return ZCL_STA_SUCCESS;
}
#endif

#if DUAL_MODE_WITH_MATTER
static s32 sampleLight_lightNumCheckTimerCb(void *arg)
{
	printf("checkTimer:\n");

	u8 scene_idx = 0;

	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet();
	zcl_levelAttr_t *pLevel = zcl_levelAttrGet();

	ldsTouchlinkPassFlagSet(true);

	// add scene handle
	if (ldsLightSceneHandleCheck())
	{
		g_factory_reset_flag = true;
		if(lightNumCheck.levelNum){
			printf("lvl = %d, num = %d\n", lightNumCheck.levelSum, lightNumCheck.levelNum);

			u8 level = lightNumCheck.levelSum / lightNumCheck.levelNum;

			pLevel->curLevel = level;
		}

		bool onOff = pOnOff->onOff;
		if(lightNumCheck.onLightNum != lightNumCheck.offLightNum){
			printf("onNum = %d, offNum = %d\n",
					lightNumCheck.onLightNum, lightNumCheck.offLightNum);

			onOff = lightNumCheck.onLightNum > lightNumCheck.offLightNum ? 1 : 0;
		}

		if (lightNumCheck.sceneTable.total_num) {
			scene_idx = ldsLightCurrentSceneIndexGet();
		}

		lds_onoff_util_write(1, onOff);
		lds_lvl_util_write(1, pLevel->curLevel);
		ldsSyncSceneIdInformation(scene_idx);
		printf("sampleLight_lightNumCheckTimerCb test8888: %d, %d, %d, %d, %d\n", lightNumCheck.levelNum, lightNumCheck.sceneTable.total_num, onOff, pLevel->curLevel, scene_idx);
	}

	lightNumCheck.checkTimerEvt = NULL;
	return -1;
}

static void sampleLight_zclAddGroupCmdHandler(u8 endpoint, u16 srcAddr, u16 groupId)
{
	printf("rcv addGroup: ep = %x, src = %x, groupId = %x\n", endpoint, srcAddr, groupId);

#if 0
	extern void ikea_sceneUpdate(u8 endpoint, u16 groupId);
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

//#ifdef ZCL_LEVEL_CTRL
		pReadCmd->attrID[0] = ZCL_ATTRID_LEVEL_CURRENT_LEVEL;
		zcl_sendReadCmd(SAMPLE_LIGHT_ENDPOINT, &dstEpInfo, ZCL_CLUSTER_GEN_LEVEL_CONTROL, TRUE, ZCL_FRAME_CLIENT_SERVER_DIR, pReadCmd);
//#endif

		pReadCmd->attrID[0] = ZCL_ATTRID_SCENE_CURRENT_SCENE;
		zcl_sendReadCmd(SAMPLE_LIGHT_ENDPOINT, &dstEpInfo, ZCL_CLUSTER_GEN_SCENES, TRUE, ZCL_FRAME_CLIENT_SERVER_DIR, pReadCmd);

		// read scene
		ev_buf_free((u8 *)pReadCmd);
	}

	ldsLightStateSynNumClean();

	if(lightNumCheck.checkTimerEvt){
		TL_ZB_TIMER_CANCEL(&lightNumCheck.checkTimerEvt);
	}
	lightNumCheck.checkTimerEvt = TL_ZB_TIMER_SCHEDULE(sampleLight_lightNumCheckTimerCb, NULL, 1000);
}
#endif

status_t sampleLight_groupCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	if(pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			switch(cmdId){
				case ZCL_CMD_GROUP_ADD_GROUP:
					sampleLight_zclAddGroupCmdHandler(pAddrInfo->dstEp, pAddrInfo->srcAddr, ((aps_add_group_req_t *)cmdPayload)->group_addr);
					break;
				default:
					break;
			}
		}
	}

	return ZCL_STA_SUCCESS;
}

#endif  /* __PROJECT_TL_LIGHT__ */


