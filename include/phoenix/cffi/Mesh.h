// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Material.h"
#include "Vfs.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/mesh.hh>
typedef phoenix::mesh PxMesh;
#else
typedef struct PxInternal_Mesh PxMesh;
#endif

typedef struct {
	std::uint8_t is_portal;
	std::uint8_t is_occluder;
	std::uint8_t is_sector;
	std::uint8_t should_relight;
	std::uint8_t is_outdoor;
	std::uint8_t is_ghost_occluder;
	std::uint8_t is_dynamically_lit;
	std::int16_t sector_index;

	uint8_t is_lod;
	uint8_t normal_axis;
} PxPolygonFlags;

// TODO: Lightmaps
PXC_API PxMesh* pxMshLoad(PxBuffer* buffer);
PXC_API PxMesh* pxMshLoadFromVfs(PxVfs const* vfs, char const* name);
PXC_API void pxMshDestroy(PxMesh* msh);

PXC_API char const* pxMshGetName(PxMesh const* msh);
PXC_API PxAABB pxMshGetBbox(PxMesh const* msh);
PXC_API uint32_t pxMshGetMaterialCount(PxMesh const* msh);
PXC_API PxMaterial const* pxMshGetMaterial(PxMesh const* msh, uint32_t i);
PXC_API uint32_t pxMshGetVertexCount(PxMesh const* msh);
PXC_API PxVec3 pxMshGetVertex(PxMesh const* msh, uint32_t i);
PXC_API uint32_t pxMshGetFeatureCount(PxMesh const* msh);
PXC_API void pxMshGetFeature(PxMesh const* msh, uint32_t i, PxVec2* texture, uint32_t* light, PxVec3* normal);
PXC_API uint32_t const* pxMshGetPolygonMaterialIndices(PxMesh const* msh, uint32_t* length);
PXC_API uint32_t const* pxMshGetPolygonFeatureIndices(PxMesh const* msh, uint32_t* length);
PXC_API uint32_t const* pxMshGetPolygonVertexIndices(PxMesh const* msh, uint32_t* length);

PXC_API uint32_t pxMshGetPolygonCount(PxMesh const* msh);
PXC_API void pxMshGetPolygon(PxMesh const* msh,
                             uint32_t idx,
                             uint32_t* materialIndex,
                             int32_t* lightmapIndex,
                             PxPolygonFlags* flags,
                             uint32_t const** vertexIndices,
                             uint32_t const** featureIndices,
                             uint32_t* vertexCount);
