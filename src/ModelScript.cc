// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/ModelScript.h>
#include <phoenix/model_script.hh>

PxModelScript* pxMdsLoad(PxBuffer* buffer) {
	try {
		auto mat = phoenix::model_script::parse(buffer->duplicate());
		return new phoenix::model_script(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxModelScript: ", e.what());
		return nullptr;
	}
}

PxModelScript* pxMdsLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vdf entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxModelScript* result = pxMdsLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdsDestroy(PxModelScript* mdm) {
	delete mdm;
}



uint32_t pxMdsGetMeshCount(PxModelScript* mds)
{
	return mds->meshes.size();
}

const char* pxMdsGetMesh(PxModelScript* mds, uint32_t i)
{
	return mds->meshes[i].c_str();
}

uint32_t pxMdsGetDisabledAnimationsCount(PxModelScript* mds)
{
	return mds->disabled_animations.size();
}

const char* pxMdsGetDisabledAnimation(PxModelScript* mds, uint32_t i)
{
	return mds->disabled_animations[i].c_str();
}

uint32_t pxMdsGetModelTagCount(PxModelScript* mds)
{
	return mds->model_tags.size();
}

void pxMdsGetModelTag(PxModelScript* mds, uint32_t i, const char* bone)
{
	auto &tag = mds->model_tags[i];
	bone = tag.bone.c_str();
}

uint32_t pxMdsGetAnimationCombinationCount(PxModelScript* mds)
{
	return mds->combinations.size();
}

void pxMdsGetAnimationCombination(PxModelScript* mds, uint32_t i,
	const char* name,
    uint32_t* layer,
    const char* next,
	float* blend_in,
	float* blend_out,
	PxAnimationFlags* flags,
	const char* model,
	int32_t* last_frame)
{
	auto &combination = mds->combinations[i];

	name = combination.name.c_str(),
    *layer = combination.layer,
    next = combination.next.c_str(),
	*blend_in = combination.blend_in,
	*blend_out = combination.blend_out,
	*flags = static_cast<PxAnimationFlags>(combination.flags),
	model = combination.model.c_str(),
	*last_frame = combination.last_frame;
}

uint32_t pxMdsGetAnimationBlendingCount(PxModelScript* mds)
{
	return mds->blends.size();
}

void pxMdsGetAnimationBlending(PxModelScript* mds, uint32_t i,
	const char* name,
	const char* next,
	float* blend_in,
	float* blend_out)
{
	auto &blending = mds->blends[i];

	name = blending.name.c_str();
	next = blending.next.c_str();
	*blend_in = blending.blend_in;
	*blend_out = blending.blend_out;
}

uint32_t pxMdsGetAnimationAliasCount(PxModelScript* mds)
{
	return mds->aliases.size();
}

void pxMdsGetAnimationAlias(PxModelScript* mds, uint32_t i,
			const char* name,
			uint32_t* layer,
			const char* next,
			float* blend_in,
			float* blend_out,
			PxAnimationFlags* flags,
			const char* alias,
			PxAnimationDirection* direction)
{
	auto &animAlias = mds->aliases[i];

	name = animAlias.name.c_str();
	*layer = animAlias.layer;
	next = animAlias.next.c_str();
	*blend_in = animAlias.blend_in;
	*blend_out = animAlias.blend_out;
	*flags = static_cast<PxAnimationFlags>(animAlias.flags);
	alias = animAlias.alias.c_str();
	*direction = static_cast<PxAnimationDirection>(animAlias.direction);
}
