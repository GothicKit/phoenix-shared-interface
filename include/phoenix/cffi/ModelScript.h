// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/model_script.hh>
typedef phoenix::model_script PxModelScript;
#else
typedef struct PxInternal_ModelScript PxModelScript;
#endif

typedef enum : uint8_t {
	af_none = 0,
	af_move = 1,
	af_rotate = 2,
	af_queue = 4,
	af_fly = 8,
	af_idle = 16,   
} PxAnimationFlags;

typedef enum : uint8_t {
	forward = 0,  ///< The animation samples are played from first to last.
	backward = 1, ///< The animation samples are played from last to first.
} PxAnimationDirection;

typedef enum {
	unknown,
	create_item,
	insert_item,
	remove_item,
	destroy_item,
	place_item,
	exchange_item,
	fight_mode,
	place_munition,
	remove_munition,
	draw_sound,
	undraw_sound,
	swap_mesh,
	draw_torch,
	inventory_torch,
	drop_torch,
	hit_limb,
	hit_direction,
	dam_multiply,
	par_frame,
	opt_frame,
	hit_end,
	window,
} PxEventTagType;

typedef enum {
	fist,       ///< The player fights with his fists.
	one_handed, ///< The player wields a one-handed weapon.
	two_handed, ///< The player wields a two-handed weapon.
	bow,        ///< The player wields a bow.
	crossbow,   ///< The player wields a crossbow.
	magic,      ///< The player casts a magic spell.
	none,       ///< The player is not in a fighting stance.
	invalid,    ///< A fight mode which acts as an `unset` marker. Added for OpenGothic compatibility.
} PxEventFightMode;


PXC_API PxModelScript* pxMdsLoad(PxBuffer* buffer);
PXC_API PxModelScript* pxMdsLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMdsDestroy(PxModelScript* mds);

PXC_API const char* pxMdsGetSkeletonName(PxModelScript* mds);
PXC_API bool pxMdsGetSkeletonDisableMesh(PxModelScript* mds);

PXC_API uint32_t pxMdsGetMeshCount(PxModelScript* mds);
PXC_API const char* pxMdsGetMesh(PxModelScript* mds, uint32_t i);
PXC_API uint32_t pxMdsGetDisabledAnimationsCount(PxModelScript* mds);
PXC_API const char* pxMdsGetDisabledAnimation(PxModelScript* mds, uint32_t i);

PXC_API uint32_t pxMdsGetModelTagCount(PxModelScript* mds);
PXC_API const char* pxMdsGetModelTagBone(PxModelScript* mds, uint32_t i);

