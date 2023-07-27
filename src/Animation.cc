// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"
#include "phoenix/cffi/Api.h"
#include "phoenix/cffi/Buffer.h"
#include "phoenix/cffi/Vfs.h"

#include <phoenix/animation.hh>
#include <phoenix/cffi/Animation.h>

PxModelAnimation* pxManLoad(PxBuffer* buffer) {
	try {
		auto ani = px::animation::parse(buffer->duplicate());
		return new px::animation(std::move(ani));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxModelAnimation: ", e.what());
		return nullptr;
	}
}

PxModelAnimation* pxManLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetNodeByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vfs entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
	PxModelAnimation* result = pxManLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxManDestroy(PxModelAnimation* ani) {
	delete ani;
}

char const* pxManGetName(PxModelAnimation const* man) {
	return man->name.c_str();
}

char const* pxManGetNext(PxModelAnimation const* man) {
	return man->next.c_str();
}

uint32_t pxManGetLayer(PxModelAnimation const* man) {
	return man->layer;
}

uint32_t pxManGetFrameCount(PxModelAnimation const* man) {
	return man->frame_count;
}

uint32_t pxManGetNodeCount(PxModelAnimation const* man) {
	return man->node_count;
}

float pxManGetFps(PxModelAnimation const* man) {
	return man->fps;
}

PxAABB pxManGetBbox(PxModelAnimation const* man) {
	auto& bb = man->bbox;
	return {
	    {bb.min.x, bb.min.y, bb.min.z},
	    {bb.max.x, bb.max.y, bb.max.z},
	};
}

uint32_t pxManGetChecksum(PxModelAnimation const* man) {
	return man->checksum;
}

uint32_t const* pxManGetNodeIndices(PxModelAnimation const* man, uint32_t* length) {
	auto& ni = man->node_indices;
	*length = (uint32_t) ni.size();
	return ni.data();
}

uint32_t pxManGetSampleCount(PxModelAnimation const* man) {
	return (uint32_t) man->samples.size();
}

void pxManGetSample(PxModelAnimation const* man, uint32_t i, PxVec3* position, PxQuat* rotation) {
	auto const& src = man->samples[i];
	position->x = src.position.x;
	position->y = src.position.y;
	position->z = src.position.z;
	rotation->x = src.rotation.x;
	rotation->y = src.rotation.y;
	rotation->z = src.rotation.z;
	rotation->w = src.rotation.w;
}
