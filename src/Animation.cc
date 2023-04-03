// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"
#include "phoenix/cffi/Api.h"
#include "phoenix/cffi/Buffer.h"
#include "phoenix/cffi/Vdf.h"

#include <phoenix/animation.hh>
#include <phoenix/cffi/Animation.h>

PxModelAnimation* pxManLoad(PxBuffer* buffer) {
	try {
		auto* buf = RC(px::buffer, buffer);
		auto ani = px::animation::parse(buf->duplicate());
		return RC(PxModelAnimation, new px::animation(std::move(ani)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModelAnimation* pxManLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxModelAnimation* result = pxManLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxManDestroy(PxModelAnimation* ani) {
	delete RC(px::animation, ani);
}

char const* pxManGetName(PxModelAnimation const* man) {
	return RCC(px::animation, man)->name.c_str();
}

char const* pxManGetNext(PxModelAnimation const* man) {
	return RCC(px::animation, man)->next.c_str();
}

uint32_t pxManGetLayer(PxModelAnimation const* man) {
	return RCC(px::animation, man)->layer;
}

uint32_t pxManGetFrameCount(PxModelAnimation const* man) {
	return RCC(px::animation, man)->frame_count;
}

uint32_t pxManGetNodeCount(PxModelAnimation const* man) {
	return RCC(px::animation, man)->node_count;
}

float pxManGetFps(PxModelAnimation const* man) {
	return RCC(px::animation, man)->fps;
}

PxAABB pxManGetBbox(PxModelAnimation const* man) {
	auto& bb = RCC(px::animation, man)->bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

uint32_t pxManGetChecksum(PxModelAnimation const* man) {
	return RCC(px::animation, man)->checksum;
}

uint32_t const* pxManGetNodeIndices(PxModelAnimation const* man, uint32_t* length) {
	auto& ni = RCC(px::animation, man)->node_indices;
	*length = (uint32_t) ni.size();
	return ni.data();
}

void pxManGetSample(PxModelAnimation const* man, uint32_t i, PxVec3* position, PxQuat* rotation) {
	auto const& src = RCC(px::animation, man)->samples[i];
	position->x = src.position.x;
	position->y = src.position.y;
	position->z = src.position.z;
	rotation->x = src.rotation.x;
	rotation->y = src.rotation.y;
	rotation->z = src.rotation.z;
	rotation->w = src.rotation.w;
}
