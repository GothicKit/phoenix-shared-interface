// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vfs.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/model_hierarchy.hh>
typedef phoenix::model_hierarchy PxModelHierarchy;
#else
typedef struct PxInternal_ModelHierarchy PxModelHierarchy;
#endif

PXC_API PxModelHierarchy* pxMdhLoad(PxBuffer* buffer);
PXC_API PxModelHierarchy* pxMdhLoadFromVfs(PxVfs const* vf, char const* name);
PXC_API void pxMdhDestroy(PxModelHierarchy* mdh);

PXC_API PxAABB pxMdhGetBbox(PxModelHierarchy const* mdh);
PXC_API PxAABB pxMdhGetCollisionBbox(PxModelHierarchy const* mdh);
PXC_API PxVec3 pxMdhGetRootTranslation(PxModelHierarchy const* mdh);
PXC_API uint32_t pxMdhGetChecksum(PxModelHierarchy const* mdh);
PXC_API uint32_t pxMdhGetNodeCount(PxModelHierarchy const* mdh);
PXC_API void
pxMdhGetNode(PxModelHierarchy const* mdh, uint32_t i, int16_t* parent, char const** name, PxMat4x4* transform);
