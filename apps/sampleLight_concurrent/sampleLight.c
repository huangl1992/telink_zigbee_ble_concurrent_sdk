/********************************************************************************************************
 * @file    sampleLight.c
 *
 * @brief   This is the source file for sampleLight
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
#include "bdb.h"
#include "ota.h"
#include "gp.h"
#include "sampleLight.h"
#include "sampleLightCtrl.h"
#include "app_ui.h"
#include "factory_reset.h"
#if ZBHCI_EN
#include "zbhci.h"
#endif
#if ZCL_WWAH_SUPPORT
#include "wwah.h"
#endif

#include "lds_includes.h"
#include "lds_dim_algorithm.h"
#include "lds_light_control.h"
#include "lds_aging_test.h"
#include "lds_mfg_token_config.h"
#ifdef LDS_UART_ENABLE
#include "lds_uart.h"
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
app_ctx_t gLightCtx;


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
//	.linkKey.distributeLinkKey.keyType = CERTIFICATION_KEY,
//	.linkKey.distributeLinkKey.key = (u8 *)linkKeyDistributedCertification,  //use linkKeyDistributedCertification before testing
//	.linkKey.touchLinkKey.keyType = CERTIFICATION_KEY,
//	.linkKey.touchLinkKey.key = (u8 *)touchLinkKeyCertification,   			//use touchLinkKeyCertification before testing

#if TOUCHLINK_SUPPORT
	.touchlinkEnable = 1,												/* enable touch-link */
#else
	.touchlinkEnable = 0,												/* disable touch-link */
#endif
	.touchlinkChannel = DEFAULT_CHANNEL, 								/* touch-link default operation channel for target */
	.touchlinkLqiThreshold = 0xA0,			   							/* threshold for touch-link scan req/resp command */
};

void ldsBdbCommissionSettingParamsUpdate(void)
{
	if (ldsMfgTokenNetworkKeyGet())
	{
		g_bdbCommissionSetting.linkKey.distributeLinkKey.keyType = MASTER_KEY;
		g_bdbCommissionSetting.linkKey.distributeLinkKey.key = (u8 *)linkKeyDistributedMaster; 	//use linkKeyDistributedCertification before testing
		g_bdbCommissionSetting.linkKey.touchLinkKey.keyType = MASTER_KEY;
		g_bdbCommissionSetting.linkKey.touchLinkKey.key = (u8 *)touchLinkKeyMaster;   			//use touchLinkKeyCertification before testing
	}
	else
	{
		g_bdbCommissionSetting.linkKey.distributeLinkKey.keyType = CERTIFICATION_KEY;
		g_bdbCommissionSetting.linkKey.distributeLinkKey.key = (u8 *)linkKeyDistributedCertification;  //use linkKeyDistributedCertification before testing
		g_bdbCommissionSetting.linkKey.touchLinkKey.keyType = CERTIFICATION_KEY;
		g_bdbCommissionSetting.linkKey.touchLinkKey.key = (u8 *)touchLinkKeyCertification;   			//use touchLinkKeyCertification before testing
	}
}
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
#if AF_TEST_ENABLE
	/* A sample of AF data handler. */
	af_endpointRegister(SAMPLE_TEST_ENDPOINT, (af_simple_descriptor_t *)&sampleTestDesc, afTest_rx_handler, afTest_dataSendConfirm);
#endif

	/* Initialize or restore attributes, this must before 'zcl_register()' */
	zcl_sampleLightAttrsInit();
	zcl_reportingTabInit();

	/* Register ZCL specific cluster information */

	ldsUpdateZclBasicInformation();
	zcl_register(SAMPLE_LIGHT_ENDPOINT, SAMPLELIGHT_CB_CLUSTER_NUM, (zcl_specClusterInfo_t *)g_sampleLightClusterList);

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
	zcl_onOffAttr_save();
	zcl_levelAttr_save();
	zcl_colorCtrlAttr_save();

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
	if(gLightCtx.lightAttrsChanged){
		gLightCtx.lightAttrsChanged = FALSE;
		if(zb_isDeviceJoinedNwk()){
			sampleLightAttrsStoreTimerStart();
		}
	}
}

