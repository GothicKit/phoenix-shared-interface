// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/MultiResolutionMesh.h>
#include <phoenix/proto_mesh.hh>

PxMultiResolutionMesh* pxMrmLoad(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::proto_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxMultiResolutionMesh*>(new phoenix::proto_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxMultiResolutionMesh* pxMrmLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxMultiResolutionMesh* result = pxMrmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMrmDestroy(PxMultiResolutionMesh* mrm) {
	delete reinterpret_cast<phoenix::proto_mesh*>(mrm);
}

uint32_t pxMrmGetPositionCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) RCC(px::proto_mesh, mrm)->positions.size();
}

PxVec3 pxMrmGetPosition(PxMultiResolutionMesh const* mrm, uint32_t i) {
	auto& pos = RCC(px::proto_mesh, mrm)->positions[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}

uint32_t pxMrmGetNormalCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) RCC(px::proto_mesh, mrm)->normals.size();
}

PxVec3 pxMrmGetNormal(PxMultiResolutionMesh const* mrm, uint32_t i) {
	auto& pos = RCC(px::proto_mesh, mrm)->normals[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}

uint32_t pxMrmGetSubMeshCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) RCC(px::proto_mesh, mrm)->sub_meshes.size();
}

PxMultiResolutionSubMesh const* pxMrmGetSubMesh(PxMultiResolutionMesh const* mrm, uint32_t i) {
	return RCC(PxMultiResolutionSubMesh, &RCC(px::proto_mesh, mrm)->sub_meshes[i]);
}

uint32_t pxMrmGetMaterialCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) RCC(px::proto_mesh, mrm)->materials.size();
}

PxMaterial const* pxMrmGetMaterial(PxMultiResolutionMesh const* mrm, uint32_t i) {
	return RCC(PxMaterial, &RCC(px::proto_mesh, mrm)->materials[i]);
}

uint8_t pxMrmGetAlphaTest(PxMultiResolutionMesh const* mrm) {
	return RCC(px::proto_mesh, mrm)->alpha_test;
}

PxAABB pxMrmGetBbox(PxMultiResolutionMesh const* mrm) {
	auto& bbox = RCC(px::proto_mesh, mrm)->bbox;
	return PxAABB {
	    PxVec3 {bbox.min.x, bbox.min.y, bbox.min.z},
	    PxVec3 {bbox.max.x, bbox.max.y, bbox.max.z},
	};
}

PxMaterial const* pxMrmSubMeshGetMaterial(PxMultiResolutionSubMesh const* sub) {
	return RCC(PxMaterial, &RCC(px::sub_mesh, sub)->mat);
}

uint32_t pxMrmSubMeshGetTriangleCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) RCC(px::sub_mesh, sub)->triangles.size();
}

void pxMrmSubMeshGetTriangle(PxMultiResolutionSubMesh const* sub, uint32_t i, uint16_t* a, uint16_t* b, uint16_t* c) {
	auto& tri = RCC(px::sub_mesh, sub)->triangles[i];
	*a = tri.wedges[0];
	*b = tri.wedges[1];
	*c = tri.wedges[2];
}

uint32_t pxMrmSubMeshGetWedgeCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) RCC(px::sub_mesh, sub)->wedges.size();
}

void pxMrmSubMeshGetWedge(PxMultiResolutionSubMesh const* sub,
                          uint32_t i,
                          PxVec3* normal,
                          PxVec2* texture,
                          uint16_t* index) {
	auto& tri = RCC(px::sub_mesh, sub)->wedges[i];
	normal->x = tri.normal.x;
	normal->y = tri.normal.y;
	normal->z = tri.normal.z;
	texture->x = tri.texture.x;
	texture->y = tri.texture.y;
	texture->x = tri.texture.x;
	*index = tri.index;
}

float const* pxMrmSubMeshGetColors(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& clrs = RCC(px::sub_mesh, sub)->colors;
	*length = (uint32_t) clrs.size();
	return clrs.data();
}

uint16_t const* pxMrmSubMeshGetTrianglePlaneIndices(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& clrs = RCC(px::sub_mesh, sub)->triangle_plane_indices;
	*length = (uint32_t) clrs.size();
	return clrs.data();
}

uint32_t pxMrmSubMeshGetTrianglePlaneCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) RCC(px::sub_mesh, sub)->triangle_planes.size();
}

void pxMrmSubMeshGetTrianglePlane(PxMultiResolutionSubMesh const* sub, uint32_t i, float* distance, PxVec3* normal) {
	auto& tri = RCC(px::sub_mesh, sub)->triangle_planes[i];
	*distance = tri.distance;
	normal->x = tri.normal.x;
	normal->y = tri.normal.y;
	normal->z = tri.normal.z;
}

uint32_t pxMrmSubMeshGetTriangleEdgeCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) RCC(px::sub_mesh, sub)->triangle_edges.size();
}

void pxMrmSubMeshGetTriangleEdge(PxMultiResolutionSubMesh const* sub,
                                 uint32_t i,
                                 uint16_t* a,
                                 uint16_t* b,
                                 uint16_t* c) {
	auto& tri = RCC(px::sub_mesh, sub)->triangle_edges[i];
	*a = tri.edges[0];
	*b = tri.edges[1];
	*c = tri.edges[2];
}

uint32_t pxMrmSubMeshGetEdgeCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) RCC(px::sub_mesh, sub)->edges.size();
}

void pxMrmSubMeshGetEdge(PxMultiResolutionSubMesh const* sub, uint32_t i, uint16_t* a, uint16_t* b) {
	auto& tri = RCC(px::sub_mesh, sub)->edges[i];
	*a = tri.edges[0];
	*b = tri.edges[1];
}

float const* pxMrmSubMeshGetEdgeScores(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& scrs = RCC(px::sub_mesh, sub)->edge_scores;
	*length = (uint32_t) scrs.size();
	return scrs.data();
}

uint16_t const* pxMrmSubMeshGetWedgeMap(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& scrs = RCC(px::sub_mesh, sub)->wedge_map;
	*length = (uint32_t) scrs.size();
	return scrs.data();
}
