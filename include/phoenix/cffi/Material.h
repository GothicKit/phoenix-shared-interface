// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/material.hh>
typedef phoenix::material PxMaterial;
#else
typedef struct PxInternal_Material PxMaterial;
#endif

typedef enum {
	PxMaterialGroup_Undefined = 0,
	PxMaterialGroup_Metal = 1,
	PxMaterialGroup_Stone = 2,
	PxMaterialGroup_Wood = 3,
	PxMaterialGroup_Earth = 4,
	PxMaterialGroup_Water = 5,
	PxMaterialGroup_Snow = 6,

	/// \brief The material group is explicitly not set. Added for [OpenGothic](https://github.com/Try/OpenGothic)
	///        compatibility. It does not exist in real Gothic or Gothic 2 materials.
	PxMaterialGroup_None = 0xFF,
} PxMaterialGroup;

typedef enum {
	PxMaterialAnimMap_None = 0,
	PxMaterialAnimMap_Linear = 1,
} PxMaterialAnimationMappingMode;

typedef enum {
	PxMaterialWaveMode_None = 0,
	PxMaterialWaveMode_AmbientGround = 1,
	PxMaterialWaveMode_Ground = 2,
	PxMaterialWaveMode_AmbientWall = 3,
	PxMaterialWaveMode_Wall = 4,
	PxMaterialWaveMode_Env = 5,
	PxMaterialWaveMode_AmbientWind = 6,
	PxMaterialWaveMode_Wind = 7,
} PxMaterialWaveModeType;

typedef enum {
	PxMaterialWaveSpeed_None = 0,
	PxMaterialWaveSpeed_Slow = 1,
	PxMaterialWaveSpeed_Normal = 2,
	PxMaterialWaveSpeed_Fast = 3,
} PxMaterialWaveSpeedType;

typedef enum {
	PxMaterialAlpha_Default = 0,
	PxMaterialAlpha_None = 1,
	PxMaterialAlpha_Blend = 2,
	PxMaterialAlpha_Add = 3,
	PxMaterialAlpha_Sub = 4,
	PxMaterialAlpha_Mul = 5,
	PxMaterialAlpha_Mul2 = 6,
} PxMaterialAlphaFunction;

PXC_API char const* pxMatGetName(PxMaterial const* mat);
PXC_API PxMaterialGroup pxMatGetGroup(PxMaterial const* mat);
PXC_API uint32_t pxMatGetColor(PxMaterial const* mat);
PXC_API float pxMatGetSmoothAngle(PxMaterial const* mat);
PXC_API char const* pxMatGetTexture(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetTextureScale(PxMaterial const* mat);
PXC_API float pxMatGetTextureAnimFps(PxMaterial const* mat);
PXC_API PxMaterialAnimationMappingMode pxMatGetTextureAnimMapMode(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetTextureAnimMapDir(PxMaterial const* mat);
PXC_API PxBool pxMatGetDisableCollision(PxMaterial const* mat);
PXC_API PxBool pxMatGetDisableLightmap(PxMaterial const* mat);
PXC_API PxBool pxMatGetDontCollapse(PxMaterial const* mat);
PXC_API char const* pxMatGetDetailObject(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetDetailTextureScale(PxMaterial const* mat);
PXC_API PxBool pxMatGetForceOccluder(PxMaterial const* mat);
PXC_API PxBool pxMatGetEnvironmentMapping(PxMaterial const* mat);
PXC_API float pxMatGetEnvironmentMappingStrength(PxMaterial const* mat);
PXC_API PxMaterialWaveModeType pxMatGetWaveMode(PxMaterial const* mat);
PXC_API PxMaterialWaveSpeedType pxMatGetWaveSpeed(PxMaterial const* mat);
PXC_API float pxMatGetWaveMaxAmplitude(PxMaterial const* mat);
PXC_API float pxMatGetWaveGridSize(PxMaterial const* mat);
PXC_API PxBool pxMatGetIgnoreSun(PxMaterial const* mat);
PXC_API PxMaterialAlphaFunction pxMatGetAlphaFunc(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetDefaultMapping(PxMaterial const* mat);
