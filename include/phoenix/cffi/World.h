// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "BspTree.h"
#include "Buffer.h"
#include "Mesh.h"
#include "Vfs.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/world.hh>
typedef phoenix::world PxWorld;
typedef phoenix::vob PxVob;

	#include <phoenix/vobs/camera.hh>
typedef phoenix::vobs::camera_trj_frame PxVobCameraTrjFrame;
typedef phoenix::vobs::cs_camera PxVobCsCamera;

	#include <phoenix/vobs/light.hh>
typedef phoenix::vobs::light_preset PxVobLightPreset;
typedef phoenix::vobs::light PxVobLight;

	#include <phoenix/vobs/misc.hh>
typedef phoenix::vobs::animate PxVobAnimate;
typedef phoenix::vobs::item PxVobItem;
typedef phoenix::vobs::lens_flare PxVobLensFlare;
typedef phoenix::vobs::pfx_controller PxVobPfxController;
typedef phoenix::vobs::message_filter PxVobMessageFilter;
typedef phoenix::vobs::code_master PxVobCodeMaster;
typedef phoenix::vobs::mover_controller PxVobMoverController;
typedef phoenix::vobs::touch_damage PxVobTouchDamage;
typedef phoenix::vobs::earthquake PxVobEarthquake;
typedef phoenix::vobs::npc PxVobNpc;

	#include <phoenix/vobs/mob.hh>
typedef phoenix::vobs::mob PxVobMob;
typedef phoenix::vobs::mob_inter PxVobMobInter;
typedef phoenix::vobs::mob_fire PxVobMobFire;
typedef phoenix::vobs::mob_container PxVobMobContainer;
typedef phoenix::vobs::mob_door PxVobMobDoor;

	#include <phoenix/vobs/sound.hh>
typedef phoenix::vobs::sound PxVobSound;
typedef phoenix::vobs::sound_daytime PxVobSoundDaytime;

	#include <phoenix/vobs/trigger.hh>
typedef phoenix::vobs::trigger PxVobTrigger;
typedef phoenix::vobs::trigger_mover PxVobTriggerMover;
typedef phoenix::vobs::trigger_list PxVobTriggerList;
typedef phoenix::vobs::trigger_script PxVobTriggerScript;
typedef phoenix::vobs::trigger_change_level PxVobTriggerChangeLevel;
typedef phoenix::vobs::trigger_world_start PxVobTriggerWorldStart;
typedef phoenix::vobs::trigger_untouch PxVobTriggerUntouch;

	#include <phoenix/vobs/zone.hh>
typedef phoenix::vobs::zone_music PxVobZoneMusic;
typedef phoenix::vobs::zone_far_plane PxVobZoneFarPlane;
typedef phoenix::vobs::zone_fog PxVobZoneFog;
#else
typedef struct PxInternal_World PxWorld;
typedef struct PxInternal_WorldVob PxVob;

typedef struct PxInternal_WorldVobCameraTrjFrame PxVobCameraTrjFrame;
typedef struct PxInternal_WorldVobCsCamera PxVobCsCamera;

typedef struct PxInternal_WorldVobLightPreset PxVobLightPreset;
typedef struct PxInternal_WorldVobLight PxVobLight;

typedef struct PxInternal_WorldVobAnimate PxVobAnimate;
typedef struct PxInternal_WorldVobItem PxVobItem;
typedef struct PxInternal_WorldVobLensFlare PxVobLensFlare;
typedef struct PxInternal_WorldVobPfxController PxVobPfxController;
typedef struct PxInternal_WorldVobMessageFilter PxVobMessageFilter;
typedef struct PxInternal_WorldVobCodeMaster PxVobCodeMaster;
typedef struct PxInternal_WorldVobMoverController PxVobMoverController;
typedef struct PxInternal_WorldVobTouchDamage PxVobTouchDamage;
typedef struct PxInternal_WorldVobEarthquake PxVobEarthquake;
typedef struct PxInternal_WorldVobNpc PxVobNpc;

typedef struct PxInternal_WorldVobMob PxVobMob;
typedef struct PxInternal_WorldVobMobInter PxVobMobInter;
typedef struct PxInternal_WorldVobMobFire PxVobMobFire;
typedef struct PxInternal_WorldVobMobContainer PxVobMobContainer;
typedef struct PxInternal_WorldVobMobDoor PxVobMobDoor;

typedef struct PxInternal_WorldVobSound PxVobSound;
typedef struct PxInternal_WorldVobSoundDaytime PxVobSoundDaytime;

typedef struct PxInternal_WorldVobTrigger PxVobTrigger;
typedef struct PxInternal_WorldVobTriggerMover PxVobTriggerMover;
typedef struct PxInternal_WorldVobTriggerList PxVobTriggerList;
typedef struct PxInternal_WorldVobTriggerScript PxVobTriggerScript;
typedef struct PxInternal_WorldVobTriggerChangeLevel PxVobTriggerChangeLevel;
typedef struct PxInternal_WorldVobTriggerWorldStart PxVobTriggerWorldStart;
typedef struct PxInternal_WorldVobTriggerUntouch PxVobTriggerUntouch;

