/**
 * @brief lds-light-effect.h header file
 * @file lds-light-effect.h
 * @version 1.0
 * @par Copyright:
 * Copyright (c) Leedarson Lighting 2000-2024. All rights reserved.
 */
#ifndef _LDS_LIGHT_EFFECT_H_
#define _LDS_LIGHT_EFFECT_H_

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include "lds_light_control.h"

typedef enum {
    LIGHTEFFECT_MULTISTATE_EFFECT_IDLE = 0x00,
    LIGHTEFFECT_MULTISTATE_EFFECT,
    LIGHTEFFECT_MULTISTATE_EFFECT_STOP,
} teLightEffectEvent_t;

typedef enum
{
    ColorMode_HSV = 0,
    ColorMode_xyY,
    ColorMode_CCT,
} teColorMode_t;

typedef struct {
    teLightEffectEvent_t state;
    uint8_t count;
    bool attrReport;
    bool attributeDelayStore;
    uint8_t arrayMembers;
} tsLightEffect_t;

typedef struct {
    lds_light_control_state_t lightState;
    uint32_t keepTime;  // unit: 1ms, 0xFFFFFFFF keep in current state
    bool bIsSet;
}tsLightEffectStateList_t;

void ldsLightMultiStateEffect(tsLightEffectStateList_t *bulbblinkstate, uint16_t loopCount, uint8_t arrayMembers, bool attrReport, bool lightStatusBackupOnOff, bool attributeDelayStore);

void ldsLightEffectMultiStateStoreCurrentStateCallback(bool lightStatusBackupOnOff);

bool ldsLightEffectMultiStateRecallSaveStateCallback(bool attributeDelayStore);

void ldsLightMultiEffectStop(void);

teLightEffectEvent_t ldsGetLightEffectState(void);

void ldsSetLightEffectState(teLightEffectEvent_t state);

void ldsSetAttrWhenReachTarget(lds_light_control_state_t *lightState);

bool ldsLightEffectIsGoingOff(void);

void ldsLightMultiEffectStopAndRecallSaveState(void);

void ldsLightMultiEffectFinish(void);

void ldsLightEffectGroupSyncStart(void);

void ldsLightPwmLowBrightnessOpenOptimization(uint16_t transition_time);

void ldsLightTriggerJoinNetworkEnableStart(void);

void ldsLightEffectJionNetworkStart(void);

void ldsLightEffectFactoryResetDefaultValue(void);

void ldsLightEffectFactoryResetStart(void);

void ldsLightColorAgingTestEffectBreathe(uint16_t count);

void ldsLightColorAgingFactoryTestEffectBreathe(uint16_t count);

void ldsLightEffectIdentifyStart(void);

void ldsLightEffectPowerOnStart(void);

void ldsLightEffectTouchlinkInitiatedStart(void);

void ldsLightEffectTouchlinkIdentify(uint16_t identify_time);

void ldsLightEffectTouchlinkInitiatedStop(void);

void ldsLightEffectInit(void);

void ldsLightEffectRedBlinkStart();

void ldsLightEffectIdentifyOneBlink();

void ldsLightEffectIdentifyBreathe();

void ldsLightEffectIdentifyOkay();

void ldsLightEffectIdentifyChannelChange();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LDS_LIGHT_EFFECT_H_
