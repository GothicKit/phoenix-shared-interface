// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "phoenix/cffi/BspTree.h"

PxBspTreeMode pxBspGetMode(PxBspTree const* slf) {
	return static_cast<PxBspTreeMode>(slf->mode);
}

size_t pxBspGetPolygonIndicesLength(PxBspTree const* slf) {
	return slf->polygon_indices.size();
}

uint32_t const* pxBspGetPolygonIndices(PxBspTree const* slf, size_t* size) {
	if (size != nullptr) *size = slf->polygon_indices.size();
	return slf->polygon_indices.data();
}

size_t pxBspGetLeafPolygonIndicesLength(PxBspTree const* slf) {
	return slf->leaf_polygons.size();
}

uint32_t const* pxBspGetLeafPolygonIndices(PxBspTree const* slf, size_t* size) {
	if (size != nullptr) *size = slf->leaf_polygons.size();
	return slf->leaf_polygons.data();
}

size_t pxBspGetPortalPolygonIndicesLength(PxBspTree const* slf) {
	return slf->portal_polygon_indices.size();
}

uint32_t const* pxBspGetPortalPolygonIndices(PxBspTree const* slf, size_t* size) {
	if (size != nullptr) *size = slf->portal_polygon_indices.size();
	return slf->portal_polygon_indices.data();
}

size_t pxBspGetLightPointsLength(PxBspTree const* slf) {
	return slf->light_points.size();
}

PxVec3 pxBspGetLightPoint(PxBspTree const* slf, size_t idx) {
	auto& v = slf->light_points.at(idx);
	return {v.x, v.y, v.z};
}

size_t pxBspGetLeafNodeIndicesLength(PxBspTree const* slf) {
	return slf->leaf_node_indices.size();
}

uint64_t const* pxBspGetLeafNodeIndices(PxBspTree const* slf, size_t* size) {
	if (size != nullptr) *size = slf->leaf_node_indices.size();
	return slf->leaf_node_indices.data();
}

size_t pxBspGetSectorsLength(PxBspTree const* slf) {
	return slf->sectors.size();
}

void pxBspGetSector(PxBspTree const* slf,
                    size_t idx,
                    char const** name,
                    uint32_t const** nodeIndices,
                    size_t* nodeIndicesLength,
                    uint32_t const** portalPolygonIndices,
                    size_t* portalPolygonIndicesLength) {
	auto& v = slf->sectors.at(idx);
	if (name != nullptr) *name = v.name.c_str();
	if (nodeIndices != nullptr) *nodeIndices = v.node_indices.data();
	if (nodeIndicesLength != nullptr) *nodeIndicesLength = v.node_indices.size();
	if (portalPolygonIndices != nullptr) *portalPolygonIndices = v.portal_polygon_indices.data();
	if (portalPolygonIndicesLength != nullptr) *portalPolygonIndicesLength = v.portal_polygon_indices.size();
}

size_t pxBspGetNodesLength(PxBspTree const* slf) {
	return slf->nodes.size();
}

void pxBspGetNode(PxBspTree const* slf,
                  size_t idx,
                  PxVec4* plane,
                  PxAABB* bbox,
                  uint32_t* polygonIndex,
                  uint32_t* polygonCount,
                  int32_t* frontNodeIndex,
                  int32_t* backNodeIndex,
                  int32_t* parentNodeIndex) {
	auto& v = slf->nodes.at(idx);
	if (plane != nullptr) {
		plane->x = v.plane.x;
		plane->y = v.plane.y;
		plane->z = v.plane.z;
		plane->w = v.plane.w;
	}

	if (bbox != nullptr) {
		bbox->max.x = v.bbox.max.x;
		bbox->max.y = v.bbox.max.y;
		bbox->max.z = v.bbox.max.z;
		bbox->min.x = v.bbox.min.x;
		bbox->min.y = v.bbox.min.y;
		bbox->min.z = v.bbox.min.z;
	}

	if (polygonIndex != nullptr) *polygonIndex = v.polygon_index;
	if (polygonCount != nullptr) *polygonCount = v.polygon_count;
	if (frontNodeIndex != nullptr) *frontNodeIndex = v.front_index;
	if (backNodeIndex != nullptr) *backNodeIndex = v.back_index;
	if (parentNodeIndex != nullptr) *parentNodeIndex = v.parent_index;
}
