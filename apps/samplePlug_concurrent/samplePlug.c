/********************************************************************************************************
 * @file    samplePlug.c
 *
 * @brief   This is the source file for samplePlug
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
#include "zb_api.h"
#include "zcl_include.h"
#include "bdb.h"
#include "ota.h"
#include "gp.h"
#include "samplePlug.h"
#include "samplePlugCtrl.h"
#include "app_ui.h"
#include "factory_reset.h"
#if ZBHCI_EN
#include "zbhci.h"
#endif
#if ZCL_WWAH_SUPPORT
#include "wwah.h"
#endif

/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * GLOBAL VARIABLES
 */
bool gLightAttrsChanged = FALSE;
app_linkKey_info_t gLightLinkKey;
app_ctx_t gLightCtx[2];

#ifdef ZCL_OTA
extern ota_callBack_t sampleLight_otaCb;

//running code firmware information
ota_preamble_t sampleLight_otaInfo = {
	.fileVer 			= FILE_VERSION,
	.imageType 			= IMAGE_TYPE,
	.manufacturerCode 	= MANUFACTURER_CODE_TELINK,
};
#endif


//Must declare the application call back function which used by ZDO layer
const zdo_appIndCb_t appCbLst = {
	bdb_zdoStartDevCnf,//start device cnf cb
	NULL,//reset cnf cb
	NULL,//device announce indication cb
	sampleLight_leaveIndHandler,//leave ind cb
	sampleLight_leaveCnfHandler,//leave cnf cb
	sampleLight_nwkUpdateIndicateHandler,//nwk update ind cb
	NULL,//permit join ind cb
	NULL,//nlme sync cnf cb
	NULL,//tc join ind cb
	NULL,//tc detects that the frame counter is near limit
};


/**
 *  @brief Definition for bdb commissioning setting
 */
bdb_commissionSetting_t g_bdbCommissionSetting = {
	.linkKey.tcLinkKey.keyType = SS_GLOBAL_LINK_KEY,
	.linkKey.tcLinkKey.key = (u8 *)tcLinkKeyCentralDefault,       		//can use unique link key stored in NV
#if TEST_FOR_CERTIFICATION
	.linkKey.distributeLinkKey.keyType = CERTIFICATION_KEY,
	.linkKey.distributeLinkKey.key = (u8 *)linkKeyDistributedCertification,  //use linkKeyDistributedCertification before testing
	.linkKey.touchLinkKey.keyType = CERTIFICATION_KEY,
	.linkKey.touchLinkKey.key = (u8 *)touchLinkKeyCertification,   			//use touchLinkKeyCertification before testing
#else
	.linkKey.distributeLinkKey.keyType = MASTER_KEY,
	.linkKey.distributeLinkKey.key = (u8 *)linkKeyDistributedMaster,  	//use linkKeyDistributedCertification before testing
	.linkKey.touchLinkKey.keyType = MASTER_KEY,
	.linkKey.touchLinkKey.key = (u8 *)touchLinkKeyMaster,   			//use touchLinkKeyCertification before testing
#endif
#if TOUCHLINK_SUPPORT
	.touchlinkEnable = 1,												/* enable touch-link */
#else
	.touchlinkEnable = 0,												/* disable touch-link */
#endif
	.touchlinkChannel = DEFAULT_CHANNEL, 								/* touch-link default operation channel for target */
	.touchlinkLqiThreshold = 0xA0,			   							/* threshold for touch-link scan req/resp command */
};

/**********************************************************************
 * LOCAL VARIABLES
 */
ev_timer_event_t *sampleLightAttrsStoreTimerEvt = NULL;


/**********************************************************************
 * FUNCTIONS
 */

/*********************************************************************
 * @fn      stack_init
 *
 * @brief   This function initialize the ZigBee stack and related profile. If HA/ZLL profile is
 *          enabled in this application, related cluster should be registered here.
 *
 * @param   None
 *
 * @return  None
 */
void stack_init(void)
{
	/* Initialize ZB stack */
	zb_init();

	/* Register stack CB */
    zb_zdoCbRegister((zdo_appIndCb_t *)&appCbLst);
}