typedef struct PxInternal_WorldVobZoneMusic PxVobZoneMusic;
typedef struct PxInternal_WorldVobZoneFarPlane PxVobZoneFarPlane;
typedef struct PxInternal_WorldVobZoneFog PxVobZoneFog;
#endif

typedef enum {
	PxVob_zCVob = 0,
	PxVob_zCVobLevelCompo = 1,
	PxVob_oCItem = 2,
	PxVob_oCNpc = 3,
	PxVob_zCMoverController = 4,
	PxVob_zCVobScreenFX = 5,
	PxVob_zCVobStair = 6,
	PxVob_zCPFXController = 7,
	PxVob_zCVobAnimate = 8,
	PxVob_zCVobLensFlare = 9,
	PxVob_zCVobLight = 10,
	PxVob_zCVobSpot = 11,
	PxVob_zCVobStartpoint = 12,
	PxVob_zCMessageFilter = 13,
	PxVob_zCCodeMaster = 14,
	PxVob_zCTriggerWorldStart = 15,
	PxVob_zCCSCamera = 16,
	PxVob_zCCamTrj_KeyFrame = 17,
	PxVob_oCTouchDamage = 18,
	PxVob_zCTriggerUntouch = 19,
	PxVob_zCEarthquake = 20,
	PxVob_oCMOB = 21,
	PxVob_oCMobInter = 22,
	PxVob_oCMobBed = 23,
	PxVob_oCMobFire = 24,
	PxVob_oCMobLadder = 25,
	PxVob_oCMobSwitch = 26,
	PxVob_oCMobWheel = 27,
	PxVob_oCMobContainer = 28,
	PxVob_oCMobDoor = 29,
	PxVob_zCTrigger = 30,
	PxVob_zCTriggerList = 31,
	PxVob_oCTriggerScript = 32,
	PxVob_oCTriggerChangeLevel = 33,
	PxVob_oCCSTrigger = 34,
	PxVob_zCMover = 35,
	PxVob_zCVobSound = 36,
	PxVob_zCVobSoundDaytime = 37,
	PxVob_oCZoneMusic = 38,
	PxVob_oCZoneMusicDefault = 39,
	PxVob_zCZoneZFog = 40,
	PxVob_zCZoneZFogDefault = 41,
	PxVob_zCZoneVobFarPlane = 42,
	PxVob_zCZoneVobFarPlaneDefault = 43,
	PxVob_ignored = 44,
	PxVob_unknown = 45,
} PxVobType;

typedef enum {
	PxVobLightModePoint = 0,
	PxVobLightModeSpot = 1,
	PxVobLightModeReserved0 = 2,
	PxVobLightModeReserved1 = 3,
} PxVobLightMode;

typedef enum {
	PxVobLightQualityHigh = 0,
	PxVobLightQualityMedium = 1,
	PxVobLightQualityLow = 2,
} PxVobLightQuality;

typedef enum {
	PxVobShadowNone = 0,
	PxVobShadowBlob = 1,
} PxVobShadowMode;

typedef enum {
	PxVobAnimationNone = 0,
	PxVobAnimationWind = 1,
	PxVobAnimationWind2 = 2,
} PxVobAnimationMode;

typedef enum {
	PxVobSpriteAlignNone = 0,
	PxVobSpriteAlignYaw = 1,
	PxVobSpriteAlignFull = 2,
} PxVobSpriteAlignment;

typedef enum {
	PxVobVisualDecal = 0,               ///< The VOb presents as a decal.
	PxVobVisualMesh = 1,                ///< The VOb presents a PxMesh.
	PxVobVisualMultiResolutionMesh = 2, ///< The VOb presents a PxMultiResolutionMesh.
	PxVobVisualParticleSystem = 3,      ///< The VOb presents as a particle system.
	PxVobVisualAiCamera = 4,            ///< The VOb is a game-controlled camera.
	PxVobVisualModel = 5,               ///< The VOb presents a PxModel.
	PxVobVisualMorphMesh = 6,           ///< The VOb presents a PxMorphMesh.
	PxVobVisualUnknown = 7,             ///< The VOb presents an unknown visual or no visual at all.
} PxVobVisualType;

typedef enum {
	PxVobMobSoundWood = 0,
	PxVobMobSoundStone = 1,
	PxVobMobSoundMetal = 2,
	PxVobMobSoundLeather = 3,
	PxVobMobSoundClay = 4,
	PxVobMobSoundGlass = 5,
} PxVobMobSoundMaterial;

typedef enum {
	PxVobSoundModeLoop = 0,   ///< The sound should be player forever until the player exits the trigger volume.
	PxVobSoundModeOnce = 1,   ///< The sound should be played once when the player enters the trigger volume.
	PxVobSoundModeRandom = 2, ///< While the player is in the trigger volume, the should should play randomly.
} PxVobSoundMode;

