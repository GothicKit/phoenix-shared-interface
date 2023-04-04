// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/ModelHierarchy.h>
#include <phoenix/model_hierarchy.hh>

PxModelHierarchy* pxMdhLoad(PxBuffer* buffer) {
	try {
		auto* buf = RC(px::buffer, buffer);
		auto mat = px::model_hierarchy::parse(buf->duplicate());
		return RC(PxModelHierarchy, new px::model_hierarchy(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModelHierarchy* pxMdhLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxModelHierarchy* result = pxMdhLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdhDestroy(PxModelHierarchy* mdh) {
	delete RC(px::model_hierarchy, mdh);
}

PxAABB pxMdhGetBbox(PxModelHierarchy const* mdh) {
	auto& bb = RCC(px::model_hierarchy, mdh)->bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

PxAABB pxMdhGetCollisionBbox(PxModelHierarchy const* mdh) {
	auto& bb = RCC(px::model_hierarchy, mdh)->collision_bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

PxVec3 pxMdhGetRootTranslation(PxModelHierarchy const* mdh) {
	auto& rt = RCC(px::model_hierarchy, mdh)->root_translation;
	return {rt.x, rt.y, rt.z};
}

uint32_t pxMdhGetChecksum(PxModelHierarchy const* mdh) {
	return RCC(px::model_hierarchy, mdh)->checksum;
}

uint32_t pxMdhGetNodeCount(PxModelHierarchy const* mdh) {
	return (uint32_t) RCC(px::model_hierarchy, mdh)->nodes.size();
}

void pxMdhGetNode(PxModelHierarchy const* mdh,
                  uint32_t i,
                  int16_t* parent,
                  char const** name /*, TODO: Node transform*/) {
	auto& node = RCC(px::model_hierarchy, mdh)->nodes[i];
	*parent = node.parent_index;
	*name = node.name.c_str();
}
