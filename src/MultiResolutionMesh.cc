// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/MultiResolutionMesh.h>
#include <phoenix/proto_mesh.hh>

PxMultiResolutionMesh* pxMrmLoad(PxBuffer* buffer) {
	try {
		auto mat = phoenix::proto_mesh::parse(buffer->duplicate());
		return new phoenix::proto_mesh(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error,
		                 "encountered exception while parsing PxMultiResolutionMesh: ",
		                 e.what());
		return nullptr;
	}
}

PxMultiResolutionMesh* pxMrmLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetEntryByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vfs entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
	PxMultiResolutionMesh* result = pxMrmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMrmDestroy(PxMultiResolutionMesh* mrm) {
	delete mrm;
}

uint32_t pxMrmGetPositionCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) mrm->positions.size();
}

PxVec3 pxMrmGetPosition(PxMultiResolutionMesh const* mrm, uint32_t i) {
	auto& pos = mrm->positions[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}

uint32_t pxMrmGetNormalCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) mrm->normals.size();
}

PxVec3 pxMrmGetNormal(PxMultiResolutionMesh const* mrm, uint32_t i) {
	auto& pos = mrm->normals[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}

uint32_t pxMrmGetSubMeshCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) mrm->sub_meshes.size();
}

PxMultiResolutionSubMesh const* pxMrmGetSubMesh(PxMultiResolutionMesh const* mrm, uint32_t i) {
	return &mrm->sub_meshes[i];
}

uint32_t pxMrmGetMaterialCount(PxMultiResolutionMesh const* mrm) {
	return (uint32_t) mrm->materials.size();
}

PxMaterial const* pxMrmGetMaterial(PxMultiResolutionMesh const* mrm, uint32_t i) {
	return &mrm->materials[i];
}

uint8_t pxMrmGetAlphaTest(PxMultiResolutionMesh const* mrm) {
	return mrm->alpha_test;
}

PxAABB pxMrmGetBbox(PxMultiResolutionMesh const* mrm) {
	auto& bbox = mrm->bbox;
	return PxAABB {
	    PxVec3 {bbox.min.x, bbox.min.y, bbox.min.z},
	    PxVec3 {bbox.max.x, bbox.max.y, bbox.max.z},
	};
}

PxMaterial const* pxMrmSubMeshGetMaterial(PxMultiResolutionSubMesh const* sub) {
	return &sub->mat;
}

uint32_t pxMrmSubMeshGetTriangleCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) sub->triangles.size();
}

void pxMrmSubMeshGetTriangle(PxMultiResolutionSubMesh const* sub, uint32_t i, uint16_t* a, uint16_t* b, uint16_t* c) {
	auto& tri = sub->triangles[i];
	*a = tri.wedges[0];
	*b = tri.wedges[1];
	*c = tri.wedges[2];
}

uint32_t pxMrmSubMeshGetWedgeCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) sub->wedges.size();
}

void pxMrmSubMeshGetWedge(PxMultiResolutionSubMesh const* sub,
                          uint32_t i,
                          PxVec3* normal,
                          PxVec2* texture,
                          uint16_t* index) {
	auto& tri = sub->wedges[i];
	normal->x = tri.normal.x;
	normal->y = tri.normal.y;
	normal->z = tri.normal.z;
	texture->x = tri.texture.x;
	texture->y = tri.texture.y;
	texture->x = tri.texture.x;
	*index = tri.index;
}

float const* pxMrmSubMeshGetColors(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& clrs = sub->colors;
	*length = (uint32_t) clrs.size();
	return clrs.data();
}

uint16_t const* pxMrmSubMeshGetTrianglePlaneIndices(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& clrs = sub->triangle_plane_indices;
	*length = (uint32_t) clrs.size();
	return clrs.data();
}

uint32_t pxMrmSubMeshGetTrianglePlaneCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) sub->triangle_planes.size();
}

void pxMrmSubMeshGetTrianglePlane(PxMultiResolutionSubMesh const* sub, uint32_t i, float* distance, PxVec3* normal) {
	auto& tri = sub->triangle_planes[i];
	*distance = tri.distance;
	normal->x = tri.normal.x;
	normal->y = tri.normal.y;
	normal->z = tri.normal.z;
}

uint32_t pxMrmSubMeshGetTriangleEdgeCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) sub->triangle_edges.size();
}

void pxMrmSubMeshGetTriangleEdge(PxMultiResolutionSubMesh const* sub,
                                 uint32_t i,
                                 uint16_t* a,
                                 uint16_t* b,
                                 uint16_t* c) {
	auto& tri = sub->triangle_edges[i];
	*a = tri.edges[0];
	*b = tri.edges[1];
	*c = tri.edges[2];
}

uint32_t pxMrmSubMeshGetEdgeCount(PxMultiResolutionSubMesh const* sub) {
	return (uint32_t) sub->edges.size();
}

void pxMrmSubMeshGetEdge(PxMultiResolutionSubMesh const* sub, uint32_t i, uint16_t* a, uint16_t* b) {
	auto& tri = sub->edges[i];
	*a = tri.edges[0];
	*b = tri.edges[1];
}

float const* pxMrmSubMeshGetEdgeScores(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& scrs = sub->edge_scores;
	*length = (uint32_t) scrs.size();
	return scrs.data();
}

uint16_t const* pxMrmSubMeshGetWedgeMap(PxMultiResolutionSubMesh const* sub, uint32_t* length) {
	auto& scrs = sub->wedge_map;
	*length = (uint32_t) scrs.size();
	return scrs.data();
}