typedef enum {
	PxVobSoundTriggerVolumeSpherical = 0, ///< The sound is triggered when the player enters a spherical area around the
	                                      ///< VOb indicated by its radius setting.
	PxVobSoundTriggerVolumeEllipsoidal = 1, ///< The sound is triggered when the player enters a ellipsoidal area around
	                                        ///< the VOb indicated by its radius setting.
} PxVobSoundTriggerVolume;

typedef enum {
	PxVobTriggerMoverBehaviourToggle = 0,
	PxVobTriggerMoverBehaviourTriggerControl = 1,
	PxVobTriggerMoverBehaviourOpenTimed = 2,
	PxVobTriggerMoverBehaviourLoop = 3,
	PxVobTriggerMoverBehaviourSingleKeys = 4,
} PxVobTriggerMoverBehaviour;

typedef enum {
	PxVobTriggerMoverLerpModeCurve = 0,
	PxVobTriggerMoverLerpModeLinear = 1,
} PxVobTriggerMoverLerpMode;

typedef enum {
	PxVobTriggerMoverSpeedModeSegConstant = 0,
	PxVobTriggerMoverSpeedModeSlowStartEnd = 1,
	PxVobTriggerMoverSpeedModeSlowStart = 2,
	PxVobTriggerMoverSpeedModeSlowEnd = 3,
	PxVobTriggerMoverSpeedModeSegSlowStarEnd = 4,
	PxVobTriggerMoverSpeedModeSegSlowStart = 5,
	PxVobTriggerMoverSpeedModeSegSlowEnd = 6,

} PxVobTriggerMoverSpeedMode;

typedef enum {
	PxVobTriggerBatchModeAll = 0,
	PxVobTriggerBatchModeNext = 1,
	PxVobTriggerBatchModeRandom = 2,
} PxVobTriggerBatchMode;

PXC_API PxWorld* pxWorldLoad(PxBuffer* buffer);
PXC_API PxWorld* pxWorldLoadFromVfs(PxVfs const* vfs, char const* name);
PXC_API void pxWorldDestroy(PxWorld* world);

PXC_API PxBspTree const* pxWorldGetBspTree(PxWorld const* world);
PXC_API PxMesh const* pxWorldGetMesh(PxWorld const* world);
PXC_API uint32_t pxWorldGetWayPointCount(PxWorld const* world);
PXC_API void pxWorldGetWayPoint(PxWorld const* world,
                                uint32_t i,
                                char const** name,
                                PxVec3* position,
                                PxVec3* direction,
                                PxBool* freePoint,
                                PxBool* underwater,
                                int32_t* waterDepth);
PXC_API uint32_t pxWorldGetWayEdgeCount(PxWorld const* world);
PXC_API void pxWorldGetWayEdge(PxWorld const* world, uint32_t i, uint32_t* a, uint32_t* b);

PXC_API uint32_t pxWorldGetRootVobCount(PxWorld const* world);
PXC_API PxVob* pxWorldGetRootVob(PxWorld const* world, uint32_t i);

PXC_API PxVobType pxVobGetType(PxVob const* vob);
PXC_API uint32_t pxVobGetId(PxVob const* vob);
PXC_API PxAABB pxVobGetBbox(PxVob const* vob);
PXC_API PxVec3 pxVobGetPosition(PxVob const* vob);
PXC_API PxMat3x3 pxVobGetRotation(PxVob const* vob); ///< IMPORTANT: This matrix is column-major column order!
PXC_API PxBool pxVobGetShowVisual(PxVob const* vob);
PXC_API PxVobSpriteAlignment pxVobGetSpriteAlignment(PxVob const* vob);
PXC_API PxBool pxVobGetCdStatic(PxVob const* vob);
PXC_API PxBool pxVobGetCdDynamic(PxVob const* vob);
PXC_API PxBool pxVobGetVobStatic(PxVob const* vob);
PXC_API PxVobShadowMode pxVobGetShadowMode(PxVob const* vob);
PXC_API PxBool pxVobGetPhysicsEnabled(PxVob const* vob);
PXC_API PxVobAnimationMode pxVobGetAnimationMode(PxVob const* vob);
PXC_API int32_t pxVobGetBias(PxVob const* vob);
PXC_API PxBool pxVobGetAmbient(PxVob const* vob);
PXC_API float pxVobGetAnimationStrength(PxVob const* vob);
PXC_API float pxVobGetFarClipScale(PxVob const* vob);
PXC_API char const* pxVobGetPresetName(PxVob const* vob);
PXC_API char const* pxVobGetVobName(PxVob const* vob);
PXC_API char const* pxVobGetVisualName(PxVob const* vob);
PXC_API PxVobVisualType pxVobGetVisualType(PxVob const* vob);

// TODO: saved

