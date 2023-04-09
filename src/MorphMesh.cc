// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/MorphMesh.h>
#include <phoenix/morph_mesh.hh>

PxMorphMesh* pxMmbLoad(PxBuffer* buffer) {
	try {
		auto mat = phoenix::morph_mesh::parse(buffer->duplicate());
		return new phoenix::morph_mesh(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxMorphMesh: ", e.what());
		return nullptr;
	}
}

PxMorphMesh* pxMmbLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vdf entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxMorphMesh* result = pxMmbLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMmbDestroy(PxMorphMesh* mmb) {
	delete mmb;
}

char const* pxMmbGetName(PxMorphMesh const* mmb) {
	return mmb->name.c_str();
}

PxMultiResolutionMesh const* pxMmbGetMesh(PxMorphMesh const* mmb) {
	return &mmb->mesh;
}

uint32_t pxMmbGetMorphPositionCount(PxMorphMesh const* mmb) {
	return (uint32_t) mmb->morph_positions.size();
}

PxVec3 pxMmbGetMorphPosition(PxMorphMesh const* mmb, uint32_t i) {
	auto& pos = mmb->morph_positions[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}

uint32_t pxMmbGetAnimationCount(PxMorphMesh const* mmb) {
	return (uint32_t) mmb->animations.size();
}

PxMorphMeshAnimation const* pxMmbGetAnimation(PxMorphMesh const* mmb, uint32_t i) {
	return &mmb->animations[i];
}

char const* pxMmbAniGetName(PxMorphMeshAnimation const* ani) {
	return ani->name.c_str();
}

int32_t pxMmbAniGetLayer(PxMorphMeshAnimation const* ani) {
	return ani->layer;
}

float pxMmbAniGetBlendIn(PxMorphMeshAnimation const* ani) {
	return ani->blend_in;
}

float pxMmbAniGetBlendOut(PxMorphMeshAnimation const* ani) {
	return ani->blend_out;
}

float pxMmbAniGetDuration(PxMorphMeshAnimation const* ani) {
	return ani->duration;
}

float pxMmbAniGetSpeed(PxMorphMeshAnimation const* ani) {
	return ani->duration;
}

uint8_t pxMmbAniGetFlags(PxMorphMeshAnimation const* ani) {
	return ani->flags;
}

uint32_t pxMmbAniGetFrameCount(PxMorphMeshAnimation const* ani) {
	return ani->frame_count;
}

uint32_t const* pxMmbAniGetVertices(PxMorphMeshAnimation const* ani, uint32_t* length) {
	auto& verts = ani->vertices;
	*length = (uint32_t) verts.size();
	return ani->vertices.data();
}

uint32_t pxMmbAniGetSampleCount(PxMorphMeshAnimation const* ani) {
	return (uint32_t) ani->samples.size();
}

PxVec3 pxMmbAniGetSample(PxMorphMeshAnimation const* ani, uint32_t i) {
	auto& pos = ani->samples[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}
