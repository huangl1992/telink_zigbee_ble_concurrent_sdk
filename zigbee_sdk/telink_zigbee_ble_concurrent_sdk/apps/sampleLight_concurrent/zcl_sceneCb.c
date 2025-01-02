/********************************************************************************************************
 * @file    zcl_sceneCb.c
 *
 * @brief   This is the source file for zcl_sceneCb
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
#include "sampleLight.h"

#include "lds_device_config.h"
#include "lds_light_cct_algorithm.h"
#include "lds_color_utility.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */
#define IKEA_ZCL_CMD_STEP_SCENE		0x07
#define IKEA_ZCL_CMD_MOVE_SCENE		0x08
#define IKEA_ZCL_CMD_STOP_SCENE		0x09

#define IKEA_SCENE_MODE_UP			0x00
#define IKEA_SCENE_MODE_DOWN		0x01
#define IKEA_SCENE_MODE_DEFAULT		0x02

#define IKEA_CCT_SCENE_IDX_MAX		4

typedef enum{
	SCENE_ZERO = 0,
	SCENE_ONE,
	SCENE_TWO,
	SCENE_THREE,
	SCENE_FOUR,
	SCENE_FIVE,
	SCENE_SIX,
	SCENE_SEVEN,
	SCENE_EIGHT,
	SCENE_NINE,
}LDS_SCENE_E;

/**********************************************************************
 * TYPEDEFS
 */
typedef struct _attribute_packed_{
	u8 mode;
	u8 stepSize;
	u16 transTime;
}ikea_stepScene_t;

typedef struct _attribute_packed_{
	u8 mode;
	u16 transTime;
}ikea_moveScene_t;

typedef struct _attribute_packed_{
	u16 holdTime;
}ikea_stopScene_t;

typedef struct{
	ev_timer_event_t *timerEvt;
	u16 transTime;
	s8 sceneIdx;
	s8 step;
}ikea_sceneInfo_t;

static ikea_sceneInfo_t ikeaSceneInfo;
uint8_t g_scene_transtime = 0;
#define COLOR_TEST							0
#define CWS_TEN_PRS_TEST					0
//s32 move_status = 0;
/**********************************************************************
 * LOCAL VARIABLES
 */

#if COLOR_TEST
const u16 ikea_colors_CIE_1931[][2] = {
	{30015, 26870},		// 0.4580, 0.4100 : 2700K
	{25022, 24884},		// 0.3818, 0.3797 : 4000K
	{20466, 21515},		// 0.3123, 0.3283 : 6500K
	{32886, 27217},		// 0.5018, 0.4153 : 2200K
	{35978, 26365},		// color start
	{37550, 25116},
	{24740, 25067},
	{28509, 23886},
	{24896, 19251},
	{20761, 15872},
	{27004, 26512},
	{35571, 23604},
	{25759, 17997},
	{20864, 13675},
	{31662, 28313},
	{40699, 22308},
	{29587, 15924},
	{20970, 11404},
	{33989, 27943},
	{41947, 21624},
	{32719, 16541},
	{26110, 12900},
	{27105, 32492},
	{18411, 19740},
	{16034, 16217},
	{15604, 13478},
	{25280, 32674},
	{16253, 17607},
	{13227, 10720},
	{15116, 11507},
	{23865, 35622},
	{12940, 13164},
	{11334, 6916},
	{13514, 7818},
	{21989, 37472},
	{11563, 10168},
	{9831, 3932},
	{13159, 5766},
};
#else
#if CWS_TEN_PRS_TEST
const u16 ikea_colors_CIE_1931[][2] = {
	 {20467, 21515},   // 0.5018, 0.4153 : 2200K
	 {25022, 24884}, // 0.4580, 0.4100 : 2700K
	 {30015, 26870},   // 0.3818, 0.3797 : 4000K
	 {32886, 27217},   // 0.3123, 0.3283 : 6500K
	#if (LDS_DEFAULT_SCENES_NUMER_OF > 4) // save flash for CCT
	 {41943, 21627},   // 0.6400, 0.3300 : Red
	 {19661, 39322},   // 0.3000, 0.6000 : Green
	 {9830,  3932},    // 0.1500, 0.0600 : Blue
	 {14726, 21548},   // 0.2247, 0.3288 : Cyan
	 {21031, 10106},   // 0.3209, 0.1542 : Magenta
	 {27479, 33109},   // 0.4193, 0.5052 : Yellow
	#endif
};
#else
const u16 ikea_colors_CIE_1931[][2] = {
	{30015, 26870},		// 0.4580, 0.4100 : 2700K
	{25022, 24884},		// 0.3818, 0.3797 : 4000K
	{20466, 21515},		// 0.3123, 0.3283 : 6500K
	{32886, 27217},		// 0.5018, 0.4153 : 2200K
#if (LDS_DEFAULT_SCENES_NUMER_OF > 4)
	{35848, 26214},		// 0.5470. 0.4000 : 1780K
	{38011, 24904},		// 0.5800, 0.3800 : Warm Ambar
	{40632, 22282},		// 0.6200, 0.3400 : Dark Peach
	{32768, 15729},		// 0.5000, 0.2400 : Saturated Pink
	{22282, 12452},		// 0.3400, 0.1900 : Light Purple
	{13107, 6554},		// 0.2000, 0.1000 : Light Blue
#endif
};
#endif
#endif