PXC_API uint32_t pxVobGetChildCount(PxVob const* vob);
PXC_API PxVob* pxVobGetChild(PxVob const* vob, uint32_t i);

// Decal
PXC_API PxBool pxVobGetGetHasDecal(PxVob const* vob);
PXC_API char const* pxVobGetDecalName(PxVob const* vob);
PXC_API PxVec2 pxVobGetDecalDimension(PxVob const* vob);
PXC_API PxVec2 pxVobGetDecalOffset(PxVob const* vob);
PXC_API PxBool pxVobGetDecalTwoSided(PxVob const* vob);
PXC_API PxMaterialAlphaFunction pxVobGetDecalAlphaFunc(PxVob const* vob);
PXC_API float pxVobGetDecalTextureAnimFps(PxVob const* vob);
PXC_API uint8_t pxVobGetDecalAlphaWeight(PxVob const* vob);
PXC_API PxBool pxVobGetDecalIgnoreDaylight(PxVob const* vob);

// TODO Vob - Camera

// Light Preset
PXC_API char const* pxLightPresetGetPreset(PxVobLightPreset const* lightPreset);
PXC_API PxVobLightMode pxLightPresetGetLightType(PxVobLightPreset const* lightPreset);
PXC_API float pxLightPresetGetRange(PxVobLightPreset const* lightPreset);
PXC_API PxColor pxLightPresetGetColor(PxVobLightPreset const* lightPreset);
PXC_API float pxLightPresetGetConeAngle(PxVobLightPreset const* lightPreset);
PXC_API PxBool pxLightPresetGetIsStatic(PxVobLightPreset const* lightPreset);
PXC_API PxVobLightQuality pxLightPresetGetQuality(PxVobLightPreset const* lightPreset);
PXC_API char const* pxLightPresetGetLensFlareFx(PxVobLight const* light);
PXC_API PxBool pxLightPresetGetOn(PxVobLightPreset const* lightPreset);
PXC_API uint32_t pxLightPresetGetRangeAnimationScaleCount(PxVobLightPreset const* lightPreset);
PXC_API float pxLightPresetGetRangeAnimationScale(PxVobLightPreset const* lightPreset, uint32_t i);
PXC_API float pxLightPresetGetRangeAnimationFps(PxVobLightPreset const* lightPreset);
PXC_API PxBool pxLightPresetGetRangeAnimationSmooth(PxVobLightPreset const* lightPreset);
PXC_API uint32_t pxLightPresetGetColorAnimationListCount(PxVobLightPreset const* lightPreset);
PXC_API PxColor pxLightPresetGetColorAnimationList(PxVobLightPreset const* lightPreset, uint32_t i);
PXC_API float pxLightPresetGetColorAnimationFps(PxVobLightPreset const* lightPreset);
PXC_API PxBool pxLightPresetGetColorAnimationSmooth(PxVobLightPreset const* lightPreset);
PXC_API PxBool pxLightPresetGetCanMove(PxVobLightPreset const* lightPreset);

// Vob - Light
PXC_API char const* pxVobLightGetPreset(PxVobLight const* light);
PXC_API PxVobLightMode pxVobLightGetLightType(PxVobLight const* light);
PXC_API float pxVobLightGetRange(PxVobLight const* light);
PXC_API PxColor pxVobLightGetColor(PxVobLight const* light);
PXC_API float pxVobLightGetConeAngle(PxVobLight const* light);
PXC_API PxBool pxVobLightGetIsStatic(PxVobLight const* light);
PXC_API PxVobLightQuality pxVobLightGetQuality(PxVobLight const* light);
PXC_API char const* pxVobLightGetLensFlareFx(PxVobLight const* light);
PXC_API PxBool pxVobLightGetOn(PxVobLight const* light);
PXC_API uint32_t pxVobLightGetRangeAnimationScaleCount(PxVobLight const* light);
PXC_API float pxVobLightGetRangeAnimationScale(PxVobLight const* light, uint32_t i);
PXC_API float pxVobLightGetRangeAnimationFps(PxVobLight const* light);
PXC_API PxBool pxVobLightGetRangeAnimationSmooth(PxVobLight const* light);
PXC_API uint32_t pxVobLightGetColorAnimationListCount(PxVobLight const* light);
PXC_API PxColor pxVobLightGetColorAnimationList(PxVobLight const* light, uint32_t i);
PXC_API float pxVobLightGetColorAnimationFps(PxVobLight const* light);
PXC_API PxBool pxVobLightGetColorAnimationSmooth(PxVobLight const* light);
PXC_API PxBool pxVobLightGetCanMove(PxVobLight const* light);

// Vob - Animate
PXC_API PxBool pxVobAnimateGetStartOn(PxVobAnimate const* animate);

// Vob - Item
PXC_API char const* pxVobItemGetInstance(PxVobItem const* item);

// Vob - Lens Flare
PXC_API char const* pxVobLensFlareGetFx(PxVobLensFlare const* lensFlare);