// AnimationCombinations
PXC_API uint32_t pxMdsGetAnimationCombinationCount(PxModelScript* mds);
PXC_API const char* pxMdsGetAnimationCombinationName(PxModelScript* mds, uint32_t i);
PXC_API uint32_t pxMdsGetAnimationCombinationLayer(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationCombinationNext(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationCombinationBlendIn(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationCombinationBlendOut(PxModelScript* mds, uint32_t i);
PXC_API PxAnimationFlags pxMdsGetAnimationCombinationFlags(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationCombinationModel(PxModelScript* mds, uint32_t i);
PXC_API int32_t pxMdsGetAnimationCombinationLastFrame(PxModelScript* mds, uint32_t i);

// AnimationBlendings
PXC_API uint32_t pxMdsGetAnimationBlendingCount(PxModelScript* mds);
PXC_API const char* pxMdsGetAnimationBlendingName(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationBlendingNext(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationBlendingBlendIn(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationBlendingBlendOut(PxModelScript* mds, uint32_t i);

// AnimationAlias
PXC_API uint32_t pxMdsGetAnimationAliasCount(PxModelScript* mds);
PXC_API const char* pxMdsGetAnimationAliasName(PxModelScript* mds, uint32_t i);
PXC_API uint32_t pxMdsGetAnimationAliasLayer(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationAliasNext(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationAliasBlendIn(PxModelScript* mds, uint32_t i);
PXC_API float pxMdsGetAnimationAliasBlendOut(PxModelScript* mds, uint32_t i);
PXC_API PxAnimationFlags pxMdsGetAnimationAliasFlags(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationAliasAlias(PxModelScript* mds, uint32_t i);
PXC_API PxAnimationDirection pxMdsGetAnimationAliasDirection(PxModelScript* mds, uint32_t i);

// Animations
PXC_API uint32_t pxMdsGetAnimationCount(PxModelScript* mds);
PXC_API const char* pxMdsGetAnimationName(PxModelScript* mds, uint32_t i);
PXC_API uint32_t pxMdsGetAnimationLayer(PxModelScript* mds, uint32_t i);
PXC_API const char* pxMdsGetAnimationNext(PxModelScript* mds, uint32_t i);
PXC_API  float pxMdsGetAnimationBlendIn(PxModelScript* mds, uint32_t i);
PXC_API  float pxMdsGetAnimationBlendOut(PxModelScript* mds, uint32_t i);
PXC_API  PxAnimationFlags pxMdsGetAnimationFlags(PxModelScript* mds, uint32_t i);
PXC_API  const char* pxMdsGetAnimationModel(PxModelScript* mds, uint32_t i);
PXC_API  PxAnimationDirection pxMdsGetAnimationDirection(PxModelScript* mds, uint32_t i);
PXC_API  int32_t pxMdsGetAnimationFirstFrame(PxModelScript* mds, uint32_t i);
PXC_API  int32_t pxMdsGetAnimationLastFrame(PxModelScript* mds, uint32_t i);
PXC_API  float pxMdsGetAnimationFps(PxModelScript* mds, uint32_t i);
PXC_API  float pxMdsGetAnimationSpeed(PxModelScript* mds, uint32_t i);
PXC_API  float pxMdsGetAnimationCollisionVolumeScale(PxModelScript* mds, uint32_t i);

// Animations -> EventTags
PXC_API uint32_t pxMdsGetAnimation_EventTagCount(PxModelScript* mds, uint32_t i);
PXC_API int32_t pxMdsGetAnimation_EventTagFrame(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex);
PXC_API PxEventTagType pxMdsGetAnimation_EventTagType(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex);
PXC_API const char* pxMdsGetAnimation_EventTagSlot(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex);
PXC_API const char* pxMdsGetAnimation_EventTagSlot2(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex);
PXC_API const char* pxMdsGetAnimation_EventTagItem(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex);
PXC_API int32_t* pxMdsGetAnimation_EventTagFrames(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex, uint32_t* size);
PXC_API PxEventFightMode pxMdsGetAnimation_EventTagFightMode(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex);
PXC_API bool pxMdsGetAnimation_EventTagAttached(PxModelScript* mds, uint32_t animIndex, uint32_t eventTagIndex);

// Animations -> EventPfx
PXC_API uint32_t pxMdsGetAnimation_EventPfxCount(PxModelScript* mds, uint32_t i);
PXC_API int32_t pxMdsGetAnimation_EventPfxFrame(PxModelScript* mds, uint32_t animIndex, uint32_t eventIndex);
PXC_API int32_t pxMdsGetAnimation_EventPfxIndex(PxModelScript* mds, uint32_t animIndex, uint32_t eventIndex);
PXC_API const char* pxMdsGetAnimation_EventPfxName(PxModelScript* mds, uint32_t animIndex, uint32_t eventIndex);
PXC_API const char* pxMdsGetAnimation_EventPfxPosition(PxModelScript* mds, uint32_t animIndex, uint32_t eventIndex);
PXC_API bool pxMdsGetAnimation_EventPfxAttached(PxModelScript* mds, uint32_t animIndex, uint32_t eventIndex);

// Animations -> PfxStop
PXC_API uint32_t pxMdsGetAnimation_EventPfxStopCount(PxModelScript* mds, uint32_t i);
PXC_API void pxMdsGetAnimation_EventPfxStop(PxModelScript* mds, uint32_t animIndex, uint32_t pfxStopIndex,
	int32_t* frame,
	int32_t* index);

// Animations -> Sfx
PXC_API uint32_t pxMdsGetAnimation_EventSfxCount(PxModelScript* mds, uint32_t i);
PXC_API int32_t pxMdsGetAnimation_EventSfxFrame(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);
PXC_API const char* pxMdsGetAnimation_EventSfxName(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);
PXC_API float pxMdsGetAnimation_EventSfxRange(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);
PXC_API bool pxMdsGetAnimation_EventSfxEmptySlot(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);

// Animations -> SfxGround
PXC_API  uint32_t pxMdsGetAnimationEventSfxGroundCount(PxModelScript* mds, uint32_t i);
PXC_API int32_t pxMdsGetAnimation_EventSfxGroundFrame(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);
PXC_API const char* pxMdsGetAnimation_EventSfxGroundName(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);
PXC_API float pxMdsGetAnimation_EventSfxGroundRange(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);
PXC_API bool pxMdsGetAnimation_EventSfxGroundEmptySlot(PxModelScript* mds, uint32_t animIndex, uint32_t sfxIndex);

// Animations -> EventMorphAnimate
PXC_API uint32_t pxMdsGetAnimation_EventMorphAnimateCount(PxModelScript* mds, uint32_t i);
PXC_API int32_t pxMdsGetAnimation_EventMorphAnimateFrame(PxModelScript* mds, uint32_t animIndex, uint32_t morphIndex);
PXC_API const char* pxMdsGetAnimation_EventMorphAnimateAnimation(PxModelScript* mds, uint32_t animIndex, uint32_t morphIndex);
PXC_API const char* pxMdsGetAnimation_EventMorphAnimateNode(PxModelScript* mds, uint32_t animIndex, uint32_t morphIndex);

// Animations -> EventCameraTremor
PXC_API uint32_t pxMdsGetAnimation_EventCameraTremorCount(PxModelScript* mds, uint32_t i);
PXC_API void pxMdsGetAnimation_EventCameraTremor(PxModelScript* mds, uint32_t animIndex, uint32_t tremorIndex,
	int32_t* frame,
	int32_t* field1,
	int32_t* field2,
	int32_t* field3,
	int32_t* field4);
