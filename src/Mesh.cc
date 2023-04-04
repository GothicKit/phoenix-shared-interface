// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"
#include "phoenix/cffi/Api.h"

#include <phoenix/mesh.hh>
#include <phoenix/cffi/Mesh.h>

PxMesh* pxMshLoad(PxBuffer* buffer) {
	try {
		auto* buf = RC(px::buffer, buffer);
		auto mat = px::mesh::parse(buf->duplicate());
		return RC(PxMesh, new phoenix::mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxMesh* pxMshLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxMesh* result = pxMshLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMshDestroy(PxMesh* msh) {
	delete RC(px::mesh, msh);
}

char const* pxMshGetName(PxMesh const* msh) {
	return RCC(px::mesh, msh)->name.c_str();
}

PxAABB pxMshGetBbox(PxMesh const* msh) {
	auto& bb = RCC(px::mesh, msh)->bbox;
	return {
		{bb.min.x, bb.min.y, bb.min.z},
		{bb.max.x, bb.max.y, bb.max.z},
	};
}

uint32_t PxMshGetMaterialCount(PxMesh const* msh) {
	return (uint32_t) RCC(px::mesh, msh)->materials.size();
}

PxMaterial const* pxMshGetMaterial(PxMesh const* msh, uint32_t i) {
	return RCC(PxMaterial, &RCC(px::mesh, msh)->materials[i]);
}

uint32_t pxMshGetVertexCount(PxMesh const* msh) {
	return (uint32_t)RCC(px::mesh, msh)->vertices.size();
}

PxVec3 pxMshGetVertex(PxMesh const* msh, uint32_t i) {
	auto& vt = RCC(px::mesh, msh)->vertices[i];
	return {vt.x, vt.y, vt.z};
}

uint32_t pxMshGetFeatureCount(PxMesh const* msh) {
	return (uint32_t) RCC(px::mesh, msh)->features.size();
}

void pxMshGetFeature(PxMesh const* msh, uint32_t i, PxVec2* texture, uint32_t* light, PxVec3* normal) {
	auto& ft = RCC(px::mesh, msh)->features[i];

	texture->x = ft.texture.x;
	texture->y = ft.texture.y;
	*light = ft.light;
	normal->x = ft.normal.x;
	normal->y = ft.normal.y;
	normal->z = ft.normal.z;
}

uint32_t const* pxMshGetPolygonMaterialIndices(PxMesh const* msh, uint32_t* length) {
	auto& polys = RCC(px::mesh, msh)->polygons;
	*length = (uint32_t) polys.material_indices.size();
	return polys.material_indices.data();
}

uint32_t const* pxMshGetPolygonFeatureIndices(PxMesh const* msh, uint32_t* length) {
	auto& polys = RCC(px::mesh, msh)->polygons;
	*length = (uint32_t) polys.feature_indices.size();
	return polys.feature_indices.data();
}

uint32_t const* pxMshGetPolygonVertexIndices(PxMesh const* msh, uint32_t* length) {
	auto& polys = RCC(px::mesh, msh)->polygons;
	*length = (uint32_t) polys.vertex_indices.size();
	return polys.vertex_indices.data();
}
