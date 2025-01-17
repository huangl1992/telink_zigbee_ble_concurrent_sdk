/********************************************************************************************************
 * @file    sampleLightEpCfg.c
 *
 * @brief   This is the source file for sampleLightEpCfg
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
#include "lds_mfg_token_config.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */

#define XT_CREDENTIALS_FW_VERSION	"1.1.8"

#ifndef ZCL_BASIC_MFG_NAME
#define ZCL_BASIC_MFG_NAME     		{16, 'L', 'E', 'D', ' ', 'L', 'i', 'g', 'h', 't', '0', 'x', '0', '7', 'C', '2'}	//{6,'T','E','L','I','N','K'}
#endif
#ifndef ZCL_BASIC_MODEL_ID
#define ZCL_BASIC_MODEL_ID	   		{32,'T','L','S','R','9'}
#endif
#ifndef ZCL_BASIC_SW_BUILD_ID
#define ZCL_BASIC_SW_BUILD_ID     	{8, 'V', '1', '.', '1', '.', '8'}
#endif
#ifndef ZCL_BASIC_DATA_CODE
#define ZCL_BASIC_DATA_CODE			{9, '2', '0', '2', '4', '1', '2', '2', '3'}
#endif

#define COLOR_TEMPERATURE_PHYSICAL_MIN		0x0099 	//0x00FA//4000K
#define COLOR_TEMPERATURE_PHYSICAL_MAX		0x01C6	//2200K
#define COLOR_TEMPERATURE_PHYSICAL_DEFAULT	0x0172	//2700K


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * GLOBAL VARIABLES
 */
/**
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
const u16 sampleLight_inClusterList[] =
{
	ZCL_CLUSTER_GEN_BASIC,
	ZCL_CLUSTER_GEN_IDENTIFY,
#ifdef ZCL_GROUP
	ZCL_CLUSTER_GEN_GROUPS,
#endif
#ifdef ZCL_SCENE
	ZCL_CLUSTER_GEN_SCENES,
#endif
#ifdef ZCL_ON_OFF
	ZCL_CLUSTER_GEN_ON_OFF,
#endif
#ifdef ZCL_LEVEL_CTRL
	ZCL_CLUSTER_GEN_LEVEL_CONTROL,
#endif
#ifdef ZCL_LIGHT_COLOR_CONTROL
	ZCL_CLUSTER_LIGHTING_COLOR_CONTROL,
#endif
#ifdef ZCL_ZLL_COMMISSIONING
	ZCL_CLUSTER_TOUCHLINK_COMMISSIONING,
#endif
#ifdef ZCL_WWAH
	ZCL_CLUSTER_WWAH,
#endif
};

/**
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
const u16 sampleLight_outClusterList[] =
{
#ifdef ZCL_OTA
    ZCL_CLUSTER_OTA,
#endif
};

/**
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define SAMPLELIGHT_IN_CLUSTER_NUM		(sizeof(sampleLight_inClusterList)/sizeof(sampleLight_inClusterList[0]))
#define SAMPLELIGHT_OUT_CLUSTER_NUM		(sizeof(sampleLight_outClusterList)/sizeof(sampleLight_outClusterList[0]))

/**
 *  @brief Definition for simple description for HA profile
 */
const af_simple_descriptor_t sampleLight_simpleDesc =
{
	HA_PROFILE_ID,                      		/* Application profile identifier */
#ifdef ZCL_LIGHT_COLOR_CONTROL
	HA_DEV_COLOR_DIMMABLE_LIGHT,
#else
	#ifdef ZCL_LEVEL_CTRL
		HA_DEV_DIMMABLE_LIGHT,              	/* Application device identifier */
	#else
		HA_DEV_ONOFF_LIGHT,						/* Application device identifier */
	#endif
#endif
	SAMPLE_LIGHT_ENDPOINT,              		/* Endpoint */
	1,                                  		/* Application device version */
	0,											/* Reserved */
	SAMPLELIGHT_IN_CLUSTER_NUM,           		/* Application input cluster count */
	SAMPLELIGHT_OUT_CLUSTER_NUM,          		/* Application output cluster count */
	(u16 *)sampleLight_inClusterList,    		/* Application input cluster list */
	(u16 *)sampleLight_outClusterList,   		/* Application output cluster list */
};

