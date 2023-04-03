// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_Material PxMaterial;
PXC_API char const* px_material_name(PxMaterial const* mat);
PXC_API uint8_t px_material_group(PxMaterial const* mat);
PXC_API uint32_t px_material_color(PxMaterial const* mat);
PXC_API float px_material_smooth_angle(PxMaterial const* mat);
PXC_API char const* px_material_texture(PxMaterial const* mat);
PXC_API PxVec2 px_material_texture_scale(PxMaterial const* mat);
PXC_API float px_material_texture_anim_fps(PxMaterial const* mat);
PXC_API uint8_t px_material_texture_anim_map_mode(PxMaterial const* mat);
PXC_API PxVec2 px_material_texture_anim_map_dir(PxMaterial const* mat);
PXC_API PxBool px_material_disable_collision(PxMaterial const* mat);
PXC_API PxBool px_material_disable_lightmap(PxMaterial const* mat);
PXC_API PxBool px_material_dont_collapse(PxMaterial const* mat);
PXC_API char const* px_material_detail_object(PxMaterial const* mat);
PXC_API PxVec2 px_material_detail_texture_scale(PxMaterial const* mat);
PXC_API PxBool px_material_force_occluder(PxMaterial const* mat);
PXC_API PxBool px_material_environment_mapping(PxMaterial const* mat);
PXC_API float px_material_environment_mapping_strength(PxMaterial const* mat);
PXC_API uint8_t px_material_wave_mode(PxMaterial const* mat);
PXC_API uint8_t px_material_wave_speed(PxMaterial const* mat);
PXC_API float px_material_wave_max_amplitude(PxMaterial const* mat);
PXC_API float px_material_wave_grid_size(PxMaterial const* mat);
PXC_API PxBool px_material_ignore_sun(PxMaterial const* mat);
PXC_API uint8_t px_material_alpha_func(PxMaterial const* mat);
PXC_API PxVec2 px_material_default_mapping(PxMaterial const* mat);