/*********************************************************************
 * @fn      user_app_init
 *
 * @brief   This function initialize the application(Endpoint) information for this node.
 *
 * @param   None
 *
 * @return  None
 */
void user_app_init(void)
{
	af_nodeDescManuCodeUpdate(MANUFACTURER_CODE_TELINK);

    /* Initialize ZCL layer */
	/* Register Incoming ZCL Foundation command/response messages */
    zcl_init(sampleLight_zclProcessIncomingMsg);

	/* Register endPoint */
	af_endpointRegister(SAMPLE_LIGHT_ENDPOINT, (af_simple_descriptor_t *)&sampleLight_simpleDesc, zcl_rx_handler, NULL);
#if PLUG_EP_2_SUPPORT
	af_endpointRegister(SAMPLE_LIGHT_ENDPOINT_2, (af_simple_descriptor_t *)&sampleLight_simpleDesc_2, zcl_rx_handler, NULL);
#endif
#if AF_TEST_ENABLE
	/* A sample of AF data handler. */
	af_endpointRegister(SAMPLE_TEST_ENDPOINT, (af_simple_descriptor_t *)&sampleTestDesc, afTest_rx_handler, afTest_dataSendConfirm);
#endif

	/* Initialize or restore attributes, this must before 'zcl_register()' */
	zcl_sampleLightAttrsInit();//SAMPLE_LIGHT_ENDPOINT
#if PLUG_EP_2_SUPPORT
	zcl_sampleLightAttrsInit_2();//SAMPLE_LIGHT_ENDPOINT_2
#endif
	zcl_reportingTabInit();

	/* Register ZCL specific cluster information */
	zcl_register(SAMPLE_LIGHT_ENDPOINT, SAMPLELIGHT_CB_CLUSTER_NUM, (zcl_specClusterInfo_t *)g_sampleLightClusterList);
#if PLUG_EP_2_SUPPORT
	zcl_register(SAMPLE_LIGHT_ENDPOINT_2, SAMPLELIGHT_CB_CLUSTER_NUM_2, (zcl_specClusterInfo_t *)g_sampleLightClusterList_2);
#endif

#if ZCL_GP_SUPPORT
	/* Initialize GP */
	gp_init(SAMPLE_LIGHT_ENDPOINT);
#endif

#if ZCL_OTA_SUPPORT
	/* Initialize OTA */
    ota_init(OTA_TYPE_CLIENT, (af_simple_descriptor_t *)&sampleLight_simpleDesc, &sampleLight_otaInfo, &sampleLight_otaCb);
#endif

#if ZCL_WWAH_SUPPORT
    /* Initialize WWAH server */
    wwah_init(WWAH_TYPE_SERVER, (af_simple_descriptor_t *)&sampleLight_simpleDesc);
#endif
}



s32 sampleLightAttrsStoreTimerCb(void *arg)
{
#if ZCL_ON_OFF_SUPPORT
	zcl_onOffAttr_save();
#if PLUG_EP_2_SUPPORT
	zcl_onOffAttr_save_2();
#endif
#endif

#if ZCL_LEVEL_CTRL_SUPPORT
	zcl_levelAttr_save();
#if PLUG_EP_2_SUPPORT
	zcl_levelAttr_save_2();
#endif
#endif

#if ZCL_LIGHT_COLOR_CONTROL_SUPPORT
	zcl_colorCtrlAttr_save();
#if PLUG_EP_2_SUPPORT
	zcl_colorCtrlAttr_save_2();
#endif
#endif

	sampleLightAttrsStoreTimerEvt = NULL;
	return -1;
}

void sampleLightAttrsStoreTimerStart(void)
{
	if(sampleLightAttrsStoreTimerEvt){
		TL_ZB_TIMER_CANCEL(&sampleLightAttrsStoreTimerEvt);
	}
	sampleLightAttrsStoreTimerEvt = TL_ZB_TIMER_SCHEDULE(sampleLightAttrsStoreTimerCb, NULL, 200);
}

