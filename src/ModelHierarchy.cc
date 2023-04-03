// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/model_hierarchy.hh>
#include <phoenix/cffi/ModelHierarchy.h>

PxModelHierarchy* px_mdh_parse(PxBuffer* buffer) {
	try {
		auto* buf = RC(px::buffer, buffer);
		auto mat = px::model_hierarchy::parse(buf->duplicate());
		return RC(PxModelHierarchy, new px::model_hierarchy(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxAABB px_mdh_bbox(PxModelHierarchy const* mdh) {
	auto& bb = RCC(px::model_hierarchy, mdh)->bbox;
	return {
		{bb.min.x, bb.min.y, bb.min.z},
		{bb.max.x, bb.max.y, bb.max.z},
	};
}

PxAABB px_mdh_collision_bbox(PxModelHierarchy const* mdh) {
	auto& bb = RCC(px::model_hierarchy, mdh)->collision_bbox;
	return {
		{bb.min.x, bb.min.y, bb.min.z},
		{bb.max.x, bb.max.y, bb.max.z},
	};
}

PxVec3 px_mdh_root_translation(PxModelHierarchy const* mdh) {
	auto& rt = RCC(px::model_hierarchy, mdh)->root_translation;
	return {rt.x, rt.y, rt.z};
}

uint32_t px_mdh_checksum(PxModelHierarchy const* mdh) {
	return RCC(px::model_hierarchy, mdh)->checksum;
}

uint32_t px_mdh_node_count(PxModelHierarchy const* mdh) {
	return (uint32_t) RCC(px::model_hierarchy, mdh)->nodes.size();
}

void px_mdh_node(PxModelHierarchy const* mdh, uint32_t i, int16_t* parent, char const** name /*, TODO: Node transform*/) {
	auto& node = RCC(px::model_hierarchy, mdh)->nodes[i];
	*parent = node.parent_index;
	*name = node.name.c_str();
}

int16_t px_mdh_node_parent(PxModelHierarchyNode const* node) {
	return RCC(px::model_hierarchy_node, node)->parent_index;
}

char const* px_mdh_node_name(PxModelHierarchyNode const* node) {
	return RCC(px::model_hierarchy_node, node)->name.c_str();
}

void px_mdh_destroy(PxModelHierarchy* mdh) {
	delete RC(px::model_hierarchy, mdh);
}
