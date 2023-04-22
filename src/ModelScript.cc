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

const char* pxMdsGetSkeletonName(PxModelScript* mds) {
	return mds->skeleton.name.c_str();
}
bool pxMdsGetSkeletonDisableMesh(PxModelScript* mds) {
	return mds->skeleton.disable_mesh;
}

uint32_t pxMdsGetMeshCount(PxModelScript* mds) {
	return (uint32_t) mds->meshes.size();
}

const char* pxMdsGetMesh(PxModelScript* mds, uint32_t i) {
	return mds->meshes[i].c_str();
}

uint32_t pxMdsGetDisabledAnimationsCount(PxModelScript* mds) {
	return (uint32_t) mds->disabled_animations.size();
}

const char* pxMdsGetDisabledAnimation(PxModelScript* mds, uint32_t i) {
	return mds->disabled_animations[i].c_str();
}

uint32_t pxMdsGetModelTagCount(PxModelScript* mds) {
	return (uint32_t) mds->model_tags.size();
}

const char* pxMdsGetModelTagBone(PxModelScript* mds, uint32_t i) {
	return mds->model_tags[i].bone.c_str();
}

// AnimationCombination
uint32_t pxMdsGetAnimationCombinationCount(PxModelScript* mds) {
	return (uint32_t) mds->combinations.size();
}
const char* pxMdsGetAnimationCombinationName(PxModelScript* mds, uint32_t i) {
	return mds->combinations[i].name.c_str();
}
uint32_t pxMdsGetAnimationCombinationLayer(PxModelScript* mds, uint32_t i) {
	return mds->combinations[i].layer;
}
const char* pxMdsGetAnimationCombinationNext(PxModelScript* mds, uint32_t i) {
	return mds->combinations[i].next.c_str();
}
float pxMdsGetAnimationCombinationBlendIn(PxModelScript* mds, uint32_t i) {
	return mds->combinations[i].blend_in;
}
float pxMdsGetAnimationCombinationBlendOut(PxModelScript* mds, uint32_t i) {
	return mds->combinations[i].blend_out;
}
PxAnimationFlags pxMdsGetAnimationCombinationFlags(PxModelScript* mds, uint32_t i) {
	return static_cast<PxAnimationFlags>(mds->combinations[i].flags);
}
const char* pxMdsGetAnimationCombinationModel(PxModelScript* mds, uint32_t i) {
	return mds->combinations[i].model.c_str();
}
int32_t pxMdsGetAnimationCombinationLastFrame(PxModelScript* mds, uint32_t i) {
	return mds->combinations[i].last_frame;
}

// Blends
uint32_t pxMdsGetAnimationBlendingCount(PxModelScript* mds) {
	return (uint32_t) mds->blends.size();
}
const char* pxMdsGetAnimationBlendingName(PxModelScript* mds, uint32_t i) {
	return mds->blends[i].name.c_str();
}
const char* pxMdsGetAnimationBlendingNext(PxModelScript* mds, uint32_t i) {
	return mds->blends[i].next.c_str();
}
float pxMdsGetAnimationBlendingBlendIn(PxModelScript* mds, uint32_t i) {
	return mds->blends[i].blend_in;
}
float pxMdsGetAnimationBlendingBlendOut(PxModelScript* mds, uint32_t i) {
	return mds->blends[i].blend_out;
}


// AnimationAlias
uint32_t pxMdsGetAnimationAliasCount(PxModelScript* mds) {
	return (uint32_t) mds->aliases.size();
}
const char* pxMdsGetAnimationAliasName(PxModelScript* mds, uint32_t i) {
	return mds->aliases[i].name.c_str();
}
uint32_t pxMdsGetAnimationAliasLayer(PxModelScript* mds, uint32_t i) {
	return mds->aliases[i].layer;
}
const char* pxMdsGetAnimationAliasNext(PxModelScript* mds, uint32_t i) {
	return mds->aliases[i].next.c_str();
}
float pxMdsGetAnimationAliasBlendIn(PxModelScript* mds, uint32_t i) {
	return mds->aliases[i].blend_in;
}
float pxMdsGetAnimationAliasBlendOut(PxModelScript* mds, uint32_t i) {
	return mds->aliases[i].blend_out;
}
PxAnimationFlags pxMdsGetAnimationAliasFlags(PxModelScript* mds, uint32_t i) {
	return static_cast<PxAnimationFlags>(mds->aliases[i].flags);
}
const char* pxMdsGetAnimationAliasAlias(PxModelScript* mds, uint32_t i) {
	return mds->aliases[i].alias.c_str();
}
PxAnimationDirection pxMdsGetAnimationAliasDirection(PxModelScript* mds, uint32_t i) {
	return static_cast<PxAnimationDirection>(mds->aliases[i].direction);
}

