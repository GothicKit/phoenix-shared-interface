// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "MultiResolutionMesh.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/morph_mesh.hh>
typedef phoenix::morph_mesh PxMorphMesh;
typedef phoenix::morph_animation PxMorphMeshAnimation;
#else
typedef struct PxInternal_MorphMesh PxMorphMesh;
typedef struct PxInternal_MorphMeshAnimation PxMorphMeshAnimation;
#endif

// TODO
PXC_API PxMorphMesh* pxMmbLoad(PxBuffer* buffer);
PXC_API PxMorphMesh* pxMmbLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMmbDestroy(PxMorphMesh* mmb);

PXC_API char const* pxMmbGetName(PxMorphMesh const* mmb);
PXC_API PxMultiResolutionMesh const* pxMmbGetMesh(PxMorphMesh const* mmb);
PXC_API uint32_t pxMmbGetMorphPositionCount(PxMorphMesh const* mmb);
PXC_API PxVec3 pxMmbGetMorphPosition(PxMorphMesh const* mmb, uint32_t i);
PXC_API uint32_t pxMmbGetAnimationCount(PxMorphMesh const* mmb);
PXC_API PxMorphMeshAnimation const* pxMmbGetAnimation(PxMorphMesh const* mmb, uint32_t i);
// TODO: Sources

PXC_API char const* pxMmbAniGetName(PxMorphMeshAnimation const* ani);
PXC_API int32_t pxMmbAniGetLayer(PxMorphMeshAnimation const* ani);
PXC_API float pxMmbAniGetBlendIn(PxMorphMeshAnimation const* ani);
PXC_API float pxMmbAniGetBlendOut(PxMorphMeshAnimation const* ani);
PXC_API float pxMmbAniGetDuration(PxMorphMeshAnimation const* ani);
PXC_API float pxMmbAniGetSpeed(PxMorphMeshAnimation const* ani);
PXC_API uint8_t pxMmbAniGetFlags(PxMorphMeshAnimation const* ani);
PXC_API uint32_t pxMmbAniGetFrameCount(PxMorphMeshAnimation const* ani);
PXC_API uint32_t const* pxMmbAniGetVertices(PxMorphMeshAnimation const* ani, uint32_t* length);
PXC_API uint32_t pxMmbAniGetSampleCount(PxMorphMeshAnimation const* ani);
PXC_API PxVec3 pxMmbAniGetSample(PxMorphMeshAnimation const* ani, uint32_t i);