const u16 g_ikea_color_table[][1] = {
	{370},		// 2700K
	{250},		// 4000K
	{153},		// 6500K
	{454},		// 2200K
};

#if (LDS_DEFAULT_SCENES_NUMER_OF > 4)
#if COLOR_TEST
#define IKEA_SCENE_IDX_MAX		37
#else
#define IKEA_SCENE_IDX_MAX		9
#endif
#else
#define IKEA_SCENE_IDX_MAX		3
#endif
extern void sampleLight_moveToColorProcess(zcl_colorCtrlMoveToColorCmd_t *cmd);
extern void sampleLight_moveToColorTemperatureProcess(zcl_colorCtrlMoveToColorTemperatureCmd_t *cmd);

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

	for (u8 i = 0; i < IKEA_SCENE_IDX_MAX; i++){
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

uint16_t ldsLightTranstionTimeGet(uint16_t trans_time)
{
	uint16_t transtion_time = 0;
	uint16_t dimmer_pwm = 0;

	dimmer_pwm = ldsDimmerPwmValueGet();
	transtion_time = (float)(trans_time * dimmer_pwm) / 10000.0;
	if (dimmer_pwm <= 1000)	{
		transtion_time = 50;
	}

	return transtion_time;
}

void ldsLightStatusGetSceneId(void)
{
	u8 i = 0;
	uint8_t status = 0;
	zcl_lightColorCtrlAttr_t *light_attr = zcl_colorAttrGet();

	if (light_attr->colorMode == ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS)
	{
		for (i = 0; i < IKEA_CCT_SCENE_IDX_MAX; i++)
		{
			if (light_attr->colorTemperatureMireds == g_ikea_color_table[i][0])
			{
				ikeaSceneInfo.sceneIdx = i;
				break;
			}
		}
	}
#if (defined EXTENDEDCOLOR_LIGHT)
	else if (light_attr->colorMode == ZCL_COLOR_MODE_CURRENT_X_Y)
	{
		for (i = IKEA_CCT_SCENE_IDX_MAX; i <= IKEA_SCENE_IDX_MAX; i++)
		{
			if ((light_attr->currentX == ikea_colors_CIE_1931[i][0])
				&& (light_attr->currentY == ikea_colors_CIE_1931[i][1]))
			{
				ikeaSceneInfo.sceneIdx = i;
				break;
			}
		}
	}
#endif

	status = zcl_setAttrVal(1, ZCL_CLUSTER_GEN_SCENES, ZCL_ATTRID_SCENE_CURRENT_SCENE, (u8 *)&ikeaSceneInfo.sceneIdx);

	printf("ldsLightStatusGetSceneId: %d, %d\n", ikeaSceneInfo.sceneIdx, status);
	if (status)
	{
		printf("ldsLightStatusGetSceneId write scene attribute fail\r\n");
	}
}

#if (defined EXTENDEDCOLOR_LIGHT)
void ldsMove2Color(u8 scene_index, u16 trans_time)
{
	zcl_colorCtrlMoveToColorCmd_t move2Color;

	move2Color.colorX = ikea_colors_CIE_1931[scene_index][0];
	move2Color.colorY = ikea_colors_CIE_1931[scene_index][1];
	move2Color.transitionTime = trans_time;
	move2Color.optPresent = 0;

	sampleLight_moveToColorProcess(&move2Color);
}
#endif

void ldsMoveTemperature(u8 scene_index, u16 trans_time)
{
	zcl_colorCtrlMoveToColorTemperatureCmd_t move2Temperature;

	move2Temperature.colorTemperature = g_ikea_color_table[scene_index][0];
	move2Temperature.transitionTime = trans_time;
	move2Temperature.optPresent = 0;

	sampleLight_moveToColorTemperatureProcess(&move2Temperature);
}

void ldsSyncSceneIdInformation(u8 scene_idx)
{
	u8 color_mode = 0;
	u8 endpoint = 1;
	u16 colorTemperature = 0;

	ikeaSceneInfo.sceneIdx = scene_idx;

	switch (scene_idx)
	{
		case SCENE_ZERO:
		case SCENE_ONE:
		case SCENE_TWO:
		case SCENE_THREE:
		{
			color_mode = 2;
			colorTemperature = g_ikea_color_table[scene_idx][0];
			printf("ldsSyncSceneIdInformation: %d, %d\n", scene_idx, colorTemperature);
			lds_color_util_update_mode_conditionally(endpoint, color_mode);
			lds_color_util_write_temp(endpoint, colorTemperature);
		}
			break;
#if (defined EXTENDEDCOLOR_LIGHT)
		case SCENE_FOUR:
		case SCENE_FIVE:
		case SCENE_SIX:
		case SCENE_SEVEN:
		case SCENE_EIGHT:
		case SCENE_NINE:
		{
			u16 colorX = 0;
			u16 colorY = 0;

			color_mode = 1;
			colorX = ikea_colors_CIE_1931[scene_idx][0];
			colorY = ikea_colors_CIE_1931[scene_idx][1];

			lds_color_util_write_xy(endpoint, colorX, colorY);
			lds_color_util_update_mode_conditionally(endpoint, color_mode);
			printf("ldsSyncSceneIdInformation extended color light: %d, %d, %d\n", scene_idx, colorX, colorY);
		}
			break;
#endif
		default:
			break;
	}
}

#if COLOR_TEST
void ldsMoveTemperatureOrMoveColor(u8 scene_index, u16 trans_time)
{
//	uint8_t status = 0;
//	uint8_t scene_id = 0;

	if ((scene_index >= SCENE_ZERO)
	  && (scene_index <= SCENE_THREE))
	{
		ldsMoveTemperature(scene_index, trans_time);
	}
#if (defined EXTENDEDCOLOR_LIGHT)
	else if ((scene_index >= SCENE_FOUR)
			&& (scene_index < 38))
	{
		ldsMove2Color(scene_index, trans_time);
	}
#endif
}
#else
#include "lds_log.h"
#include "lds_dim_algorithm.h"
void ldsMoveTemperatureOrMoveColor(u8 scene_index, u16 trans_time)
{
	uint8_t status = 0;
	uint8_t scene_id = 0;
	u16 attrLen = 0;
	float percent[5] = {0.0};

//	zcl_levelAttr_t *pLevel = zcl_levelAttrGet();

//	LDS_LOG_I("ldsMoveTemperatureOrMoveColor test: %d, %f", pLevel->curLevel, ldsGetDimalgorithmExpteble(pLevel->curLevel));
#if CWS_TEN_PRS_TEST
	switch (scene_index)
	{
		case SCENE_ZERO:
		case SCENE_ONE:
		case SCENE_TWO:
		case SCENE_THREE:
			ldsMoveTemperature(scene_index, trans_time);
			break;
#if (defined EXTENDEDCOLOR_LIGHT)
		case SCENE_FOUR:
		case SCENE_FIVE:
		case SCENE_SIX:
		case SCENE_SEVEN:
		case SCENE_EIGHT:
		case SCENE_NINE:
			ldsMove2Color(scene_index, trans_time);
			break;
#endif
		default:
			break;
	}

#else
	switch (scene_index)
	{
		case SCENE_ZERO:
		case SCENE_ONE:
		case SCENE_TWO:
		case SCENE_THREE:
			ldsMoveTemperature(scene_index, trans_time);
			break;
#if (defined EXTENDEDCOLOR_LIGHT)
		case SCENE_FOUR:
		case SCENE_FIVE:
		case SCENE_SIX:
		case SCENE_SEVEN:
		case SCENE_EIGHT:
		case SCENE_NINE:
			ldsMove2Color(scene_index, trans_time);
			break;
#endif
		default:
			break;
	}

	if (zcl_getAttrVal(1, ZCL_CLUSTER_GEN_SCENES, ZCL_ATTRID_SCENE_CURRENT_SCENE, &attrLen, (u8 *)&scene_id) == ZCL_STA_SUCCESS)
	{

	}

	status = zcl_setAttrVal(1, ZCL_CLUSTER_GEN_SCENES, ZCL_ATTRID_SCENE_CURRENT_SCENE, (u8 *)&ikeaSceneInfo.sceneIdx);
	if (!status)
	{
		printf("ldsMoveTemperatureOrMoveColor fail\n");
	}
}
#endif
#endif

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
//	ikeaSceneInfo.transTime = pStepScene->transTime;
	ikeaSceneInfo.transTime = 0;
	g_scene_transtime = pStepScene->transTime;

	if(ikeaSceneInfo.sceneIdx > IKEA_SCENE_IDX_MAX){
		ikeaSceneInfo.sceneIdx = 0;
	}else if(ikeaSceneInfo.sceneIdx < 0){
		ikeaSceneInfo.sceneIdx = IKEA_SCENE_IDX_MAX;
	}

	printf("stepScene: curIdx = %d, dstIdx = %d, transTime = %d, %d\n", curSceneIdx, ikeaSceneInfo.sceneIdx, ikeaSceneInfo.transTime, g_scene_transtime);
	ldsMoveTemperatureOrMoveColor((u8)ikeaSceneInfo.sceneIdx, ikeaSceneInfo.transTime);
}