//#define LDS_ADC_EN
//#define TEST_ENABLE
void app_task(void)
{
#ifdef TEST_ENABLE
	static u32 A_test_main_loop;
	A_test_main_loop++;

	if (clock_time_exceed(A_test_main_loop, 15000 * 1000))
	{
		A_test_main_loop = clock_time();
		ldsEnterMatterMode();
		LDS_LOG_I("Enter Matter mode for Zigbee mode.....\n");
	}
#endif

#ifdef LDS_ADC_EN
	static u32 A_task_main_loop;
#endif
//	A_task_main_loop++;
#if defined(LDS_I2C_CHANGE_ENABLE)
	static uint32_t A_test_loop;
	A_test_loop++;
#endif

#if (!DUAL_MODE_WITH_MATTER) || !defined(DUAL_MODE_WITH_MATTER)
	app_key_handler();
	localPermitJoinState();
#endif

	if(BDB_STATE_GET() == BDB_STATE_IDLE){
		factoryRst_handler();

		report_handler();

#if 1/* NOTE: If set to '1', the latest status of lighting will be stored. */
		sampleLightAttrsChk();
#endif
#ifdef LDS_ADC_EN
		if (clock_time_exceed(A_task_main_loop, 2000 * 1000))
		{
			A_task_main_loop = clock_time();
			uint16_t voltage = ldsDeviceAdcVoltageGet();
			uint8_t temp = ldsTrfVoltageChangeTemperature(voltage);

			LDS_LOG_I("NTC test: %d, %d\n",voltage, temp);
		}
#endif
	}
#if defined(LDS_I2C_CHANGE_ENABLE)
	if (ldsPwmUpdateEndFlagGet())
	{
		if (clock_time_exceed(A_test_loop, 2000 * 1000))
		{
			A_test_loop = clock_time();
			ldsDriverI2cAgainWrite();
			ldsPwmUpdateEndFlagSet(0);
		}
	}
#endif
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
void ldsDeviceInit(void)
{
#if APP_LIGHT_USER_MODE_EN
	ldsDeviceInformationInfo();

	ldsDeviceAdcInit();
//#if defined(LDS_NTC_ENABLE)
	ldsDeivceNtcInit();
//#endif

	if (!zb_isDeviceFactoryNew()
		&& ldsDeviceAgingFunctionTestDone())
	{
		ldsLightStatusGetSceneId();
	}

	ldsDimAlgorithmParamSet(ldsMfgTokenDriverMinDutyCycle());

	ldsPwmLutInitTable();
	bool status = ldsDriverCommonInit();
	if (status)
	{
		LDS_LOG_I("lds driver common init fail\n");
	}

	const tsCCTAlgorithmParam_t  cct_param = {
		.driveMode = ldsMfgTokenCctDriverModeGet(),
		.minColorTemp = 2200,
		.maxColorTemp = 6500,
		.minLevel = 0.01,
	};

	ldsLightingCCTAlgorithmInit(cct_param);
#if defined(EXTENDEDCOLOR_LIGHT)
	lds_color_algorithm_init();
#endif

	if (!ldsDeviceAgingTestInit())
	{
		return;
	}
	else
	{
		init_to_startup(1, zb_isDeviceFactoryNew());
	}
#endif

	ldsBdbCommissionSettingParamsUpdate();
}

uint8_t ldsTxPowerParamsUpdate(uint8_t tx_power_value)
{
	uint8_t tx_power = 0;

	switch (tx_power_value)
	{
		case RF_TX_POWER_10dBm:
			tx_power = RF_POWER_INDEX_P9p90dBm;
			break;
		case RF_TX_POWER_9dBm:
			tx_power = RF_POWER_INDEX_P9p15dBm;
			break;
		case RF_TX_POWER_8dBm:
			tx_power = RF_POWER_INDEX_P8p25dBm;
			break;
		case RF_TX_POWER_7dBm:
			tx_power = RF_POWER_INDEX_P7p00dBm;
			break;
		case RF_TX_POWER_6dBm:
			tx_power = RF_POWER_INDEX_P6p32dBm;
			break;
		case RF_TX_POWER_5dBm:
			tx_power = RF_POWER_INDEX_P5p21dBm;
			break;
		case RF_TX_POWER_4dBm:
			tx_power = RF_POWER_INDEX_P4p02dBm;
			break;
		case RF_TX_POWER_3dBm:
			tx_power = RF_POWER_INDEX_P3p00dBm;
			break;
		case RF_TX_POWER_2dBm:
			tx_power = RF_POWER_INDEX_P2p01dBm;
			break;
		case RF_TX_POWER_1dBm:
			tx_power = RF_POWER_INDEX_P1p03dBm;
			break;
		case RF_TX_POWER_0dBm:
			tx_power = RF_POWER_INDEX_P0p01dBm;
			break;
		default:
			break;
	}

	return tx_power;
}

uint8_t ldsZigbeeTxPowerSet(void)
{
	uint8_t zb_tx_power = 0;

//	LDS_LOG_I("ldsZigbeeTxPowerSet current channel test: %d\r\n", rf_getChannel());
	if (rf_getChannel() == 26)
	{
		zb_tx_power = ldsTxPowerParamsUpdate(ldsMfgTokenZigbeeHighChannelTxPowerGet());
	}
	else
	{
		zb_tx_power = ldsTxPowerParamsUpdate(ldsMfgTokenZigbeeLowChannelTxPowerGet());
	}

	return zb_tx_power;
}

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

	ldsGetTokenInfoFromFlashGet();
	/* Register except handler for test */
	sys_exceptHandlerRegister(sampleLightSysException);

	/* Initialize LEDs*/
#if (!DUAL_MODE_WITH_MATTER) || !defined(DUAL_MODE_WITH_MATTER)
	led_init();
#endif

#if (!APP_LIGHT_USER_MODE_EN)
	light_init();
#endif
#if DUAL_MODE_WITH_MATTER
	if(nv_facrotyNewRstFlagCheck()){
		printf("last factoryRst not completed\n");
		light_adjust();
	}
#endif

	factoryRst_init();

	/* Initialize Stack */
	stack_init();

#if APP_USER_BINDING_TABLE
	app_userBindingTblRestore();
#endif

	/* Initialize user application */
	user_app_init();

	ldsDeviceInit();

	/* Adjust light state to default attributes*/
	light_adjust();

	/* User's Task */
#if ZBHCI_EN
	zbhciInit();
	ev_on_poll(EV_POLL_HCI, zbhciTask);
#endif
	ev_on_poll(EV_POLL_IDLE, app_task);
#ifdef LDS_UART_ENABLE
	ev_on_poll(EV_POLL_IDLE, ldsUartPacketRecvTask);
#endif
    /* Read the pre-install code from NV */
	if(bdb_preInstallCodeLoad(&gLightCtx.tcLinkKey.keyType, gLightCtx.tcLinkKey.key) == RET_OK){
		g_bdbCommissionSetting.linkKey.tcLinkKey.keyType = gLightCtx.tcLinkKey.keyType;
		g_bdbCommissionSetting.linkKey.tcLinkKey.key = gLightCtx.tcLinkKey.key;
	}

    /* Set default reporting configuration */
    u8 reportableChange[2] = {0x00, 0x00};
    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
    						ZCL_CLUSTER_GEN_ON_OFF, ZCL_ATTRID_ONOFF,
    						0x000a, 0x003d, (u8 *)&reportableChange);
    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
    						ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL,
    						0x000a, 0x003d, (u8 *)&reportableChange);