// Vob - Pfx Controller
PXC_API char const* pxVobPfxControllerGetPfxName(PxVobPfxController const* pfxController);
PXC_API PxBool pxVobPfxControllerGetKillWhenDone(PxVobPfxController const* pfxController);
PXC_API PxBool pxVobPfxControllerGetInitiallyRunning(PxVobPfxController const* pfxController);

// Vob - Message Filter
PXC_API char const* pxVobMessageFilterGetTarget(PxVobMessageFilter const* messageFilter);
PXC_API uint32_t pxVobMessageFilterGetOnTrigger(PxVobMessageFilter const* messageFilter);
PXC_API uint32_t pxVobMessageFilterGetOnUntrigger(PxVobMessageFilter const* messageFilter);

// Vob - Code Master
PXC_API char const* pxVobCodeMasterGetTarget(PxVobCodeMaster const* codeMaster);
PXC_API PxBool pxVobCodeMasterGetOrdered(PxVobCodeMaster const* codeMaster);
PXC_API PxBool pxVobCodeMasterGetFirstFalseIsFailure(PxVobCodeMaster const* codeMaster);
PXC_API char const* pxVobCodeMasterGetFailureTarget(PxVobCodeMaster const* codeMaster);
PXC_API PxBool pxVobCodeMasterGetUntriggeredCancels(PxVobCodeMaster const* codeMaster);
PXC_API uint32_t pxVobCodeMasterGetSlavesCount(PxVobCodeMaster const* codeMaster);
PXC_API char const* pxVobCodeMasterGetSlaves(PxVobCodeMaster const* codeMaster, uint32_t i);

// Vob - Mover Controller
PXC_API char const* pxVobMoverControllerGetTarget(PxVobMoverController const* moverController);
PXC_API uint32_t pxVobMoverControllerGetMessage(PxVobMoverController const* moverController);
PXC_API int32_t pxVobMoverControllerGetKey(PxVobMoverController const* moverController);

