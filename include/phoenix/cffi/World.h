// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Mesh.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/world.hh>
typedef phoenix::world PxWorld;
typedef phoenix::vob PxVob;
#else
typedef struct PxInternal_World PxWorld;
typedef struct PxInternal_WorldVob PxVob;
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

// TODO
PXC_API PxWorld* pxWorldLoad(PxBuffer* buffer);
PXC_API PxWorld* pxWorldLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxWorldDestroy(PxWorld* world);

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
PXC_API PxMat3 pxVobGetRotation(PxVob const* vob); ///< IMPORTANT: This matrix is column-major column order!
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
// TODO: decal
// TODO: saved
PXC_API uint32_t pxVobGetChildCount(PxVob const* vob);
PXC_API PxVob* pxVobGetChild(PxVob const* vob, uint32_t i);
