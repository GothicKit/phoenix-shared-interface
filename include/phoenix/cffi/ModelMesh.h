// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"
#include "MultiResolutionMesh.h"

#include <stdint.h>

typedef struct PxInternal_ModelMesh PxModelMesh;
typedef struct PxInternal_SoftSkinMesh PxSoftSkinMesh;

PXC_API PxModelMesh* pxMdmLoad(PxBuffer* buffer);
PXC_API PxModelMesh* pxMdmLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMdmDestroy(PxModelMesh* mdm);

PXC_API uint32_t pxMdmGetMeshCount(PxModelMesh const* mdm);
PXC_API PxSoftSkinMesh const* pxMdmGetMesh(PxModelMesh const* mdm, uint32_t i);
PXC_API PxMultiResolutionMesh const* pxMdmGetAttachment(PxModelMesh const* mdm, char const* name);
PXC_API uint32_t pxMdmGetChecksum(PxModelMesh const* mdm);

PXC_API PxMultiResolutionMesh const* pxSsmGetMesh(PxSoftSkinMesh const* ssm);
// TODO: bboxes
PXC_API uint32_t pxSsmGetWedgeNormalsCount(PxSoftSkinMesh const* ssm);
PXC_API void pxSsmGetWedgeNormal(PxSoftSkinMesh const* ssm, uint32_t i, PxVec3* normal, uint32_t* index);
PXC_API uint32_t pxSsmGetNodeCount(PxSoftSkinMesh const* ssm);
PXC_API uint32_t pxSsmGetNodeWeightCount(PxSoftSkinMesh const* ssm, uint32_t node);
PXC_API void pxSsmGetNodeWeight(PxSoftSkinMesh const* ssm, uint32_t node, uint32_t i, float* weight, PxVec3* position, uint8_t* index);
PXC_API int32_t const* pxSsmGetNodes(PxSoftSkinMesh const* ssm, uint32_t* length);