static s32 ikea_sceneTimerCb(void *arg)
{
	static uint8_t move_scene_count = 0;

	u8 curSceneIdx = ikeaSceneInfo.sceneIdx;
	ikeaSceneInfo.sceneIdx = curSceneIdx + ikeaSceneInfo.step;
	if(ikeaSceneInfo.sceneIdx > IKEA_SCENE_IDX_MAX){
		ikeaSceneInfo.sceneIdx = 0;
	}else if(ikeaSceneInfo.sceneIdx < 0){
		ikeaSceneInfo.sceneIdx = IKEA_SCENE_IDX_MAX;
	}

	printf("moveScene: curIdx = %d, dstIdx = %d\n", curSceneIdx, ikeaSceneInfo.sceneIdx);
	ldsMoveTemperatureOrMoveColor((u8)ikeaSceneInfo.sceneIdx, ikeaSceneInfo.transTime);

	move_scene_count++;
#if (defined EXTENDEDCOLOR_LIGHT)
	if (move_scene_count >= 30)			// scene loop 3 times
#else
	if (move_scene_count >= 12)
#endif
	{
		move_scene_count = 0;
		return -1;
	}

	return 0;
}

//static void ikea_sceneTimerStop(void)
void ikea_sceneTimerStop(void)
{
	if (ikeaSceneInfo.timerEvt){
		printf("ikea_sceneTimerStop test\n");
		TL_ZB_TIMER_CANCEL(&ikeaSceneInfo.timerEvt);
	}
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

	printf("moveScene: curIdx = %d, dstIdx = %d, trans = %d, %d\n", curSceneIdx, ikeaSceneInfo.sceneIdx, ikeaSceneInfo.transTime, g_scene_transtime);

	ldsMoveTemperatureOrMoveColor((u8)ikeaSceneInfo.sceneIdx, ikeaSceneInfo.transTime);
	ikea_sceneTimerStop();
	ikeaSceneInfo.timerEvt = TL_ZB_TIMER_SCHEDULE(ikea_sceneTimerCb, NULL, ikeaSceneInfo.transTime * 100);
}