// Animations
uint32_t pxMdsGetAnimationCount(PxModelScript* mds) {
	return (uint32_t) mds->animations.size();
}
const char* pxMdsGetAnimationName(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].name.c_str();
}
uint32_t pxMdsGetAnimationLayer(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].layer;
}
const char* pxMdsGetAnimationNext(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].next.c_str();
}
float pxMdsGetAnimationBlendIn(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].blend_in;
}
float pxMdsGetAnimationBlendOut(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].blend_out;
}
PxAnimationFlags pxMdsGetAnimationFlags(PxModelScript* mds, uint32_t i) {
	return static_cast<PxAnimationFlags>(mds->animations[i].flags);
}
const char* pxMdsGetAnimationModel(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].model.c_str();
}
PxAnimationDirection pxMdsGetAnimationDirection(PxModelScript* mds, uint32_t i) {
	return static_cast<PxAnimationDirection>(mds->animations[i].direction);
}
int32_t pxMdsGetAnimationFirstFrame(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].first_frame;
}
int32_t pxMdsGetAnimationLastFrame(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].last_frame;
}
float pxMdsGetAnimationFps(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].fps;
}
float pxMdsGetAnimationSpeed(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].speed;
}
float pxMdsGetAnimationCollisionVolumeScale(PxModelScript* mds, uint32_t i) {
	return mds->animations[i].collision_volume_scale;
}

// Animations -> EventTags
uint32_t pxMdsGetAnimation_EventTagCount(PxModelScript* mds, uint32_t i) {
	return (uint32_t) mds->animations[i].events.size();
}
int32_t pxMdsGetAnimation_EventTagFrame(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex) {
	return mds->animations[animIndex].events[eventTagIndex].frame;
}
PxEventTagType pxMdsGetAnimation_EventTagType(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex) {
	return static_cast<PxEventTagType>(mds->animations[animIndex].events[eventTagIndex].type);
}
const char* pxMdsGetAnimation_EventTagSlot(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex) {
	return mds->animations[animIndex].events[eventTagIndex].slot.c_str();
}
const char* pxMdsGetAnimation_EventTagSlot2(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex) {
	return mds->animations[animIndex].events[eventTagIndex].slot2.c_str();
}
const char* pxMdsGetAnimation_EventTagItem(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex) {
	return mds->animations[animIndex].events[eventTagIndex].item.c_str();
}
int32_t* pxMdsGetAnimation_EventTagFrames(PxModelScript* mds,
										  uint32_t animIndex,
										  uint32_t eventTagIndex,
										  uint32_t* size) {
	auto& frames = mds->animations[animIndex].events[eventTagIndex].frames;
	*size = (uint32_t) frames.size();
	return frames.data();
}
PxEventFightMode pxMdsGetAnimation_EventTagFightMode(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex) {
	return static_cast<PxEventFightMode>(mds->animations[animIndex].events[eventTagIndex].fight_mode);
}
bool pxMdsGetAnimation_EventTagAttached(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex) {
	return mds->animations[animIndex].events[eventTagIndex].attached;
}

// Animations -> EventPfx
uint32_t pxMdsGetAnimation_EventPfxCount(PxModelScript* mds, uint32_t i) {
	return (uint32_t) mds->animations[i].pfx.size();
}
int32_t pxMdsGetAnimation_EventPfxFrame(PxModelScript* mds, uint32_t animIndex, uint32_t pfxIndex) {
	return mds->animations[animIndex].pfx[pfxIndex].frame;
}
int32_t pxMdsGetAnimation_EventPfxIndex(PxModelScript* mds, uint32_t animIndex, uint32_t pfxIndex) {
	return mds->animations[animIndex].pfx[pfxIndex].index;
}
const char* pxMdsGetAnimation_EventPfxName(PxModelScript* mds, uint32_t animIndex, uint32_t pfxIndex) {
	return mds->animations[animIndex].pfx[pfxIndex].name.c_str();
}
const char* pxMdsGetAnimation_EventPfxPosition(PxModelScript* mds, uint32_t animIndex, uint32_t pfxIndex) {
	return mds->animations[animIndex].pfx[pfxIndex].position.c_str();
}
bool pxMdsGetAnimation_EventPfxAttached(PxModelScript* mds, uint32_t animIndex, uint32_t pfxIndex) {
	return mds->animations[animIndex].pfx[pfxIndex].attached;
}

