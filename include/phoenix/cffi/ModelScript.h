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
PXC_API void pxMdsGetModelTag(PxModelScript* mds, uint32_t i, const char* bone);

PXC_API uint32_t pxMdsGetAnimationCombinationCount(PxModelScript* mds);
PXC_API void pxMdsGetAnimationCombination(PxModelScript* mds, uint32_t i,
	const char* name,
    uint32_t* layer,
    const char* next,
	float* blend_in,
	float* blend_out,
	PxAnimationFlags* flags,
	const char* model,
	int32_t* last_frame);

PXC_API uint32_t pxMdsGetAnimationBlendingCount(PxModelScript* mds);
PXC_API void pxMdsGetAnimationBlending(PxModelScript* mds, uint32_t i,
	const char* name,
	const char* next,
	float* blend_in,
	float* blend_out);

PXC_API uint32_t pxMdsGetAnimationAliasCount(PxModelScript* mds);
PXC_API void pxMdsGetAnimationAlias(PxModelScript* mds, uint32_t i,
			const char* name,
			uint32_t* layer,
			const char* next,
			float* blend_in,
			float* blend_out,
			PxAnimationFlags* flags,
			const char* alias,
			PxAnimationDirection* direction);

// TODO - Implement
// mds::skeleton skeleton {};
// std::vector<mds::animation> animations {};
