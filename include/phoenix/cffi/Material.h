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

PXC_API char const* pxMatGetName(PxMaterial const* mat);
PXC_API uint8_t pxMatGetGroup(PxMaterial const* mat);
PXC_API uint32_t pxMatGetColor(PxMaterial const* mat);
PXC_API float pxMatGetSmoothAngle(PxMaterial const* mat);
PXC_API char const* pxMatGetTexture(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetTextureScale(PxMaterial const* mat);
PXC_API float pxMatGetTextureAnimFps(PxMaterial const* mat);
PXC_API uint8_t pxMatGetTextureAnimMapMode(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetTextureAnimMapDir(PxMaterial const* mat);
PXC_API PxBool pxMatGetDisableCollision(PxMaterial const* mat);
PXC_API PxBool pxMatGetDisableLightmap(PxMaterial const* mat);
PXC_API PxBool pxMatGetDontCollapse(PxMaterial const* mat);
PXC_API char const* pxMatGetDetailObject(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetDetailTextureScale(PxMaterial const* mat);
PXC_API PxBool pxMatGetForceOcculuder(PxMaterial const* mat);
PXC_API PxBool pxMatGetEnvironmentMapping(PxMaterial const* mat);
PXC_API float pxMatGetEnvironmentMappingStrength(PxMaterial const* mat);
PXC_API uint8_t pxMatGetWaveMode(PxMaterial const* mat);
PXC_API uint8_t pxMatGetWaveSpeed(PxMaterial const* mat);
PXC_API float pxMatGetWaveMaxAmplitude(PxMaterial const* mat);
PXC_API float pxMatGetWaveGridSize(PxMaterial const* mat);
PXC_API PxBool pxMatGetIgnoreSun(PxMaterial const* mat);
PXC_API uint8_t pxMatGetAlphaFunc(PxMaterial const* mat);
PXC_API PxVec2 pxMatGetDefaultMapping(PxMaterial const* mat);
