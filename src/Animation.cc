// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"
#include "phoenix/cffi/Api.h"

#include <phoenix/animation.hh>
#include <phoenix/cffi/Animation.h>


PxModelAnimation* px_man_parse(PxBuffer* buffer) {
	try {
		auto* buf = RC(px::buffer, buffer);
		auto ani = px::animation::parse(buf->duplicate());
		return RC(PxModelAnimation, new px::animation(std::move(ani)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void px_man_destroy(PxModelAnimation* ani) {
	delete RC(px::animation, ani);
}

char const* px_man_name(PxModelAnimation const* man) {
	return RCC(px::animation, man)->name.c_str();
}

char const* px_man_next(PxModelAnimation const* man) {
	return RCC(px::animation, man)->next.c_str();
}

uint32_t px_man_layer(PxModelAnimation const* man) {
	return RCC(px::animation, man)->layer;
}

uint32_t px_man_frame_count(PxModelAnimation const* man) {
	return RCC(px::animation, man)->frame_count;
}

uint32_t px_man_node_count(PxModelAnimation const* man) {
	return RCC(px::animation, man)->node_count;
}

float px_man_fps(PxModelAnimation const* man) {
	return RCC(px::animation, man)->fps;
}

PxAABB px_man_bbox(PxModelAnimation const* man) {
	auto& bb = RCC(px::animation, man)->bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

uint32_t px_man_checksum(PxModelAnimation const* man) {
	return RCC(px::animation, man)->checksum;
}

uint32_t const* px_man_node_indices(PxModelAnimation const* man, uint32_t* length) {
	auto& ni = RCC(px::animation, man)->node_indices;
	*length = (uint32_t) ni.size();
	return ni.data();
}

void px_man_sample(PxModelAnimation const* man, uint32_t i, PxVec3* position, PxQuat* rotation) {
	auto const& src = RCC(px::animation, man)->samples[i];
	position->x = src.position.x;
	position->y = src.position.y;
	position->z = src.position.z;
	rotation->x = src.rotation.x;
	rotation->y = src.rotation.y;
	rotation->z = src.rotation.z;
	rotation->w = src.rotation.w;
}
