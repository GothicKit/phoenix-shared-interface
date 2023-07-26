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
typedef phoenix::symbol PxVmSymbol;
typedef phoenix::instance PxVmInstance;
#else
typedef struct PxInternal_Vm PxVm;
typedef struct PxInternal_VmSymbol PxVmSymbol;
typedef struct PxInternal_VmInstance PxVmInstance;
#endif

typedef enum {
	PxVm_InstanceTypeNpc = 1,
	PxVm_InstanceTypeItem = 2,
	PxVm_InstanceTypeSfx = 3,
	PxVm_InstanceTypeMusic = 4
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

PXC_API PxVmSymbol* pxVmGetSymbolByIndex(PxVm* vm, uint32_t index);
PXC_API PxVmSymbol* pxVmGetSymbolByName(PxVm* vm, char const* name);
PXC_API uint32_t pxVmSymbolGetId(PxVmSymbol* symbol);
PXC_API char const* pxVmSymbolGetName(PxVmSymbol* symbol);
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
PXC_API int32_t pxVmInstanceNpcGetRoutine(PxVmInstance const* instance);

// C_Item
PXC_API int32_t pxVmInstanceItemGetId(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetName(PxVmInstance const* instance);
PXC_API char const* pxVmInstanceItemGetNameId(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetHp(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetHpMax(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetMainFlag(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetWeight(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetValue(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetDamageType(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetDamageTotal(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetDamageLength(PxVmInstance const* instance);
PXC_API int32_t pxVmInstanceItemGetDamage(PxVmInstance const* instance, uint32_t i);
PXC_API int32_t pxVmInstanceItemGetWear(PxVmInstance const* instance);
PXC_API uint32_t pxVmInstanceItemGetProtectionLength(PxVmInstance const* instance);
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
