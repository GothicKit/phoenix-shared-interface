// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vfs.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/animation.hh>
typedef phoenix::animation PxModelAnimation;
#else
typedef struct PxInternal_ModelAnimation PxModelAnimation;
#endif

PXC_API PxModelAnimation* pxManLoad(PxBuffer* buffer);
PXC_API PxModelAnimation* pxManLoadFromVfs(PxVfs const* vfs, char const* name);
PXC_API void pxManDestroy(PxModelAnimation* ani);

PXC_API char const* pxManGetName(PxModelAnimation const* man);
PXC_API char const* pxManGetNext(PxModelAnimation const* man);
PXC_API uint32_t pxManGetLayer(PxModelAnimation const* man);
PXC_API uint32_t pxManGetFrameCount(PxModelAnimation const* man);
PXC_API uint32_t pxManGetNodeCount(PxModelAnimation const* man);
PXC_API float pxManGetFps(PxModelAnimation const* man);
PXC_API PxAABB pxManGetBbox(PxModelAnimation const* man);
PXC_API uint32_t pxManGetChecksum(PxModelAnimation const* man);
PXC_API uint32_t pxManGetSampleCount(PxModelAnimation const* man);
PXC_API void pxManGetSample(PxModelAnimation const* man, uint32_t i, PxVec3* position, PxQuat* rotation);
PXC_API uint32_t const* pxManGetNodeIndices(PxModelAnimation const* man, uint32_t* length);