// Animations -> PfxStop
uint32_t pxMdsGetAnimation_EventPfxStopCount(PxModelScript* mds, uint32_t i) {
	return (uint32_t) mds->animations[i].pfx.size();
}

void pxMdsGetAnimation_EventPfxStop(PxModelScript* mds,
									uint32_t animIndex,
									uint32_t pfxStopIndex,
									int32_t* frame,
									int32_t* index) {
	auto& pfxStop = mds->animations[animIndex].pfx[pfxStopIndex];
	*frame = pfxStop.frame;
	*index = pfxStop.index;
}

// Animations -> Sfx
uint32_t pxMdsGetAnimation_EventSfxCount(PxModelScript* mds, uint32_t i) {
	return (uint32_t) mds->animations[i].sfx.size();
}
int32_t pxMdsGetAnimation_EventSfxFrame(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx[sfxIndex].frame;
}
const char* pxMdsGetAnimation_EventSfxName(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx[sfxIndex].name.c_str();
}
float pxMdsGetAnimation_EventSfxRange(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx[sfxIndex].range;
}
bool pxMdsGetAnimation_EventSfxEmptySlot(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx[sfxIndex].empty_slot;
}

// Animations -> SfxGround
uint32_t pxMdsGetAnimationEventSfxGroundCount(PxModelScript* mds, uint32_t i) {
	return (uint32_t) mds->animations[i].sfx_ground.size();
}
int32_t pxMdsGetAnimation_EventSfxGroundFrame(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx_ground[sfxIndex].frame;
}
const char* pxMdsGetAnimation_EventSfxGroundName(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx_ground[sfxIndex].name.c_str();
}
float pxMdsGetAnimation_EventSfxGroundRange(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx_ground[sfxIndex].range;
}
bool pxMdsGetAnimation_EventSfxGroundEmptySlot(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex) {
	return mds->animations[animIndex].sfx_ground[sfxIndex].empty_slot;
}

// Animations -> EventMorphAnimate
uint32_t pxMdsGetAnimation_EventMorphAnimateCount(PxModelScript* mds, uint32_t i) {
	return (uint32_t) mds->animations[i].morph.size();
}
int32_t pxMdsGetAnimation_EventMorphAnimateFrame(PxModelScript* mds, uint32_t animIndex, uint32_t morphIndex) {
	return mds->animations[animIndex].morph[morphIndex].frame;
}
const char* pxMdsGetAnimation_EventMorphAnimateAnimation(PxModelScript* mds, uint32_t animIndex, uint32_t morphIndex) {
	return mds->animations[animIndex].morph[morphIndex].animation.c_str();
}
const char* pxMdsGetAnimation_EventMorphAnimateNode(PxModelScript* mds, uint32_t animIndex, uint32_t morphIndex) {
	return mds->animations[animIndex].morph[morphIndex].node.c_str();
}

// Animations -> EventCameraTremor
uint32_t pxMdsGetAnimation_EventCameraTremorCount(PxModelScript* mds, uint32_t i) {
	return (uint32_t) mds->animations[i].tremors.size();
}
void pxMdsGetAnimation_EventCameraTremor(PxModelScript* mds,
										 uint32_t animIndex,
										 uint32_t tremorIndex,
										 int32_t* frame,
										 int32_t* field1,
										 int32_t* field2,
										 int32_t* field3,
										 int32_t* field4) {
	auto& tremor = mds->animations[animIndex].tremors[tremorIndex];
	*frame = tremor.frame;
	*field1 = tremor.field1;
	*field2 = tremor.field2;
	*field3 = tremor.field3;
	*field4 = tremor.field4;
}