#if AF_TEST_ENABLE
/**
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
const u16 sampleTest_inClusterList[] =
{
	ZCL_CLUSTER_TELINK_SDK_TEST_REQ,
	ZCL_CLUSTER_TELINK_SDK_TEST_RSP,
	ZCL_CLUSTER_TELINK_SDK_TEST_CLEAR_REQ,
	ZCL_CLUSTER_TELINK_SDK_TEST_CLEAR_RSP,
};


/**
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
const u16 sampleTest_outClusterList[] =
{
	ZCL_CLUSTER_TELINK_SDK_TEST_REQ,
	ZCL_CLUSTER_TELINK_SDK_TEST_RSP,
	ZCL_CLUSTER_TELINK_SDK_TEST_CLEAR_REQ,
	ZCL_CLUSTER_TELINK_SDK_TEST_CLEAR_RSP,
};

/**
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define SAMPLE_TEST_IN_CLUSTER_NUM		(sizeof(sampleTest_inClusterList)/sizeof(sampleTest_inClusterList[0]))
#define SAMPLE_TEST_OUT_CLUSTER_NUM		(sizeof(sampleTest_outClusterList)/sizeof(sampleTest_outClusterList[0]))

/**
 *  @brief Definition for simple description for HA profile
 */
const af_simple_descriptor_t sampleTestDesc =
{
	HA_PROFILE_ID,                      /* Application profile identifier */
	HA_DEV_DIMMABLE_LIGHT,              /* Application device identifier */
	SAMPLE_TEST_ENDPOINT,               /* Endpoint */
	0,                                  /* Application device version */
	0,									/* Reserved */
	SAMPLE_TEST_IN_CLUSTER_NUM,         /* Application input cluster count */
	SAMPLE_TEST_OUT_CLUSTER_NUM,        /* Application output cluster count */
	(u16 *)sampleTest_inClusterList,    /* Application input cluster list */
	(u16 *)sampleTest_outClusterList,   /* Application output cluster list */
};
#endif	/* AF_TEST_ENABLE */


/* Basic */
zcl_basicAttr_t g_zcl_basicAttrs =
{
	.zclVersion 	= 0x03,
	.appVersion 	= 0x00,
	.stackVersion 	= 0x02,
	.hwVersion		= 0x00,
	.manuName		= ZCL_BASIC_MFG_NAME,
	.modelId		= ZCL_BASIC_MODEL_ID,
	.datacode		= ZCL_BASIC_DATA_CODE,
	.powerSource	= POWER_SOURCE_MAINS_1_PHASE,
	.swBuildId		= ZCL_BASIC_SW_BUILD_ID,
	.deviceEnable	= TRUE,
};

void ldsUpdateZclBasicInformation(void)
{
	memcpy(g_zcl_basicAttrs.modelId, ldsMfgTokenGetModelID(), 33);
//	memcpy(&g_zcl_basicAttrs.datacode[1], (uint8_t *)XT_DATACODE, sizeof(XT_DATACODE));
	memcpy(&g_zcl_basicAttrs.swBuildId[1], (uint8_t *)XT_CREDENTIALS_FW_VERSION, sizeof(XT_CREDENTIALS_FW_VERSION));
	g_zcl_basicAttrs.swBuildId[0] = strlen(XT_CREDENTIALS_FW_VERSION);
}