// Vob - Touch Damage
PXC_API float pxVobTouchDamageGetDamage(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetBarrier(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetBlunt(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetEdge(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetFire(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetFly(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetMagic(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetPoint(PxVobTouchDamage const* touchDamage);
PXC_API PxBool pxVobTouchDamageGetFall(PxVobTouchDamage const* touchDamage);
PXC_API float pxVobTouchDamageGetRepearDelaySec(PxVobTouchDamage const* touchDamage);
PXC_API float pxVobTouchDamageGetVolumeScale(PxVobTouchDamage const* touchDamage);
PXC_API uint32_t pxVobTouchDamageGetCollision(PxVobTouchDamage const* touchDamage);

// Vob - Earthquake
PXC_API float pxVobEarthquakeGetRadius(PxVobEarthquake const* earthquake);
PXC_API float pxVobEarthquakeGetDuration(PxVobEarthquake const* earthquake);
PXC_API PxVec3 pxVobEarthquakeGetAmplitude(PxVobEarthquake const* earthquake);

// Vob - Npc
PXC_API char const* pxVobNpcGetNpcInstance(PxVobNpc const* npc);
PXC_API PxVec3 pxVobNpcGetModelScale(PxVobNpc const* npc);
PXC_API float pxVobNpcGetModelFatness(PxVobNpc const* npc);
PXC_API uint32_t pxVobNpcGetOverlaysCount(PxVobNpc const* npc);
PXC_API char const* pxVobNpcGetOverlays(PxVobNpc const* npc, uint32_t i);
PXC_API int pxVobNpcGetFlags(PxVobNpc const* npc);
PXC_API int pxVobNpcGetGuild(PxVobNpc const* npc);
PXC_API int pxVobNpcGetGuildTrue(PxVobNpc const* npc);
PXC_API int pxVobNpcGetLevel(PxVobNpc const* npc);
PXC_API int pxVobNpcGetXp(PxVobNpc const* npc);
PXC_API int pxVobNpcGetXpNextLevel(PxVobNpc const* npc);
PXC_API int pxVobNpcGetLp(PxVobNpc const* npc);
PXC_API uint32_t pxVobNpcGetTalentsCount(PxVobNpc const* npc);
PXC_API void pxVobNpcGetTalents(PxVobNpc const* npc, uint32_t i, int* talent, int* value, int* skill);
PXC_API int pxVobNpcGetFightTactic(PxVobNpc const* npc);
PXC_API int pxVobNpcGetFightMode(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetWounded(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetMad(PxVobNpc const* npc);
PXC_API int pxVobNpcGetMadTime(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetPlayer(PxVobNpc const* npc);
PXC_API uint32_t pxVobNpcGetAttributesCount(PxVobNpc const* npc);
PXC_API int pxVobNpcGetAttributes(PxVobNpc const* npc, uint32_t i);
PXC_API uint32_t pxVobNpcGetHcsCount(PxVobNpc const* npc);
PXC_API int pxVobNpcGetHcs(PxVobNpc const* npc, uint32_t i);
PXC_API uint32_t pxVobNpcGetMissionsCount(PxVobNpc const* npc);
PXC_API int pxVobNpcGetMissions(PxVobNpc const* npc, uint32_t i);
PXC_API char const* pxVobNpcGetStartAiState(PxVobNpc const* npc);
PXC_API uint32_t pxVobNpcGetAivarCount(PxVobNpc const* npc);
PXC_API int pxVobNpcGetAivar(PxVobNpc const* npc, uint32_t i);
PXC_API char const* pxVobNpcGetScriptWaypoint(PxVobNpc const* npc);
PXC_API int pxVobNpcGetAttitude(PxVobNpc const* npc);
PXC_API int pxVobNpcGetAttitudeTemp(PxVobNpc const* npc);
PXC_API int pxVobNpcGetNameNr(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetMoveLock(PxVobNpc const* npc);
PXC_API uint32_t pxVobNpcGetPackedCount(PxVobNpc const* npc);
PXC_API char const* pxVobNpcGetPacked(PxVobNpc const* npc, uint32_t i);
PXC_API uint32_t pxVobNpcGetItemsCount(PxVobNpc const* npc);
PXC_API PxVobItem const* pxVobNpcGetItems(PxVobNpc const* npc, uint32_t i);
PXC_API uint32_t pxVobNpcGetSlotsCount(PxVobNpc const* npc);
PXC_API void
pxVobNpcGetSlots(PxVobNpc const* npc, uint32_t i, PxBool* used, char const** name, int* itemIndex, PxBool* inInventory);
PXC_API PxBool pxVobNpcGetCurrentStateValid(PxVobNpc const* npc);
PXC_API char const* pxVobNpcGetCurrentStateName(PxVobNpc const* npc);
PXC_API int pxVobNpcGetCurrentStateIndex(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetCurrentStateIsRoutine(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetNextStateValid(PxVobNpc const* npc);
PXC_API char const* pxVobNpcGetNextStateName(PxVobNpc const* npc);
PXC_API int pxVobNpcGetNextStateIndex(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetNextStateIsRoutine(PxVobNpc const* npc);
PXC_API int pxVobNpcGetLastAiState(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetHasRoutine(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetRoutineChanged(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetRoutineOverlay(PxVobNpc const* npc);
PXC_API int pxVobNpcGetRoutineOverlayCount(PxVobNpc const* npc);
PXC_API int pxVobNpcGetWalkmodeRoutine(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetWeaponmodeRoutine(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetStartNewRoutine(PxVobNpc const* npc);
PXC_API int pxVobNpcGetAiStateDriven(PxVobNpc const* npc);
PXC_API PxVec3 pxVobNpcGetAiStatePos(PxVobNpc const* npc);
PXC_API char const* pxVobNpcGetCurrentRoutine(PxVobNpc const* npc);
PXC_API PxBool pxVobNpcGetRespawn(PxVobNpc const* npc);
PXC_API int pxVobNpcGetRespawnTime(PxVobNpc const* npc);
PXC_API uint32_t pxVobNpcGetProtectionCount(PxVobNpc const* npc);
PXC_API int pxVobNpcGetProtection(PxVobNpc const* npc, uint32_t i);
PXC_API int pxVobNpcGetBsInterruptableOverride(PxVobNpc const* npc);
PXC_API int pxVobNpcGetNpcType(PxVobNpc const* npc);
PXC_API int pxVobNpcGetSpellMana(PxVobNpc const* npc);

// Vob - Mob
PXC_API char const* pxVobMobGetName(PxVobMob const* mob);
PXC_API int32_t pxVobMobGetHp(PxVobMob const* mob);
PXC_API int32_t pxVobMobGetDamage(PxVobMob const* mob);
PXC_API PxBool pxVobMobGetMovable(PxVobMob const* mob);
PXC_API PxBool pxVobMobGetTakable(PxVobMob const* mob);
PXC_API PxBool pxVobMobGetFocusOverride(PxVobMob const* mob);
PXC_API PxVobMobSoundMaterial pxVobMobGetMaterial(PxVobMob const* mob);
PXC_API char const* pxVobMobGetVisualDestroyed(PxVobMob const* mob);
PXC_API char const* pxVobMobGetOwner(PxVobMob const* mob);
PXC_API char const* pxVobMobGetOwnerGuild(PxVobMob const* mob);
PXC_API PxBool pxVobMobGetDestroyed(PxVobMob const* mob);
// Vob - MobInter
PXC_API int32_t pxVobMobInterGetState(PxVobMobInter const* mobInter);
PXC_API char const* pxVobMobInterGetTarget(PxVobMobInter const* mobInter);
PXC_API char const* pxVobMobInterGetItem(PxVobMobInter const* mobInter);
PXC_API char const* pxVobMobInterGetConditionFunction(PxVobMobInter const* mobInter);
PXC_API char const* pxVobMobInterGetOnStateChangeFunction(PxVobMobInter const* mobInter);
PXC_API PxBool pxVobMobInterGetRewind(PxVobMobInter const* mobInter);
// Vob - MobFire
PXC_API char const* pxVobMobFireGetSlot(PxVobMobFire const* mobFire);
PXC_API char const* pxVobMobFireGetVobTree(PxVobMobFire const* mobFire);
// Vob - MobContainer
PXC_API PxBool pxVobMobContainerGetLocked(PxVobMobContainer const* mobContainer);
PXC_API char const* pxVobMobContainerGetKey(PxVobMobContainer const* mobContainer);
PXC_API char const* pxVobMobContainerGetPickString(PxVobMobContainer const* mobContainer);
PXC_API char const* pxVobMobContainerGetContents(PxVobMobContainer const* mobContainer);
// Vob - MobDoor
PXC_API PxBool pxVobMobDoorGetLocked(PxVobMobDoor const* mobDoor);
PXC_API char const* pxVobMobDoorGetKey(PxVobMobDoor const* mobDoor);
PXC_API char const* pxVobMobDoorGetPickString(PxVobMobDoor const* mobDoor);

// Vob - Sound
PXC_API float pxVobSoundGetVolume(PxVobSound const* sound);
PXC_API PxVobSoundMode pxVobSoundGetSoundMode(PxVobSound const* sound);
PXC_API float pxVobSoundGetRandomDelay(PxVobSound const* sound);
PXC_API float pxVobSoundGetRandomDelayVar(PxVobSound const* sound);
PXC_API PxBool pxVobSoundGetInitiallyPlaying(PxVobSound const* sound);
PXC_API PxBool pxVobSoundGetAmbient3d(PxVobSound const* sound);
PXC_API PxBool pxVobSoundGetObstruction(PxVobSound const* sound);
PXC_API float pxVobSoundGetConeAngle(PxVobSound const* sound);
PXC_API PxVobSoundTriggerVolume pxVobSoundGetSoundTriggerVolume(PxVobSound const* sound);
PXC_API float pxVobSoundGetRadius(PxVobSound const* sound);
PXC_API char const* pxVobSoundGetSoundName(PxVobSound const* sound);
// Vob - SoundDaytime
PXC_API float pxVobSoundDaytimeStartTime(PxVobSoundDaytime const* soundDaytime);
PXC_API float pxVobSoundDaytimeEndTime(PxVobSoundDaytime const* soundDaytime);
PXC_API char const* pxVobSoundDaytimeSoundName2(PxVobSoundDaytime const* soundDaytime);

// TODO Vob properties - Trigger

// Trigger
PXC_API char const* pxVobTriggerGetTarget(PxVobTrigger const* trigger);
PXC_API uint8_t pxVobTriggerGetFlags(PxVobTrigger const* trigger);
PXC_API uint8_t pxVobTriggerGetFilterFlags(PxVobTrigger const* trigger);
PXC_API char const* pxVobTriggerGetVobTarget(PxVobTrigger const* trigger);
PXC_API int32_t pxVobTriggerGetMaxActivationCount(PxVobTrigger const* trigger);
PXC_API float pxVobTriggerGetRetriggerDelaySec(PxVobTrigger const* trigger);
PXC_API float pxVobTriggerGetDamageThreshold(PxVobTrigger const* trigger);
PXC_API float pxVobTriggerGetFireDelaySec(PxVobTrigger const* trigger);
// Trigger save-game only variables
PXC_API float pxVobTriggerGetSNextTimeTriggerable(PxVobTrigger const* trigger);
PXC_API int pxVobTriggerGetSCountCanBeActivated(PxVobTrigger const* trigger);
PXC_API PxBool pxVobTriggerGetSIsEnabled(PxVobTrigger const* trigger);

// Trigger - Mover
PXC_API PxVobTriggerMoverBehaviour pxVobTriggerMoverGetBehaviour(PxVobTriggerMover const* trigger);
PXC_API float pxVobTriggerMoverGetTouchBlockerDamage(PxVobTriggerMover const* trigger);
PXC_API float pxVobTriggerMoverGetStayOpenTimeSec(PxVobTriggerMover const* trigger);
PXC_API PxBool pxVobTriggerMoverGetLocked(PxVobTriggerMover const* trigger);
PXC_API PxBool pxVobTriggerMoverGetAutoLink(PxVobTriggerMover const* trigger);
PXC_API PxBool pxVobTriggerMoverGetAutoRotate(PxVobTriggerMover const* trigger);
PXC_API float pxVobTriggerMoverGetSpeed(PxVobTriggerMover const* trigger);
PXC_API PxVobTriggerMoverLerpMode pxVobTriggerMoverGetLerpMode(PxVobTriggerMover const* trigger);
PXC_API PxVobTriggerMoverSpeedMode pxVobTriggerMoverGetSpeedMode(PxVobTriggerMover const* trigger);
PXC_API uint32_t pxVobTriggerMoverGetKeyframeCount(PxVobTriggerMover const* trigger);
PXC_API void
pxVobTriggerMoverGetKeyframe(PxVobTriggerMover const* trigger, uint32_t i, PxVec3* position, PxQuat* rotation);
PXC_API char const* pxVobTriggerMoverGetSfxOpenStart(PxVobTriggerMover const* trigger);
PXC_API char const* pxVobTriggerMoverGetSfxOpenEnd(PxVobTriggerMover const* trigger);
PXC_API char const* pxVobTriggerMoverGetSfxTransitioning(PxVobTriggerMover const* trigger);
PXC_API char const* pxVobTriggerMoverGetSfxCloseStart(PxVobTriggerMover const* trigger);
PXC_API char const* pxVobTriggerMoverGetSfxCloseEnd(PxVobTriggerMover const* trigger);
PXC_API char const* pxVobTriggerMoverGetSfxLock(PxVobTriggerMover const* trigger);
PXC_API char const* pxVobTriggerMoverGetSfxUnlock(PxVobTriggerMover const* trigger);
PXC_API char const* pxVobTriggerMoverGetSfxUseLocked(PxVobTriggerMover const* trigger);
// Trigger - Mover save-game only variables
PXC_API PxVec3 pxVobTriggerMoverGetSActKeyPosDelta(PxVobTriggerMover const* trigger);
PXC_API float pxVobTriggerMoverGetSActKeyframeF(PxVobTriggerMover const* trigger);
PXC_API int pxVobTriggerMoverGetSActKeyframe(PxVobTriggerMover const* trigger);
PXC_API int pxVobTriggerMoverGetSNextKeyFrame(PxVobTriggerMover const* trigger);
PXC_API float pxVobTriggerMoverGetMoveSpeedUnit(PxVobTriggerMover const* trigger);
PXC_API float pxVobTriggerMoverGetSAdvanceDir(PxVobTriggerMover const* trigger);
PXC_API uint32_t pxVobTriggerMoverGetSMoverState(PxVobTriggerMover const* trigger);
PXC_API int pxVobTriggerMoverGetSTriggerEventCount(PxVobTriggerMover const* trigger);
PXC_API float pxVobTriggerMoverGetSStayOpenTimeDest(PxVobTriggerMover const* trigger);

// Trigger - List
PXC_API PxVobTriggerBatchMode pxVobTriggerListGetTriggerBatchMode(PxVobTriggerList const* trigger);
PXC_API uint32_t pxVobTriggerListGetTargetsCount(PxVobTriggerList const* trigger);
PXC_API char const* pxVobTriggerListGetTargetName(PxVobTriggerList const* trigger, uint32_t i);
PXC_API float pxVobTriggerListGetTargetDelay(PxVobTriggerList const* trigger, uint32_t i);
// Trigger - List save-game only variables
PXC_API uint8_t pxVobTriggerListGetSActTarget(PxVobTriggerList const* trigger);
PXC_API PxBool pxVobTriggerListGetSSendOnTrigger(PxVobTriggerList const* trigger);

// Trigger - Script
PXC_API char const* pxVobTriggerScriptGetFunction(PxVobTriggerScript const* trigger);

// Trigger - Change Level
PXC_API char const* pxVobTriggerChangeLevelGetLevelName(PxVobTriggerChangeLevel const* trigger);
PXC_API char const* pxVobTriggerChangeLevelGetStartVob(PxVobTriggerChangeLevel const* trigger);

// Trigger - World Start
PXC_API char const* pxVobTriggerWorldStartGetTarget(PxVobTriggerWorldStart const* trigger);
PXC_API PxBool pxVobTriggerWorldStartGetFireOnce(PxVobTriggerWorldStart const* trigger);
// Trigger - World Start save-game only variables
PXC_API PxBool pxVobTriggerWorldStartGetSHasFired(PxVobTriggerWorldStart const* trigger);

// Trigger - Untouch
PXC_API char const* pxVobTriggerUntouchGetTarget(PxVobTriggerUntouch const* trigger);

// Vob - ZoneMusic
PXC_API void pxWorldVobGetZoneMusic(PxVobZoneMusic const* zoneMusic,
                                    PxBool* enabled,
                                    int32_t* priority,
                                    PxBool* ellipsoid,
                                    float* reverb,
                                    float* volume,
                                    PxBool* loop);
// Vob - ZoneFarPlane
PXC_API void
pxWorldVobGetZoneFarPlane(PxVobZoneFarPlane* zoneFarPlane, float* vob_far_plane_z, float* inner_range_percentage);
// Vob - ZoneFog
PXC_API void pxWorldVobGetZoneFog(PxVobZoneFog* zoneFog,
                                  float* range_center,
                                  float* inner_range_percentage,
                                  PxColor* color,
                                  PxBool* fade_out_sky,
                                  PxBool* override_color);
