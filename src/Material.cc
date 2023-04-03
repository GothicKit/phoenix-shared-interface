// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/material.hh>
#include <phoenix/cffi/Material.h>

char const* px_material_name(PxMaterial const* mat) {
	return RCC(px::material, mat)->name.c_str();
}

uint8_t px_material_group(PxMaterial const* mat) {
	return (uint8_t) RCC(px::material, mat)->group;
}

uint32_t px_material_color(PxMaterial const* mat) {
	auto clr = RCC(px::material, mat)->color;
	return (uint32_t) (clr.a << 24 | clr.r << 16 | clr.g << 8 | clr.b);
}

float px_material_smooth_angle(PxMaterial const* mat) {
	return RCC(px::material, mat)->smooth_angle;
}

char const* px_material_texture(PxMaterial const* mat) {
	return RCC(px::material, mat)->texture.c_str();
}

PxVec2 px_material_texture_scale(PxMaterial const* mat) {
	auto sc = RCC(px::material, mat)->texture_scale;
	return {sc.x, sc.y};
}

float px_material_texture_anim_fps(PxMaterial const* mat) {
	return RCC(px::material, mat)->texture_anim_fps;
}

uint8_t px_material_texture_anim_map_mode(PxMaterial const* mat) {
	return (uint8_t) RCC(px::material, mat)->texture_anim_map_mode;
}

PxVec2 px_material_texture_anim_map_dir(PxMaterial const* mat) {
	auto dir = RCC(px::material, mat)->texture_anim_map_dir;
	return {dir.x, dir.y};
}

PxBool px_material_disable_collision(PxMaterial const* mat) {
	return RCC(px::material, mat)->disable_collision;
}

PxBool px_material_disable_lightmap(PxMaterial const* mat) {
	return RCC(px::material, mat)->disable_lightmap;
}

PxBool px_material_dont_collapse(PxMaterial const* mat) {
	return RCC(px::material, mat)->dont_collapse;
}

char const* px_material_detail_object(PxMaterial const* mat) {
	return RCC(px::material, mat)->detail_object.c_str();
}

PxVec2 px_material_detail_texture_scale(PxMaterial const* mat) {
	auto sc = RCC(px::material, mat)->texture_scale;
	return {sc.x, sc.y};
}

PxBool px_material_force_occluder(PxMaterial const* mat) {
	return RCC(px::material, mat)->force_occluder;
}

PxBool px_material_environment_mapping(PxMaterial const* mat) {
	return RCC(px::material, mat)->environment_mapping;
}

float px_material_environment_mapping_strength(PxMaterial const* mat) {
	return RCC(px::material, mat)->environment_mapping_strength;
}

uint8_t px_material_wave_mode(PxMaterial const* mat) {
	return (uint8_t) RCC(px::material, mat)->wave_mode;
}

uint8_t px_material_wave_speed(PxMaterial const* mat) {
	return (uint8_t) RCC(px::material, mat)->wave_speed;
}

float px_material_wave_max_amplitude(PxMaterial const* mat) {
	return RCC(px::material, mat)->wave_max_amplitude;
}

float px_material_wave_grid_size(PxMaterial const* mat) {
	return RCC(px::material, mat)->wave_grid_size;
}

PxBool px_material_ignore_sun(PxMaterial const* mat) {
	return RCC(px::material, mat)->ignore_sun;
}

uint8_t px_material_alpha_func(PxMaterial const* mat) {
	return (uint8_t) RCC(px::material, mat)->alpha_func;
}

PxVec2 px_material_default_mapping(PxMaterial const* mat) {
	auto mp = RCC(px::material, mat)->default_mapping;
	return {mp.x, mp.y};
}