void sampleLightAttrsChk(void)
{
	if(gLightAttrsChanged){
		gLightAttrsChanged = FALSE;
		if(zb_isDeviceJoinedNwk()){
			sampleLightAttrsStoreTimerStart();
		}
	}
}

void app_task(void)
{
	app_key_handler();
	localPermitJoinState();

	if(BDB_STATE_GET() == BDB_STATE_IDLE){
		//factoryRst_handler();

		report_handler();

#if 1/* NOTE: If set to '1', the latest status of lighting will be stored. */
		sampleLightAttrsChk();
#endif
	}
}

static void sampleLightSysException(void)
{
#if 1
	SYSTEM_RESET();
#else
	led_on(LED_POWER);
	while(1);
#endif
}

#if APP_USER_BINDING_TABLE
/*
 * if you have changed the struct of "aps_binding_table_t", please use the "aps_userBindingTblRestore"
 * to restore the old binding table.
 * change "APS_BINDING_TABLE_NUM_V1" and the struct of "aps_binding_table_t"
 * to let it same to the old binding table
 *
 * */
aps_binding_table_t gOldBindingTbl;
void app_userBindingTblRestore(void){
	aps_userBindingTblRestore(&gOldBindingTbl, sizeof(aps_binding_table_t), APS_BINDING_TABLE_NUM_V1);
}
#endif

/*********************************************************************
 * @fn      user_init
 *
 * @brief   User level initialization code.
 *
 * @param   isRetention - if it is waking up with ram retention.
 *
 * @return  None
 */
void user_zb_init(bool isRetention)
{
	(void)isRetention;

	/* Register except handler for test */
	sys_exceptHandlerRegister(sampleLightSysException);

	/* Initialize LEDs*/
	led_init();

	light_init();

	//factoryRst_init();

	/* Initialize Stack */
	stack_init();

#if APP_USER_BINDING_TABLE
	app_userBindingTblRestore();
#endif

	/* Initialize user application */
	user_app_init();

	bool isFactoryNew = zb_isDeviceFactoryNew();
	printf("isFactoryNew: %x\n", isFactoryNew);
	printf("ep1: onOff = %x, startUp = %x\n", g_zcl_onOffAttrs.onOff, g_zcl_onOffAttrs.startUpOnOff);
#if PLUG_EP_2_SUPPORT
	printf("ep2: onOff = %x, startUp = %x\n", g_zcl_onOffAttrs_2.onOff, g_zcl_onOffAttrs_2.startUpOnOff);
#endif

	/* Adjust light state to default attributes*/
	light_adjust();

	/* User's Task */
#if ZBHCI_EN
	zbhciInit();
	ev_on_poll(EV_POLL_HCI, zbhciTask);
#endif
	ev_on_poll(EV_POLL_IDLE, app_task);

    /* Read the pre-install code from NV */
	if(bdb_preInstallCodeLoad(&gLightLinkKey.keyType, gLightLinkKey.key) == RET_OK){
		g_bdbCommissionSetting.linkKey.tcLinkKey.keyType = gLightLinkKey.keyType;
		g_bdbCommissionSetting.linkKey.tcLinkKey.key = gLightLinkKey.key;
	}

    /* Set default reporting configuration */
    u8 reportableChange[2] = {0x00, 0x00};
    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
    						ZCL_CLUSTER_GEN_ON_OFF, ZCL_ATTRID_ONOFF,
    						0x000a, 0x003d, (u8 *)&reportableChange);
#if PLUG_EP_2_SUPPORT
    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT_2, HA_PROFILE_ID,
    						ZCL_CLUSTER_GEN_ON_OFF, ZCL_ATTRID_ONOFF,
    						0x000a, 0x003d, (u8 *)&reportableChange);
#endif

    /* Initialize BDB */
	bdb_init((af_simple_descriptor_t *)&sampleLight_simpleDesc, &g_bdbCommissionSetting, &g_zbDemoBdbCb, 1);
}

#endif  /* __PROJECT_TL_PLUG__ */

