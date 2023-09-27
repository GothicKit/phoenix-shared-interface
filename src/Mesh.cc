// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Api.h>
#include <phoenix/cffi/Mesh.h>
#include <phoenix/mesh.hh>

PxMesh* pxMshLoad(PxBuffer* buffer) {
	try {
		auto mat = px::mesh::parse(buffer->duplicate());
		return new phoenix::mesh(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxMesh: ", e.what());
		return nullptr;
	}
}

PxMesh* pxMshLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetNodeByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vfs entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
	PxMesh* result = pxMshLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMshDestroy(PxMesh* msh) {
	delete msh;
}

char const* pxMshGetName(PxMesh const* msh) {
	return msh->name.c_str();
}

PxAABB pxMshGetBbox(PxMesh const* msh) {
	auto& bb = msh->bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

uint32_t pxMshGetMaterialCount(PxMesh const* msh) {
	return (uint32_t) msh->materials.size();
}

PxMaterial const* pxMshGetMaterial(PxMesh const* msh, uint32_t i) {
	return &msh->materials[i];
}

uint32_t pxMshGetVertexCount(PxMesh const* msh) {
	return (uint32_t) msh->vertices.size();
}

PxVec3 pxMshGetVertex(PxMesh const* msh, uint32_t i) {
	auto& vt = msh->vertices[i];
	return {vt.x, vt.y, vt.z};
}

uint32_t pxMshGetFeatureCount(PxMesh const* msh) {
	return (uint32_t) msh->features.size();
}

void pxMshGetFeature(PxMesh const* msh, uint32_t i, PxVec2* texture, uint32_t* light, PxVec3* normal) {
	auto& ft = msh->features[i];

	texture->x = ft.texture.x;
	texture->y = ft.texture.y;
	*light = ft.light;
	normal->x = ft.normal.x;
	normal->y = ft.normal.y;
	normal->z = ft.normal.z;
}
uint32_t pxMshGetLightMapCount(PxMesh const* msh) {
	return (uint32_t) msh->lightmaps.size();
}
void pxMshGetLightMap(PxMesh const* msh, uint32_t i, PxTexture const** image, PxVec3* origin) {
	auto& lm = msh->lightmaps[i];

	// PxVec3 normal[] = {
	//     {lm.normals[0].x, lm.normals[0].y, lm.normals[0].z},
	//     {lm.normals[1].x, lm.normals[1].y, lm.normals[1].z},
	// };

	*image = lm.image.get();
	// *normals = normal;
	*origin = PxVec3 {lm.origin.x, lm.origin.y, lm.origin.z};
}

uint32_t const* pxMshGetPolygonMaterialIndices(PxMesh const* msh, uint32_t* length) {
	auto& polys = msh->polygons;
	*length = (uint32_t) polys.material_indices.size();
	return polys.material_indices.data();
}

uint32_t const* pxMshGetPolygonFeatureIndices(PxMesh const* msh, uint32_t* length) {
	auto& polys = msh->polygons;
	*length = (uint32_t) polys.feature_indices.size();
	return polys.feature_indices.data();
}

uint32_t const* pxMshGetPolygonVertexIndices(PxMesh const* msh, uint32_t* length) {
	auto& polys = msh->polygons;
	*length = (uint32_t) polys.vertex_indices.size();
	return polys.vertex_indices.data();
}

int32_t const* pxMshGetPolygonLightMapIndices(PxMesh const* msh, uint32_t* length) {
	auto& polys = msh->polygons;
	*length = (uint32_t) polys.lightmap_indices.size();
	return polys.lightmap_indices.data();
}

uint32_t pxMshGetPolygonFlagCount(PxMesh const* msh) {
	return (uint32_t) msh->polygons.flags.size();
}

uint8_t pxMshGetPolygonFlagGetIsPortal(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].is_portal;
}

uint8_t pxMshGetPolygonFlagGetIsOccluder(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].is_occluder;
}

uint8_t pxMshGetPolygonFlagGetIsSector(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].is_sector;
}

uint8_t pxMshGetPolygonFlagGetShouldRelight(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].should_relight;
}

uint8_t pxMshGetPolygonFlagGetIsOutdoor(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].is_outdoor;
}

uint8_t pxMshGetPolygonFlagGetIsGhostGccluder(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].is_ghost_occluder;
}

uint8_t pxMshGetPolygonFlagGetIsDynamicallyLit(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].is_dynamically_lit;
}

int16_t pxMshGetPolygonFlagGetSector_Index(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].sector_index;
}

uint8_t pxMshGetPolygonFlagGetIsLod(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].is_lod;
}

uint8_t pxMshGetPolygonFlagGetNormalAxis(PxMesh const* msh, uint32_t i) {
	return msh->polygons.flags[i].normal_axis;
}