//const
zclAttrInfo_t basic_attrTbl[] =
{
	{ ZCL_ATTRID_BASIC_ZCL_VER,      		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.zclVersion},
	{ ZCL_ATTRID_BASIC_APP_VER,      		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.appVersion},
	{ ZCL_ATTRID_BASIC_STACK_VER,    		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.stackVersion},
	{ ZCL_ATTRID_BASIC_HW_VER,       		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.hwVersion},
	{ ZCL_ATTRID_BASIC_MFR_NAME,     		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)g_zcl_basicAttrs.manuName},
	{ ZCL_ATTRID_BASIC_MODEL_ID,     		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)g_zcl_basicAttrs.modelId},
	{ ZCL_ATTRID_BASIC_DATE_CODE,    		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.datacode},
	{ ZCL_ATTRID_BASIC_POWER_SOURCE, 		ZCL_DATA_TYPE_ENUM8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.powerSource},
	{ ZCL_ATTRID_BASIC_DEV_ENABLED,  		ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_basicAttrs.deviceEnable},
	{ ZCL_ATTRID_BASIC_SW_BUILD_ID,  		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs.swBuildId},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_BASIC_ATTR_NUM	  sizeof(basic_attrTbl) / sizeof(zclAttrInfo_t)


/* Identify */
zcl_identifyAttr_t g_zcl_identifyAttrs =
{
	.identifyTime	= 0x0000,
};

