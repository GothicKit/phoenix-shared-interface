// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Material.h>
#include <phoenix/material.hh>

char const* pxMatGetName(PxMaterial const* mat) {
	return mat->name.c_str();
}

uint8_t pxMatGetGroup(PxMaterial const* mat) {
	return (uint8_t) mat->group;
}

uint32_t pxMatGetColor(PxMaterial const* mat) {
	auto clr = mat->color;
	return (uint32_t) (clr.a << 24 | clr.r << 16 | clr.g << 8 | clr.b);
}

float pxMatGetSmoothAngle(PxMaterial const* mat) {
	return mat->smooth_angle;
}

char const* pxMatGetTexture(PxMaterial const* mat) {
	return mat->texture.c_str();
}

PxVec2 pxMatGetTextureScale(PxMaterial const* mat) {
	auto sc = mat->texture_scale;
	return {sc.x, sc.y};
}

float pxMatGetTextureAnimFps(PxMaterial const* mat) {
	return mat->texture_anim_fps;
}

uint8_t pxMatGetTextureAnimMapMode(PxMaterial const* mat) {
	return (uint8_t) mat->texture_anim_map_mode;
}

PxVec2 pxMatGetTextureAnimMapDir(PxMaterial const* mat) {
	auto dir = mat->texture_anim_map_dir;
	return {dir.x, dir.y};
}

PxBool pxMatGetDisableCollision(PxMaterial const* mat) {
	return mat->disable_collision;
}

PxBool pxMatGetDisableLightmap(PxMaterial const* mat) {
	return mat->disable_lightmap;
}

PxBool pxMatGetDontCollapse(PxMaterial const* mat) {
	return mat->dont_collapse;
}

char const* pxMatGetDetailObject(PxMaterial const* mat) {
	return mat->detail_object.c_str();
}

PxVec2 pxMatGetDetailTextureScale(PxMaterial const* mat) {
	auto sc = mat->texture_scale;
	return {sc.x, sc.y};
}

PxBool pxMatGetForceOcculuder(PxMaterial const* mat) {
	return mat->force_occluder;
}

PxBool pxMatGetEnvironmentMapping(PxMaterial const* mat) {
	return mat->environment_mapping;
}

float pxMatGetEnvironmentMappingStrength(PxMaterial const* mat) {
	return mat->environment_mapping_strength;
}

uint8_t pxMatGetWaveMode(PxMaterial const* mat) {
	return (uint8_t) mat->wave_mode;
}

uint8_t pxMatGetWaveSpeed(PxMaterial const* mat) {
	return (uint8_t) mat->wave_speed;
}

float pxMatGetWaveMaxAmplitude(PxMaterial const* mat) {
	return mat->wave_max_amplitude;
}

float pxMatGetWaveGridSize(PxMaterial const* mat) {
	return mat->wave_grid_size;
}

PxBool pxMatGetIgnoreSun(PxMaterial const* mat) {
	return mat->ignore_sun;
}

uint8_t pxMatGetAlphaFunc(PxMaterial const* mat) {
	return (uint8_t) mat->alpha_func;
}

PxVec2 pxMatGetDefaultMapping(PxMaterial const* mat) {
	auto mp = mat->default_mapping;
	return {mp.x, mp.y};
}
