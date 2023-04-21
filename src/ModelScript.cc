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

const char* pxMdsGetModelTagBone(PxModelScript* mds, uint32_t i)
{
	return mds->model_tags[i].bone.c_str();
}

// AnimationCombination
uint32_t pxMdsGetAnimationCombinationCount(PxModelScript* mds)
{
	return mds->combinations.size();
}
const char* pxMdsGetAnimationCombinationName(PxModelScript* mds, uint32_t i){
	return mds->combinations[i].name.c_str();
}
uint32_t pxMdsGetAnimationCombinationLayer(PxModelScript* mds, uint32_t i){
	return mds->combinations[i].layer;
}
const char* pxMdsGetAnimationCombinationNext(PxModelScript* mds, uint32_t i){
	return mds->combinations[i].next.c_str();
}
float pxMdsGetAnimationCombinationBlendIn(PxModelScript* mds, uint32_t i){
	return mds->combinations[i].blend_in;
}
float pxMdsGetAnimationCombinationBlendOut(PxModelScript* mds, uint32_t i){
	return mds->combinations[i].blend_out;
}
PxAnimationFlags pxMdsGetAnimationCombinationFlags(PxModelScript* mds, uint32_t i){
	return static_cast<PxAnimationFlags>(mds->combinations[i].flags);
}
const char* pxMdsGetAnimationCombinationModel(PxModelScript* mds, uint32_t i){
	return mds->combinations[i].model.c_str();
}
int32_t pxMdsGetAnimationCombinationLastFrame(PxModelScript* mds, uint32_t i){
	return mds->combinations[i].last_frame;
}

// Blends
uint32_t pxMdsGetAnimationBlendingCount(PxModelScript* mds)
{
	return mds->blends.size();
}
const char* pxMdsGetAnimationBlendingName(PxModelScript* mds, uint32_t i)
{
	return mds->blends[i].name.c_str();
}
const char* pxMdsGetAnimationBlendingNext(PxModelScript* mds, uint32_t i)
{
	return mds->blends[i].next.c_str();
}
float pxMdsGetAnimationBlendingBlendIn(PxModelScript* mds, uint32_t i)
{
	return mds->blends[i].blend_in;
}
float pxMdsGetAnimationBlendingBlendOut(PxModelScript* mds, uint32_t i)
{
	return mds->blends[i].blend_out;
}


// AnimationAlias
uint32_t pxMdsGetAnimationAliasCount(PxModelScript* mds)
{
	return mds->aliases.size();
}
const char* pxMdsGetAnimationAliasName(PxModelScript* mds, uint32_t i)
{
	return mds->aliases[i].name.c_str();
}
uint32_t pxMdsGetAnimationAliasLayer(PxModelScript* mds, uint32_t i)
{
	return mds->aliases[i].layer;
}
const char* pxMdsGetAnimationAliasNext(PxModelScript* mds, uint32_t i)
{
	return mds->aliases[i].next.c_str();
}
float pxMdsGetAnimationAliasBlendIn(PxModelScript* mds, uint32_t i)
{
	return mds->aliases[i].blend_in;
}
float pxMdsGetAnimationAliasBlendOut(PxModelScript* mds, uint32_t i)
{
	return mds->aliases[i].blend_out;
}
PxAnimationFlags pxMdsGetAnimationAliasFlags(PxModelScript* mds, uint32_t i)
{
	return static_cast<PxAnimationFlags>(mds->aliases[i].flags);
}
const char* pxMdsGetAnimationAliasAlias(PxModelScript* mds, uint32_t i)
{
	return mds->aliases[i].alias.c_str();
}
PxAnimationDirection pxMdsGetAnimationAliasDirection(PxModelScript* mds, uint32_t i)
{
	return static_cast<PxAnimationDirection>(mds->aliases[i].direction);
}
