// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/ModelHierarchy.h>
#include <phoenix/model_hierarchy.hh>

PxModelHierarchy* pxMdhLoad(PxBuffer* buffer) {
	try {
		auto mat = px::model_hierarchy::parse(buffer->duplicate());
		return new px::model_hierarchy(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxModelHierarchy: ", e.what());
		return nullptr;
	}
}

PxModelHierarchy* pxMdhLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetEntryByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vfs entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
	PxModelHierarchy* result = pxMdhLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdhDestroy(PxModelHierarchy* mdh) {
	delete mdh;
}

PxAABB pxMdhGetBbox(PxModelHierarchy const* mdh) {
	auto& bb = mdh->bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

PxAABB pxMdhGetCollisionBbox(PxModelHierarchy const* mdh) {
	auto& bb = mdh->collision_bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

PxVec3 pxMdhGetRootTranslation(PxModelHierarchy const* mdh) {
	auto& rt = mdh->root_translation;
	return {rt.x, rt.y, rt.z};
}

uint32_t pxMdhGetChecksum(PxModelHierarchy const* mdh) {
	return mdh->checksum;
}

uint32_t pxMdhGetNodeCount(PxModelHierarchy const* mdh) {
	return (uint32_t) mdh->nodes.size();
}

void pxMdhGetNode(PxModelHierarchy const* mdh, uint32_t i, int16_t* parent, char const** name, PxMat4x4* transform) {
	auto& node = mdh->nodes[i];
	*parent = node.parent_index;
	*name = node.name.c_str();
	transform->m00 = node.transform[0][0];
	transform->m01 = node.transform[0][1];
	transform->m02 = node.transform[0][2];
	transform->m03 = node.transform[0][3];
	transform->m10 = node.transform[1][0];
	transform->m11 = node.transform[1][1];
	transform->m12 = node.transform[1][2];
	transform->m13 = node.transform[1][3];
	transform->m20 = node.transform[2][0];
	transform->m21 = node.transform[2][1];
	transform->m22 = node.transform[2][2];
	transform->m23 = node.transform[2][3];
	transform->m30 = node.transform[3][0];
	transform->m31 = node.transform[3][1];
	transform->m32 = node.transform[3][2];
	transform->m33 = node.transform[3][3];
}