static void ikea_stopSceneReqHandler(ikea_stopScene_t *pStopScene)
{
	ikea_sceneTimerStop();

	ikeaSceneInfo.transTime = 0;
	ikeaSceneInfo.step = 0;

	printf("stopScene\n");
}
/*********************************************************************
 * @fn      sampleLight_sceneRecallReqHandler
 *
 * @brief   Handler for ZCL scene recall command. This function will recall scene.
 *
 * @param	pApsdeInd
 * @param	pScene
 *
 * @return  None
 */
static void sampleLight_sceneRecallReqHandler(zclIncomingAddrInfo_t *pAddrInfo, zcl_sceneEntry_t *pScene)
{
	u8 extLen = 0;

#ifdef ZCL_ON_OFF
	extLen += 3;//id + length
	u8 onOff = pScene->extField[extLen];
	extLen += sizeof(u8);//onOff
#endif

#ifdef ZCL_LEVEL_CTRL
	extLen += 3;//id + length
	u8 level = pScene->extField[extLen];
	extLen += sizeof(u8);//level
#endif

#ifdef ZCL_LIGHT_COLOR_CONTROL
	extLen += 3;//id + length
	u16 currentX = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u16 currentY = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u16 enhHue = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u8 saturation = pScene->extField[extLen];
	extLen += sizeof(u8);
	u8 colorLoopActive = pScene->extField[extLen];
	extLen += sizeof(u8);
	u8 colorLoopDir = pScene->extField[extLen];
	extLen += sizeof(u8);
	u16 colorLoopTime = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u16 colorTemperature = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);

	u8 mode = ZCL_COLOR_MODE_CURRENT_X_Y;
	if((currentX == 0) && (currentY == 0)){
		if(enhHue || saturation){
			mode = ZCL_COLOR_MODE_CURRENT_HUE_SATURATION;
		}else if(colorTemperature){
			mode = ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS;
		}
	}
