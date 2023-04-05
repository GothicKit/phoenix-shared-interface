// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/MorphMesh.h>
#include <phoenix/morph_mesh.hh>

PxMorphMesh* pxMmbLoad(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::morph_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxMorphMesh*>(new phoenix::morph_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxMorphMesh* pxMmbLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxMorphMesh* result = pxMmbLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMmbDestroy(PxMorphMesh* mmb) {
	delete reinterpret_cast<phoenix::morph_mesh*>(mmb);
}

char const* pxMmbGetName(PxMorphMesh const* mmb) {
	return RCC(px::morph_mesh, mmb)->name.c_str();
}

PxMultiResolutionMesh const* pxMmbGetMesh(PxMorphMesh const* mmb) {
	return RCC(PxMultiResolutionMesh, &RCC(px::morph_mesh, mmb)->mesh);
}

uint32_t pxMmbGetMorphPositionCount(PxMorphMesh const* mmb) {
	return (uint32_t) RCC(px::morph_mesh, mmb)->morph_positions.size();
}

PxVec3 pxMmbGetMorphPosition(PxMorphMesh const* mmb, uint32_t i) {
	auto& pos = RCC(px::morph_mesh, mmb)->morph_positions[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}

uint32_t pxMmbGetAnimationCount(PxMorphMesh const* mmb) {
	return (uint32_t) RCC(px::morph_mesh, mmb)->animations.size();
}

PxMorphMeshAnimation const* pxMmbGetAnimation(PxMorphMesh const* mmb, uint32_t i) {
	return RCC(PxMorphMeshAnimation, &RCC(px::morph_mesh, mmb)->animations[i]);
}

char const* pxMmbAniGetName(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->name.c_str();
}

int32_t pxMmbAniGetLayer(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->layer;
}

float pxMmbAniGetBlendIn(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->blend_in;
}

float pxMmbAniGetBlendOut(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->blend_out;
}

float pxMmbAniGetDuration(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->duration;
}

float pxMmbAniGetSpeed(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->duration;
}

uint8_t pxMmbAniGetFlags(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->flags;
}

uint32_t pxMmbAniGetFrameCount(PxMorphMeshAnimation const* ani) {
	return RCC(px::morph_animation, ani)->frame_count;
}

uint32_t const* pxMmbAniGetVertices(PxMorphMeshAnimation const* ani, uint32_t* length) {
	auto& verts = RCC(px::morph_animation, ani)->vertices;
	*length = (uint32_t) verts.size();
	return RCC(px::morph_animation, ani)->vertices.data();
}

uint32_t pxMmbAniGetSampleCount(PxMorphMeshAnimation const* ani) {
	return (uint32_t) RCC(px::morph_animation, ani)->samples.size();
}

PxVec3 pxMmbAniGetSample(PxMorphMeshAnimation const* ani, uint32_t i) {
	auto& pos = RCC(px::morph_animation, ani)->samples[i];
	return PxVec3 {pos.x, pos.y, pos.z};
}
