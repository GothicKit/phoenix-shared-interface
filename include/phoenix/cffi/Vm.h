// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vfs.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/vm.hh>
typedef struct PxInternal_Vm PxVm;
typedef phoenix::instance PxVmInstance;
#else
typedef struct PxInternal_Vm PxVm;
typedef struct PxInternal_VmInstance PxVmInstance;
#endif

typedef enum {
	PxVm_InstanceTypeNpc = 1,
	PxVm_InstanceTypeItem = 2,
	PxVm_InstanceTypeSfx = 3,
	PxVm_InstanceTypeMusic = 4,
	PxVm_InstanceTypeMenu = 5,
	PxVm_InstanceTypeMenuItem = 6,
	PxVm_InstanceTypePfx = 7
} PxVmInstanceType;

typedef void (*PxVmExternalCallback)(PxVm* vm);
typedef void (*PxVmExternalDefaultCallback)(PxVm* vm, char const* name);
typedef void (*PxVmEnumerateInstancesCallback)(char const* name);

PXC_API PxVm* pxVmLoad(PxBuffer* buffer);
PXC_API PxVm* pxVmLoadFromVfs(PxVfs const* vfs, char const* name);
PXC_API void pxVmDestroy(PxVm* vm);

PXC_API PxVmInstance* pxVmStackPopInstance(PxVm* vm);
PXC_API char const* pxVmStackPopString(PxVm* vm);
PXC_API float pxVmStackPopFloat(PxVm* vm);
PXC_API int32_t pxVmStackPopInt(PxVm* vm);

PXC_API void pxVmStackPushInstance(PxVm* vm, PxVmInstance* instance);
PXC_API void pxVmStackPushString(PxVm* vm, char const* string);
PXC_API void pxVmStackPushFloat(PxVm* vm, float f);
PXC_API void pxVmStackPushInt(PxVm* vm, int i);

PXC_API void pxVmRegisterExternal(PxVm* vm, char const* name, PxVmExternalCallback cb);
PXC_API void pxVmRegisterExternalDefault(PxVm* vm, PxVmExternalDefaultCallback cb);

PXC_API PxVmInstance* pxVmGetGlobalSelf(PxVm* vm);
PXC_API PxVmInstance* pxVmGetGlobalOther(PxVm* vm);
PXC_API PxVmInstance* pxVmGetGlobalVictim(PxVm* vm);
PXC_API PxVmInstance* pxVmGetGlobalHero(PxVm* vm);
PXC_API PxVmInstance* pxVmGetGlobalItem(PxVm* vm);

PXC_API PxVmInstance* pxVmSetGlobalSelf(PxVm* vm, PxVmInstance* instance);
PXC_API PxVmInstance* pxVmSetGlobalOther(PxVm* vm, PxVmInstance* instance);
PXC_API PxVmInstance* pxVmSetGlobalVictim(PxVm* vm, PxVmInstance* instance);
PXC_API PxVmInstance* pxVmSetGlobalHero(PxVm* vm, PxVmInstance* instance);
PXC_API PxVmInstance* pxVmSetGlobalItem(PxVm* vm, PxVmInstance* instance);

PXC_API PxBool pxVmCallFunction(PxVm* vm, char const* func, ...);
PXC_API PxBool pxVmCallFunctionByIndex(PxVm* vm, uint32_t index, char const* args, ...);

PXC_API PxVmInstance* pxVmInstanceAllocateByIndex(PxVm* vm, uint32_t index, PxVmInstanceType type);
PXC_API PxVmInstance* pxVmInstanceAllocateByName(PxVm* vm, char const* name, PxVmInstanceType type);
PXC_API PxVmInstance*
pxVmInstanceInitializeByIndex(PxVm* vm, uint32_t index, PxVmInstanceType type, PxVmInstance* existing);
PXC_API PxVmInstance*
pxVmInstanceInitializeByName(PxVm* vm, char const* name, PxVmInstanceType type, PxVmInstance* existing);
PXC_API uint32_t pxVmInstanceGetSymbolIndex(PxVmInstance const* instance);