#endif

#ifdef ZCL_ON_OFF
	sampleLight_onOffCb(pAddrInfo, onOff, NULL);
#endif
#ifdef ZCL_LEVEL_CTRL
	moveToLvl_t moveToLevel;
	moveToLevel.level = level;
	moveToLevel.transitionTime = pScene->transTime;
	moveToLevel.optPresent = 0;

	sampleLight_levelCb(pAddrInfo, ZCL_CMD_LEVEL_MOVE_TO_LEVEL, &moveToLevel);
#endif
#ifdef ZCL_LIGHT_COLOR_CONTROL
	if(mode == ZCL_COLOR_MODE_CURRENT_HUE_SATURATION){
		zcl_colorCtrlMoveToHueAndSaturationCmd_t move2HueAndSat;
		move2HueAndSat.hue = (u8)(enhHue % 256);
		move2HueAndSat.saturation = saturation;
		move2HueAndSat.transitionTime = pScene->transTime;
		move2HueAndSat.optPresent = 0;
		sampleLight_colorCtrlCb(pAddrInfo, ZCL_CMD_LIGHT_COLOR_CONTROL_MOVE_TO_HUE_AND_SATURATION, &move2HueAndSat);
	}else if(mode == ZCL_COLOR_MODE_CURRENT_X_Y){
		zcl_colorCtrlMoveToColorCmd_t move2Color;
		move2Color.colorX = currentX;
		move2Color.colorY = currentY;
		move2Color.transitionTime = pScene->transTime;
		move2Color.optPresent = 0;
		sampleLight_colorCtrlCb(pAddrInfo, ZCL_CMD_LIGHT_COLOR_CONTROL_MOVE_TO_COLOR, &move2Color);
	}else if(mode == ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS){
		zcl_colorCtrlMoveToColorTemperatureCmd_t move2CT;
		move2CT.colorTemperature = colorTemperature;
		move2CT.transitionTime = pScene->transTime;
		move2CT.optPresent = 0;
		sampleLight_colorCtrlCb(pAddrInfo, ZCL_CMD_LIGHT_COLOR_CONTROL_MOVE_TO_COLOR_TEMPERATURE, &move2CT);
	}
#endif
}

/*********************************************************************
 * @fn      sampleLight_sceneStoreReqHandler
 *
 * @brief   Handler for ZCL scene store command. This function will set scene attribute first.
 *
 * @param   pApsdeInd
 * @param   pScene
 *
 * @return  None
 */
