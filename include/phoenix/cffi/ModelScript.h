// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/model_script.hh>
typedef phoenix::model_script PxModelScript;
#else
typedef struct PxInternal_ModelScript PxModelScript;
#endif

typedef enum : uint8_t {
	af_none = 0,
	af_move = 1,
	af_rotate = 2,
	af_queue = 4,
	af_fly = 8,
	af_idle = 16,   
} PxAnimationFlags;

typedef enum : uint8_t {
	forward = 0,  ///< The animation samples are played from first to last.
	backward = 1, ///< The animation samples are played from last to first.
} PxAnimationDirection;


PXC_API PxModelScript* pxMdsLoad(PxBuffer* buffer);
PXC_API PxModelScript* pxMdsLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMdsDestroy(PxModelScript* mds);

PXC_API uint32_t pxMdsGetMeshCount(PxModelScript* mds);
PXC_API const char* pxMdsGetMesh(PxModelScript* mds, uint32_t i);
PXC_API uint32_t pxMdsGetDisabledAnimationsCount(PxModelScript* mds);
PXC_API const char* pxMdsGetDisabledAnimation(PxModelScript* mds, uint32_t i);

PXC_API uint32_t pxMdsGetModelTagCount(PxModelScript* mds);
PXC_API const char* pxMdsGetModelTagBone(PxModelScript* mds, uint32_t i);

PXC_API uint32_t pxMdsGetAnimationCombinationCount(PxModelScript* mds);
PXC_API const char* pxMdsGetAnimationCombinationName(PxModelScript* mds, uint32_t i);
PXC_API uint32_t pxMdsGetAnimationCombinationLayer(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationCombinationNext(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationCombinationBlendIn(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationCombinationBlendOut(PxModelScript* mds, uint32_t i);
PXC_API PxAnimationFlags pxMdsGetAnimationCombinationFlags(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationCombinationModel(PxModelScript* mds, uint32_t i);
PXC_API int32_t pxMdsGetAnimationCombinationLastFrame(PxModelScript* mds, uint32_t i);

PXC_API uint32_t pxMdsGetAnimationBlendingCount(PxModelScript* mds);
PXC_API const char* pxMdsGetAnimationBlendingName(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationBlendingNext(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationBlendingBlendIn(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationBlendingBlendOut(PxModelScript* mds, uint32_t i);

PXC_API uint32_t pxMdsGetAnimationAliasCount(PxModelScript* mds);
PXC_API const char* pxMdsGetAnimationAliasName(PxModelScript* mds, uint32_t i);
PXC_API uint32_t pxMdsGetAnimationAliasLayer(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationAliasNext(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationAliasBlendIn(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationAliasBlendOut(PxModelScript* mds, uint32_t i);
PXC_API PxAnimationFlags pxMdsGetAnimationAliasFlags(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationAliasAlias(PxModelScript* mds, uint32_t i);
PXC_API PxAnimationDirection pxMdsGetAnimationAliasDirection(PxModelScript* mds, uint32_t i);

// TODO - Implement
// mds::skeleton skeleton {};
// std::vector<mds::animation> animations {};
