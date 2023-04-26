// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Material.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/proto_mesh.hh>
typedef phoenix::proto_mesh PxMultiResolutionMesh;
typedef phoenix::sub_mesh PxMultiResolutionSubMesh;
#else
typedef struct PxInternal_MultiResolutionMesh PxMultiResolutionMesh;
typedef struct PxInternal_MultiResolutionSubMesh PxMultiResolutionSubMesh;
#endif

// TODO
PXC_API PxMultiResolutionMesh* pxMrmLoad(PxBuffer* buffer);
PXC_API PxMultiResolutionMesh* pxMrmLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMrmDestroy(PxMultiResolutionMesh* mrm);

PXC_API uint32_t pxMrmGetPositionCount(PxMultiResolutionMesh const* mrm);
PXC_API PxVec3 pxMrmGetPosition(PxMultiResolutionMesh const* mrm, uint32_t i);
PXC_API uint32_t pxMrmGetNormalCount(PxMultiResolutionMesh const* mrm);
PXC_API PxVec3 pxMrmGetNormal(PxMultiResolutionMesh const* mrm, uint32_t i);
PXC_API uint32_t pxMrmGetSubMeshCount(PxMultiResolutionMesh const* mrm);
PXC_API PxMultiResolutionSubMesh const* pxMrmGetSubMesh(PxMultiResolutionMesh const* mrm, uint32_t i);
PXC_API uint32_t pxMrmGetMaterialCount(PxMultiResolutionMesh const* mrm);
PXC_API PxMaterial const* pxMrmGetMaterial(PxMultiResolutionMesh const* mrm, uint32_t i);
PXC_API uint8_t pxMrmGetAlphaTest(PxMultiResolutionMesh const* mrm);
PXC_API PxAABB pxMrmGetBbox(PxMultiResolutionMesh const* mrm);
// TODO: obbox

PXC_API PxMaterial const* pxMrmSubMeshGetMaterial(PxMultiResolutionSubMesh const* sub);
PXC_API uint32_t pxMrmSubMeshGetTriangleCount(PxMultiResolutionSubMesh const* sub);
PXC_API void pxMrmSubMeshGetTriangle(PxMultiResolutionSubMesh const* sub, //
                                     uint32_t i,
                                     uint16_t* a,
                                     uint16_t* b,
                                     uint16_t* c);
PXC_API uint32_t pxMrmSubMeshGetWedgeCount(PxMultiResolutionSubMesh const* sub);
PXC_API void pxMrmSubMeshGetWedge(PxMultiResolutionSubMesh const* sub, //
                                  uint32_t,
                                  PxVec3* normal,
                                  PxVec2* texture,
                                  uint16_t* index);
PXC_API float const* pxMrmSubMeshGetColors(PxMultiResolutionSubMesh const* sub, uint32_t* length);
PXC_API uint16_t const* pxMrmSubMeshGetTrianglePlaneIndices(PxMultiResolutionSubMesh const* sub, uint32_t* length);
PXC_API uint32_t pxMrmSubMeshGetTrianglePlaneCount(PxMultiResolutionSubMesh const* sub);
PXC_API void pxMrmSubMeshGetTrianglePlane(PxMultiResolutionSubMesh const* sub, //
                                          uint32_t,
                                          float* distance,
                                          PxVec3* normal);
PXC_API uint32_t pxMrmSubMeshGetTriangleEdgeCount(PxMultiResolutionSubMesh const* sub);
PXC_API void pxMrmSubMeshGetTriangleEdge(PxMultiResolutionSubMesh const* sub, //
                                         uint32_t,
                                         uint16_t* a,
                                         uint16_t* b,
                                         uint16_t* c);
PXC_API uint32_t pxMrmSubMeshGetEdgeCount(PxMultiResolutionSubMesh const* sub);
PXC_API void pxMrmSubMeshGetEdge(PxMultiResolutionSubMesh const* sub, uint32_t, uint16_t* a, uint16_t* b);
PXC_API float const* pxMrmSubMeshGetEdgeScores(PxMultiResolutionSubMesh const* sub, uint32_t* length);
PXC_API uint16_t const* pxMrmSubMeshGetWedgeMap(PxMultiResolutionSubMesh const* sub, uint32_t* length);