PXC_API void pxVmPrintStackTrace(PxVm const* vm);
PXC_API void pxVmEnumerateInstancesByClassName(PxVm* vm, char const* name, PxVmEnumerateInstancesCallback cb);

// C_Npc
PXC_API int32_t pxVmInstanceNpcGetId(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceNpcGetNameLength(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceNpcGetName(PxVmInstance const* instance, uint32_t i);
PXC_API char const* pxVmInstanceNpcGetSlot(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceNpcGetNpcType(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceNpcGetFlags(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceNpcGetAttributeLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetAttribute(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceNpcGetProtectionLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetProtection(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceNpcGetDamageLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetDamage(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceNpcGetDamageType(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetGuild(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetLevel(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceNpcGetMissionLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetMission(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceNpcGetFightTactic(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetWeapon(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetVoice(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetVoicePitch(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetBodyMass(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetRoutine(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetStartAiState(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceNpcGetSpawnPoint(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetSpawnDelay(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetSenses(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetSensesRange(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceNpcGetAiLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetAiVar(PxVmInstance const* instance, uint32_t i);
PXC_API char const* pxVmInstanceNpcGetWP(PxVmInstance const* instance);
PXC_API void pxVmInstanceNpcSetWP(PxVmInstance* instance, char const* wpName);
PXC_API int32_t pxVmInstanceNpcGetExp(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetExpNext(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceNpcGetLp(PxVmInstance const* instance);

// C_Item
PXC_API int32_t pxVmInstanceItemGetId(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetName(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetNameId(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetHp(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetHpMax(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetMainFlag(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetFlags(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetWeight(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetValue(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetDamageType(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetDamageTotal(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetDamageLength();
PXC_API int32_t pxVmInstanceItemGetDamage(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceItemGetWear(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetProtectionLength();
PXC_API int32_t pxVmInstanceItemGetProtection(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceItemGetNutrition(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetCondAtrLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetCondAtr(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceItemGetCondValueLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetCondValue(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceItemGetChangeAtrLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetChangeAtr(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceItemGetChangeValueLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetChangeValue(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceItemGetMagic(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetOnEquip(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetOnUnequip(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetOnStateLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetOnState(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceItemGetOwner(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetOwnerGuild(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetDisguiseGuild(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetVisual(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetVisualChange(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetEffect(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetVisualSkin(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetSchemeName(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetMaterial(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetMunition(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetSpell(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetRange(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetMagCircle(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetDescription(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetTextLength(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetText(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceItemGetCountLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetCount(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceItemGetInvZbias(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetInvRotX(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetInvRotY(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetInvRotZ(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetInvAnimate(PxVmInstance const* instance);

// C_MENU
PXC_API char const* pxVmInstanceMenuGetBackPic(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuGetBackWorld(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetPosX(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetPosY(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetDimX(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetDimY(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetAlpha(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuGetMusicTheme(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetEventTimerMsec(PxVmInstance const* instance);
PXC_API uint8_t pxVmInstanceMenuGetItemsLength(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuGetItems(PxVmInstance const* instance, uint8_t i);
PXC_API uint32_t pxVmInstanceMenuGetFlags(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetDefaultOutgame(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuGetDefaultIngame(PxVmInstance const* instance);

// C_MENU_ITEM
PXC_API char const* pxVmInstanceMenuItemGetFontname(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceMenuItemGetTextLength(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuItemGetText(PxVmInstance const* instance, uint32_t i);
PXC_API char const* pxVmInstanceMenuItemGetBackpic(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuItemGetAlphamode(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetAlpha(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceMenuItemGetType(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceMenuItemGetOnSelActionLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetOnSelAction(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceMenuItemGetOnSelActionSLength(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuItemGetOnSelActionS(PxVmInstance const* instance, uint32_t i);
PXC_API char const* pxVmInstanceMenuItemGetOnChgSetOption(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuItemGetOnChgSetOptionSection(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceMenuItemGetOnEventActionLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetOnEventAction(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceMenuItemGetPosX(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetPosY(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetDimX(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetDimY(PxVmInstance const* instance);
PXC_API float pxVmInstanceMenuItemGetSizeStartScale(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceMenuItemGetFlags(PxVmInstance const* instance);
PXC_API float pxVmInstanceMenuItemGetOpenDelayTime(PxVmInstance const* instance);
PXC_API float pxVmInstanceMenuItemGetOpenDuration(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceMenuItemGetUserFloatLength(PxVmInstance const* instance);
PXC_API float pxVmInstanceMenuItemGetUserFloat(PxVmInstance const* instance, uint32_t i);
PXC_API uint32_t pxVmInstanceMenuItemGetUserStringLength(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuItemGetUserString(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceMenuItemGetFrameSizex(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetFrameSizey(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuItemGetHideIfOptionSectionSet(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceMenuItemGetHideIfOptionSet(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMenuItemGetHideOnValue(PxVmInstance const* instance);

// C_SFX
PXC_API char const* pxVmInstanceSfxGetFile(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceSfxGetPitchOff(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceSfxGetPitchVar(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceSfxGetVol(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceSfxGetLoop(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceSfxGetLoopStartOffset(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceSfxGetLoopEndOffset(PxVmInstance const* instance);
PXC_API float pxVmInstanceSfxGetReverbLevel(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceSfxGetPfxName(PxVmInstance const* instance);

// C_MUSIC_THEME
PXC_API char const* pxVmInstanceMusicGetFile(PxVmInstance const* instance);
PXC_API float pxVmInstanceMusicGetVol(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMusicGetLoop(PxVmInstance const* instance);
PXC_API float pxVmInstanceMusicGetReverbMix(PxVmInstance const* instance);
PXC_API float pxVmInstanceMusicGetReverbTime(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMusicGetTransitionType(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceMusicGetTransitionSubType(PxVmInstance const* instance);

// C_PARTICLEFX
PXC_API float pxVmInstancePfxGetPpsValue(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetPpsScaleKeys(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetPpsIsLooping(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetPpsIsSmooth(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetPpsFps(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetPpsCrateEm(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetPpsCreateEmDelay(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetShpType(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetShpFor(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetShpOffsetVec(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetShpDistribType(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetShpDistribWalkSpeed(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetShpIsVolume(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetShpDim(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetShpMesh(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetShpMeshRender(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetShpScaleKeys(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetShpScaleIsLooping(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetShpScaleIsSmooth(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetShpScaleFps(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetDirMode(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetDirFor(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetDirModeTargetFor(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetDirModeTargetPos(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetDirAngleHead(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetDirAngleHeadVar(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetDirAngleElev(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetDirAngleElevVar(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetVelAvg(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetVelVar(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetLspPartAvg(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetLspPartVar(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetFlyGravity(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetFlyCollDet(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetVisName(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetVisOrientation(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetVisTexIsQuadPoly(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetVisTexAniFps(PxVmInstance const* instance);
PXC_API PxBool pxVmInstancePfxGetVisTexAniIsLooping(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetVisTexColorStart(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetVisTexColorEnd(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetVisSizeStart(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetVisSizeEndScale(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetVisAlphaFunc(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetVisAlphaStart(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetVisAlphaEnd(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetTrlFadeSpeed(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetTrlTexture(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetTrlWidth(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetMrkFadeSpeed(PxVmInstance const* instance);
PXC_API char const* pxVmInstancePfxGetMrkTexture(PxVmInstance const* instance);
PXC_API float pxVmInstancePfxGetMrkSize(PxVmInstance const* instance);
