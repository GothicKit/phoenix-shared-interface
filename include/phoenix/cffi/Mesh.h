// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Material.h"

#include <stdint.h>

typedef struct PxInternal_Mesh PxMesh;

// TODO: Lightmaps
PXC_API PxMesh* px_msh_parse(PxBuffer* buffer);
PXC_API char const* px_msh_name(PxMesh const* msh);
PXC_API PxAABB px_msh_bbox(PxMesh const* msh);
PXC_API uint32_t px_mesh_material_count(PxMesh const* msh);
PXC_API PxMaterial const* px_mesh_material(PxMesh const* msh, uint32_t i);
PXC_API uint32_t px_mesh_vertex_count(PxMesh const* msh);
PXC_API PxVec3 px_mesh_vertex(PxMesh const* msh, uint32_t i);
PXC_API uint32_t px_mesh_feature_count(PxMesh const* msh);
PXC_API void px_mesh_feature(PxMesh const* msh, uint32_t i, PxVec2* texture, uint32_t* light, PxVec3* normal);
PXC_API uint32_t const* px_mesh_polygon_material_indices(PxMesh const* msh, uint32_t* length);
PXC_API uint32_t const* px_mesh_polygon_feature_indices(PxMesh const* msh, uint32_t* length);
PXC_API uint32_t const* px_mesh_polygon_vertex_indices(PxMesh const* msh, uint32_t* length);
PXC_API void px_msh_destroy(PxMesh* msh);