#if defined(EXTENDEDCOLOR_LIGHT)
//    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
//    						ZCL_CLUSTER_LIGHTING_COLOR_CONTROL, ZCL_ATTRID_CURRENT_HUE,
//    						0x000a, 0x003d, (u8 *)&reportableChange);
//    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
//    						ZCL_CLUSTER_LIGHTING_COLOR_CONTROL, ZCL_ATTRID_CURRENT_SATURATION,
//    						0x000a, 0x003d, (u8 *)&reportableChange);
    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
    						ZCL_CLUSTER_LIGHTING_COLOR_CONTROL, ZCL_ATTRID_CURRENT_X,
    						0x000a, 0x003d, (u8 *)&reportableChange);
    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
    						ZCL_CLUSTER_LIGHTING_COLOR_CONTROL, ZCL_ATTRID_CURRENT_Y,
    						0x000a, 0x003d, (u8 *)&reportableChange);
#endif

    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID,
    						ZCL_CLUSTER_LIGHTING_COLOR_CONTROL, ZCL_ATTRID_COLOR_TEMPERATURE_MIREDS,
    						0x000a, 0x003d, (u8 *)&reportableChange);

    /* Initialize BDB */
	bdb_init((af_simple_descriptor_t *)&sampleLight_simpleDesc, &g_bdbCommissionSetting, &g_zbDemoBdbCb, 1);
}

#endif  /* __PROJECT_TL_DIMMABLE_LIGHT__ */