static void sampleLight_sceneStoreReqHandler(zcl_sceneEntry_t *pScene)
{
	/* receive Store Scene Request command, get the latest Scene info to save */
	u8 extLen = 0;

#ifdef ZCL_ON_OFF
	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet();

	pScene->extField[extLen++] = LO_UINT16(ZCL_CLUSTER_GEN_ON_OFF);
	pScene->extField[extLen++] = HI_UINT16(ZCL_CLUSTER_GEN_ON_OFF);
	pScene->extField[extLen++] = 1;
	pScene->extField[extLen++] = pOnOff->onOff;
#endif

#ifdef ZCL_LEVEL_CTRL
	zcl_levelAttr_t *pLevel = zcl_levelAttrGet();

	pScene->extField[extLen++] = LO_UINT16(ZCL_CLUSTER_GEN_LEVEL_CONTROL);
	pScene->extField[extLen++] = HI_UINT16(ZCL_CLUSTER_GEN_LEVEL_CONTROL);
	pScene->extField[extLen++] = 1;
	pScene->extField[extLen++] = pLevel->curLevel;
#endif

#ifdef ZCL_LIGHT_COLOR_CONTROL
	zcl_lightColorCtrlAttr_t *pColor = zcl_colorAttrGet();

	pScene->extField[extLen++] = LO_UINT16(ZCL_CLUSTER_LIGHTING_COLOR_CONTROL);
	pScene->extField[extLen++] = HI_UINT16(ZCL_CLUSTER_LIGHTING_COLOR_CONTROL);
	pScene->extField[extLen++] = 13;

	//currentX and currentY
	if(pColor->enhancedColorMode == ZCL_COLOR_MODE_CURRENT_X_Y){
		pScene->extField[extLen++] = LO_UINT16(pColor->currentX);
		pScene->extField[extLen++] = HI_UINT16(pColor->currentX);
		pScene->extField[extLen++] = LO_UINT16(pColor->currentY);
		pScene->extField[extLen++] = HI_UINT16(pColor->currentY);
	}else{
		pScene->extField[extLen++] = 0;
		pScene->extField[extLen++] = 0;
		pScene->extField[extLen++] = 0;
		pScene->extField[extLen++] = 0;
	}
	//enhancedCurrentHue and currentSaturation
	if(pColor->enhancedColorMode == ZCL_COLOR_MODE_CURRENT_HUE_SATURATION){
		pScene->extField[extLen++] = LO_UINT16(pColor->currentHue);
		pScene->extField[extLen++] = HI_UINT16(pColor->currentHue);
		pScene->extField[extLen++] = pColor->currentSaturation;
	}else{
		pScene->extField[extLen++] = 0;
		pScene->extField[extLen++] = 0;
		pScene->extField[extLen++] = 0;
	}
	//colorLoopActive
	pScene->extField[extLen++] = 0;
	//colorLoopDirection
	pScene->extField[extLen++] = 0;
	//colorLoopTime
	pScene->extField[extLen++] = 0;
	pScene->extField[extLen++] = 0;
	//colorTemperatureMireds
	if(pColor->enhancedColorMode == ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS){
		pScene->extField[extLen++] = LO_UINT16(pColor->colorTemperatureMireds);
		pScene->extField[extLen++] = HI_UINT16(pColor->colorTemperatureMireds);
	}else{
		pScene->extField[extLen++] = 0;
		pScene->extField[extLen++] = 0;
	}
#endif

	pScene->extFieldLen = extLen;
}

/*********************************************************************
 * @fn      sampleLight_sceneCb
 *
 * @brief   Handler for ZCL Scene command.
 *
 * @param   pApsdeInd
 *
 * @return  None
 */
status_t sampleLight_sceneCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	status_t status = ZCL_STA_SUCCESS;
	zcl_onOffAttr_t *p_status = zcl_onoffAttrGet();

	if (!p_status->onOff)
	{
		if ((cmdId == IKEA_ZCL_CMD_STEP_SCENE)
			|| (cmdId == IKEA_ZCL_CMD_MOVE_SCENE)
			|| (cmdId == IKEA_ZCL_CMD_STOP_SCENE))
		{
			return ZCL_STA_FAILURE;
		}
	}

	if(pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			ikea_sceneTimerStop();
			switch(cmdId){
				case ZCL_CMD_SCENE_STORE_SCENE:
					sampleLight_sceneStoreReqHandler((zcl_sceneEntry_t *)cmdPayload);
					break;
				case ZCL_CMD_SCENE_RECALL_SCENE:
					sampleLight_sceneRecallReqHandler(pAddrInfo, (zcl_sceneEntry_t *)cmdPayload);
					break;
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
					break;
			}
		}
	}

	return status;
}

#endif  /* __PROJECT_TL_LIGHT__ */