const zclAttrInfo_t identify_attrTbl[] =
{
	{ ZCL_ATTRID_IDENTIFY_TIME,  			ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_identifyAttrs.identifyTime },

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_IDENTIFY_ATTR_NUM	 sizeof(identify_attrTbl) / sizeof(zclAttrInfo_t)

#ifdef ZCL_GROUP
/* Group */
zcl_groupAttr_t g_zcl_groupAttrs =
{
	.nameSupport	= 0,
};

const zclAttrInfo_t group_attrTbl[] =
{
	{ ZCL_ATTRID_GROUP_NAME_SUPPORT,  		ZCL_DATA_TYPE_BITMAP8,  ACCESS_CONTROL_READ,  (u8*)&g_zcl_groupAttrs.nameSupport },

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_GROUP_ATTR_NUM	  sizeof(group_attrTbl) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_SCENE
/* Scene */
zcl_sceneAttr_t g_zcl_sceneAttrs =
{
	.sceneCount		= 0,
	.currentScene	= 0,
	.currentGroup	= 0x0000,
	.sceneValid		= FALSE,
	.nameSupport	= 0,
};

const zclAttrInfo_t scene_attrTbl[] =
{
    { ZCL_ATTRID_SCENE_SCENE_COUNT,       	ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs.sceneCount		},
    { ZCL_ATTRID_SCENE_CURRENT_SCENE,     	ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs.currentScene   },
    { ZCL_ATTRID_SCENE_CURRENT_GROUP,     	ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs.currentGroup   },
    { ZCL_ATTRID_SCENE_SCENE_VALID,       	ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs.sceneValid     },
    { ZCL_ATTRID_SCENE_NAME_SUPPORT,      	ZCL_DATA_TYPE_BITMAP8,  ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs.nameSupport    },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_SCENE_ATTR_NUM	 sizeof(scene_attrTbl) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_ON_OFF
/* On/Off */
zcl_onOffAttr_t g_zcl_onOffAttrs =
{
	.onOff				= 0x00,
	.globalSceneControl	= 1,
	.onTime				= 0x0000,
	.offWaitTime		= 0x0000,
	.startUpOnOff 		= ZCL_START_UP_ONOFF_SET_ONOFF_TO_ON,
};

const zclAttrInfo_t onOff_attrTbl[] =
{
	{ ZCL_ATTRID_ONOFF,  					ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE,  (u8*)&g_zcl_onOffAttrs.onOff},
	{ ZCL_ATTRID_GLOBAL_SCENE_CONTROL, 		ZCL_DATA_TYPE_BOOLEAN, 	ACCESS_CONTROL_READ, 							  (u8*)&g_zcl_onOffAttrs.globalSceneControl},
	{ ZCL_ATTRID_ON_TIME, 					ZCL_DATA_TYPE_UINT16, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 	  (u8*)&g_zcl_onOffAttrs.onTime},
	{ ZCL_ATTRID_OFF_WAIT_TIME, 			ZCL_DATA_TYPE_UINT16, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 	  (u8*)&g_zcl_onOffAttrs.offWaitTime},
	{ ZCL_ATTRID_START_UP_ONOFF, 			ZCL_DATA_TYPE_ENUM8, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 	  (u8*)&g_zcl_onOffAttrs.startUpOnOff},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  							  (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_ONOFF_ATTR_NUM	 sizeof(onOff_attrTbl) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_LEVEL_CTRL
/* Level */
zcl_levelAttr_t g_zcl_levelAttrs =
{
	.curLevel				= ZCL_LEVEL_ATTR_MAX_LEVEL,
	.remainingTime			= 0,
	.options				= 0,
	.minLevel				= ZCL_LEVEL_ATTR_MIN_LEVEL,
	.maxLevel				= ZCL_LEVEL_ATTR_MAX_LEVEL,
	.startUpCurrentLevel 	= ZCL_START_UP_CURRENT_LEVEL_TO_PREVIOUS,
};

const zclAttrInfo_t level_attrTbl[] =
{
	{ ZCL_ATTRID_LEVEL_CURRENT_LEVEL,  			ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_levelAttrs.curLevel },
	{ ZCL_ATTRID_LEVEL_REMAINING_TIME, 			ZCL_DATA_TYPE_UINT16,  ACCESS_CONTROL_READ,  							(u8*)&g_zcl_levelAttrs.remainingTime },
	{ ZCL_ATTRID_LEVEL_MIN_LEVEL,  				ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ, 							(u8*)&g_zcl_levelAttrs.minLevel },
	{ ZCL_ATTRID_LEVEL_MAX_LEVEL,  				ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ, 							(u8*)&g_zcl_levelAttrs.maxLevel },
	{ ZCL_ATTRID_LEVEL_OPTIONS,  				ZCL_DATA_TYPE_BITMAP8, ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 		(u8*)&g_zcl_levelAttrs.options },
	{ ZCL_ATTRID_LEVEL_START_UP_CURRENT_LEVEL,  ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE,  	(u8*)&g_zcl_levelAttrs.startUpCurrentLevel },

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 		ZCL_DATA_TYPE_UINT16,  ACCESS_CONTROL_READ,  							(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_LEVEL_ATTR_NUM	 sizeof(level_attrTbl) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_LIGHT_COLOR_CONTROL
/* Color Control */
zcl_lightColorCtrlAttr_t g_zcl_colorCtrlAttrs =
{
#if COLOR_RGB_SUPPORT && COLOR_CCT_SUPPORT
//	.colorCapabilities				= ZCL_COLOR_CAPABILITIES_BIT_HUE_SATURATION |
//									  ZCL_COLOR_CAPABILITIES_BIT_X_Y_ATTRIBUTES |
//									  ZCL_COLOR_CAPABILITIES_BIT_COLOR_TEMPERATURE,
	.colorCapabilities				= ZCL_COLOR_CAPABILITIES_BIT_X_Y_ATTRIBUTES |
									  ZCL_COLOR_CAPABILITIES_BIT_COLOR_TEMPERATURE,
	.colorMode						= ZCL_COLOR_MODE_CURRENT_X_Y,
	.enhancedColorMode				= ZCL_COLOR_MODE_CURRENT_X_Y,
#elif COLOR_RGB_SUPPORT
	.colorCapabilities				= ZCL_COLOR_CAPABILITIES_BIT_HUE_SATURATION |
									  ZCL_COLOR_CAPABILITIES_BIT_X_Y_ATTRIBUTES,
	.colorMode						= ZCL_COLOR_MODE_CURRENT_X_Y,
	.enhancedColorMode				= ZCL_COLOR_MODE_CURRENT_X_Y,
#elif COLOR_CCT_SUPPORT
	.colorCapabilities				= ZCL_COLOR_CAPABILITIES_BIT_COLOR_TEMPERATURE,
	.colorMode						= ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS,
	.enhancedColorMode				= ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS,
#endif
	.options						= 0,
	.numOfPrimaries					= 0,
#if COLOR_RGB_SUPPORT
	.currentX 						= 0x753f,
	.currentY						= 0x68f6,

//	.currentHue						= 0x18,
//	.currentSaturation				= 0xc9,
#if COLOR_LOOP_SUPPORT
	.colorLoopActive				= 0x00,
	.colorLoopDirection				= 0x00,
	.colorLoopTime					= 0x0019,
	.colorLoopStartEnhancedHue		= 0x2300,
	.colorLoopStoredEnhancedHue		= 0x0000,
#endif//COLOR_LOOP_SUPPORT
#endif
#if COLOR_CCT_SUPPORT
	.colorTemperatureMireds			= COLOR_TEMPERATURE_PHYSICAL_DEFAULT, //COLOR_TEMPERATURE_PHYSICAL_MAX,
	.colorTempPhysicalMinMireds		= COLOR_TEMPERATURE_PHYSICAL_MIN,
	.colorTempPhysicalMaxMireds 	= COLOR_TEMPERATURE_PHYSICAL_MAX,
	.coupleColorTempToLevelMinMireds = COLOR_TEMPERATURE_PHYSICAL_MIN,
	.startUpColorTemperatureMireds 	= ZCL_START_UP_COLOR_TEMPERATURE_MIREDS_TO_PREVIOUS, //COLOR_TEMPERATURE_PHYSICAL_DEFAULT, //ZCL_START_UP_COLOR_TEMPERATURE_MIREDS_TO_PREVIOUS,
#endif
};

const zclAttrInfo_t lightColorCtrl_attrTbl[] =
{
    { ZCL_ATTRID_COLOR_MODE,              			ZCL_DATA_TYPE_ENUM8,   	ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs.colorMode },
    { ZCL_ATTRID_COLOR_OPTIONS,           			ZCL_DATA_TYPE_BITMAP8, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_colorCtrlAttrs.options },
    { ZCL_ATTRID_ENHANCED_COLOR_MODE,     			ZCL_DATA_TYPE_ENUM8,   	ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs.enhancedColorMode },
    { ZCL_ATTRID_COLOR_CAPABILITIES,       			ZCL_DATA_TYPE_BITMAP16, ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs.colorCapabilities },
    { ZCL_ATTRID_NUMBER_OF_PRIMARIES,     			ZCL_DATA_TYPE_UINT8,   	ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs.numOfPrimaries },
#if COLOR_RGB_SUPPORT
    { ZCL_ATTRID_CURRENT_X,             			ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs.currentX },
    { ZCL_ATTRID_CURRENT_Y,      					ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs.currentY },
//    { ZCL_ATTRID_CURRENT_HUE,             			ZCL_DATA_TYPE_UINT8,   	ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs.currentHue },
//    { ZCL_ATTRID_CURRENT_SATURATION,      			ZCL_DATA_TYPE_UINT8,   	ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs.currentSaturation },
#if COLOR_LOOP_SUPPORT
    { ZCL_ATTRID_COLOR_LOOP_ACTIVE,       			ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, 							 (u8*)&g_zcl_colorCtrlAttrs.colorLoopActive },
    { ZCL_ATTRID_COLOR_LOOP_DIRECTION,    			ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, 							 (u8*)&g_zcl_colorCtrlAttrs.colorLoopDirection },
    { ZCL_ATTRID_COLOR_LOOP_TIME,         			ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ, 							 (u8*)&g_zcl_colorCtrlAttrs.colorLoopTime },
    { ZCL_ATTRID_COLOR_LOOP_START_ENHANCED_HUE,   	ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs.colorLoopStartEnhancedHue },
    { ZCL_ATTRID_COLOR_LOOP_STORED_ENHANCED_HUE,  	ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs.colorLoopStoredEnhancedHue },
#endif//COLOR_LOOP_SUPPORT
#endif
#if COLOR_CCT_SUPPORT
    { ZCL_ATTRID_COLOR_TEMPERATURE_MIREDS,			ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs.colorTemperatureMireds },
    { ZCL_ATTRID_COLOR_TEMP_PHYSICAL_MIN_MIREDS,  	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs.colorTempPhysicalMinMireds },
    { ZCL_ATTRID_COLOR_TEMP_PHYSICAL_MAX_MIREDS,  	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs.colorTempPhysicalMaxMireds },
	{ ZCL_ATTRID_COUPLE_COLOR_TEMP_TO_LEVEL_MIN_MIREDS, ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs.coupleColorTempToLevelMinMireds },
    { ZCL_ATTRID_START_UP_COLOR_TEMPERATURE_MIREDS, ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE,      (u8*)&g_zcl_colorCtrlAttrs.startUpColorTemperatureMireds },
#endif
    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 			ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,  							 (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_COLOR_ATTR_NUM	 sizeof(lightColorCtrl_attrTbl) / sizeof(zclAttrInfo_t)
#endif

/**
 *  @brief Definition for simple light ZCL specific cluster
 */
const zcl_specClusterInfo_t g_sampleLightClusterList[] =
{
	{ZCL_CLUSTER_GEN_BASIC,				 MANUFACTURER_CODE_NONE, 	ZCL_BASIC_ATTR_NUM, 	basic_attrTbl,  		zcl_basic_register,			 sampleLight_basicCb},
	{ZCL_CLUSTER_GEN_IDENTIFY,			 MANUFACTURER_CODE_NONE, 	ZCL_IDENTIFY_ATTR_NUM,	identify_attrTbl,		zcl_identify_register,		 sampleLight_identifyCb},
#ifdef ZCL_GROUP
	{ZCL_CLUSTER_GEN_GROUPS,			 MANUFACTURER_CODE_NONE, 	ZCL_GROUP_ATTR_NUM, 	group_attrTbl,  		zcl_group_register,			 sampleLight_groupCb},
#endif
#ifdef ZCL_SCENE
	{ZCL_CLUSTER_GEN_SCENES,			 MANUFACTURER_CODE_IKEA, 	ZCL_SCENE_ATTR_NUM,		scene_attrTbl,			zcl_scene_register,			 sampleLight_sceneCb},
#endif
#ifdef ZCL_ON_OFF
	{ZCL_CLUSTER_GEN_ON_OFF,			 MANUFACTURER_CODE_NONE, 	ZCL_ONOFF_ATTR_NUM,		onOff_attrTbl,			zcl_onOff_register,			 sampleLight_onOffCb},
#endif
#ifdef ZCL_LEVEL_CTRL
	{ZCL_CLUSTER_GEN_LEVEL_CONTROL,		 MANUFACTURER_CODE_NONE, 	ZCL_LEVEL_ATTR_NUM,		level_attrTbl,			zcl_level_register,			 sampleLight_levelCb},
#endif
#ifdef ZCL_LIGHT_COLOR_CONTROL
	{ZCL_CLUSTER_LIGHTING_COLOR_CONTROL, MANUFACTURER_CODE_NONE, 	ZCL_COLOR_ATTR_NUM,		lightColorCtrl_attrTbl,	zcl_lightColorCtrl_register, sampleLight_colorCtrlCb},
#endif
};

u8 SAMPLELIGHT_CB_CLUSTER_NUM = (sizeof(g_sampleLightClusterList)/sizeof(g_sampleLightClusterList[0]));


/**********************************************************************
 * FUNCTIONS
 */


/*********************************************************************
 * @fn      zcl_onOffAttr_save
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_onOffAttr_save(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_ON_OFF
#if NV_ENABLE
	zcl_nv_onOff_t zcl_nv_onOff;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_ON_OFF, sizeof(zcl_nv_onOff_t), (u8*)&zcl_nv_onOff);

	if(st == NV_SUCC){
		if((zcl_nv_onOff.onOff != g_zcl_onOffAttrs.onOff) || (zcl_nv_onOff.startUpOnOff != g_zcl_onOffAttrs.startUpOnOff)){
			zcl_nv_onOff.onOff = g_zcl_onOffAttrs.onOff;
			zcl_nv_onOff.startUpOnOff = g_zcl_onOffAttrs.startUpOnOff;

			st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_ON_OFF, sizeof(zcl_nv_onOff_t), (u8*)&zcl_nv_onOff);
		}
	}else if(st == NV_ITEM_NOT_FOUND){
		zcl_nv_onOff.onOff = g_zcl_onOffAttrs.onOff;
		zcl_nv_onOff.startUpOnOff = g_zcl_onOffAttrs.startUpOnOff;

		st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_ON_OFF, sizeof(zcl_nv_onOff_t), (u8*)&zcl_nv_onOff);
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_onOffAttr_restore
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_onOffAttr_restore(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_ON_OFF
#if NV_ENABLE
	zcl_nv_onOff_t zcl_nv_onOff;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_ON_OFF, sizeof(zcl_nv_onOff_t), (u8*)&zcl_nv_onOff);

	if(st == NV_SUCC){
		g_zcl_onOffAttrs.onOff = zcl_nv_onOff.onOff;
		g_zcl_onOffAttrs.startUpOnOff = zcl_nv_onOff.startUpOnOff;
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_levelAttr_save
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_levelAttr_save(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LEVEL_CTRL
#if NV_ENABLE
	zcl_nv_level_t zcl_nv_level;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_LEVEL, sizeof(zcl_nv_level_t), (u8*)&zcl_nv_level);

	if(st == NV_SUCC){
		if((zcl_nv_level.curLevel != g_zcl_levelAttrs.curLevel) || (zcl_nv_level.startUpCurLevel != g_zcl_levelAttrs.startUpCurrentLevel)){
			zcl_nv_level.curLevel = g_zcl_levelAttrs.curLevel;
			zcl_nv_level.startUpCurLevel = g_zcl_levelAttrs.startUpCurrentLevel;

			st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_LEVEL, sizeof(zcl_nv_level_t), (u8*)&zcl_nv_level);
		}
	}else if(st == NV_ITEM_NOT_FOUND){
		zcl_nv_level.curLevel = g_zcl_levelAttrs.curLevel;
		zcl_nv_level.startUpCurLevel = g_zcl_levelAttrs.startUpCurrentLevel;

		st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_LEVEL, sizeof(zcl_nv_level_t), (u8*)&zcl_nv_level);
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_levelAttr_restore
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_levelAttr_restore(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LEVEL_CTRL
#if NV_ENABLE
	zcl_nv_level_t zcl_nv_level;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_LEVEL, sizeof(zcl_nv_level_t), (u8*)&zcl_nv_level);

	if(st == NV_SUCC){
		g_zcl_levelAttrs.curLevel = zcl_nv_level.curLevel;
		g_zcl_levelAttrs.startUpCurrentLevel = zcl_nv_level.startUpCurLevel;
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_colorCtrlAttr_save
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_colorCtrlAttr_save(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LIGHT_COLOR_CONTROL
#if NV_ENABLE
	bool needSave = FALSE;
	zcl_nv_colorCtrl_t zcl_nv_colorCtrl;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_COLOR_CTRL, sizeof(zcl_nv_colorCtrl_t), (u8*)&zcl_nv_colorCtrl);

	if(st == NV_SUCC){
		if((zcl_nv_colorCtrl.colorMode != g_zcl_colorCtrlAttrs.colorMode)	||
		   (zcl_nv_colorCtrl.currentHue != g_zcl_colorCtrlAttrs.currentHue) ||
		   (zcl_nv_colorCtrl.currentSaturation != g_zcl_colorCtrlAttrs.currentSaturation) ||
		   (zcl_nv_colorCtrl.currentX != g_zcl_colorCtrlAttrs.currentX) ||
		   (zcl_nv_colorCtrl.currentY != g_zcl_colorCtrlAttrs.currentY) ||
		   (zcl_nv_colorCtrl.colorTemperatureMireds != g_zcl_colorCtrlAttrs.colorTemperatureMireds) ||
		   (zcl_nv_colorCtrl.startUpColorTemperatureMireds != g_zcl_colorCtrlAttrs.startUpColorTemperatureMireds)){
			needSave = TRUE;
		}
	}else if(st == NV_ITEM_NOT_FOUND){
		needSave = TRUE;
	}

	if(needSave){
		zcl_nv_colorCtrl.currentHue = g_zcl_colorCtrlAttrs.currentHue;
		zcl_nv_colorCtrl.currentSaturation = g_zcl_colorCtrlAttrs.currentSaturation;
		zcl_nv_colorCtrl.currentX = g_zcl_colorCtrlAttrs.currentX;
		zcl_nv_colorCtrl.currentY = g_zcl_colorCtrlAttrs.currentY;
		zcl_nv_colorCtrl.colorTemperatureMireds = g_zcl_colorCtrlAttrs.colorTemperatureMireds;
		zcl_nv_colorCtrl.startUpColorTemperatureMireds = g_zcl_colorCtrlAttrs.startUpColorTemperatureMireds;
		zcl_nv_colorCtrl.colorMode = g_zcl_colorCtrlAttrs.colorMode;
		zcl_nv_colorCtrl.enhancedColorMode = g_zcl_colorCtrlAttrs.enhancedColorMode;

		st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_COLOR_CTRL, sizeof(zcl_nv_colorCtrl_t), (u8*)&zcl_nv_colorCtrl);
//		st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_COLOR_CTRL, sizeof(zcl_nv_colorCtrl_t), (u8*)&zcl_nv_colorCtrl);
//		printf("zcl_colorCtrlAttr_read test2222: %d, %d, %x, %d, %d, %d\n", st, needSave, zcl_nv_colorCtrl.colorMode,
//									zcl_nv_colorCtrl.colorTemperatureMireds, zcl_nv_colorCtrl.currentX, zcl_nv_colorCtrl.currentY);
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_colorCtrlAttr_restore
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_colorCtrlAttr_restore(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LIGHT_COLOR_CONTROL
#if NV_ENABLE
	zcl_nv_colorCtrl_t zcl_nv_colorCtrl;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_COLOR_CTRL, sizeof(zcl_nv_colorCtrl_t), (u8*)&zcl_nv_colorCtrl);
	if(st == NV_SUCC){
		g_zcl_colorCtrlAttrs.colorMode = zcl_nv_colorCtrl.colorMode;
		g_zcl_colorCtrlAttrs.enhancedColorMode = zcl_nv_colorCtrl.enhancedColorMode;
		g_zcl_colorCtrlAttrs.currentHue = zcl_nv_colorCtrl.currentHue;
		g_zcl_colorCtrlAttrs.currentSaturation = zcl_nv_colorCtrl.currentSaturation;
		g_zcl_colorCtrlAttrs.currentX = zcl_nv_colorCtrl.currentX;
		g_zcl_colorCtrlAttrs.currentY = zcl_nv_colorCtrl.currentY;
		g_zcl_colorCtrlAttrs.colorTemperatureMireds = zcl_nv_colorCtrl.colorTemperatureMireds;
		g_zcl_colorCtrlAttrs.startUpColorTemperatureMireds = zcl_nv_colorCtrl.startUpColorTemperatureMireds;
	}

	//printf("zcl_colorCtrlAttr_restore: %d, %x, %d, %d, %d\n", st, zcl_nv_colorCtrl.colorMode,
	//							zcl_nv_colorCtrl.colorTemperatureMireds, zcl_nv_colorCtrl.currentX, zcl_nv_colorCtrl.currentY);
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_sampleLightAttrsInit
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
void zcl_sampleLightAttrsInit(void)
{
	zcl_onOffAttr_restore();
	zcl_levelAttr_restore();
	zcl_colorCtrlAttr_restore();
}

#endif	/* __PROJECT_TL_DIMMABLE_LIGHT__ */
