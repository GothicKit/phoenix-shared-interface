// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_ModelAnimation PxModelAnimation;

PXC_API PxModelAnimation* px_man_parse(PxBuffer* buffer);
PXC_API char const* px_man_name(PxModelAnimation const* man);
PXC_API char const* px_man_next(PxModelAnimation const* man);
PXC_API uint32_t px_man_layer(PxModelAnimation const* man);
PXC_API uint32_t px_man_frame_count(PxModelAnimation const* man);
PXC_API uint32_t px_man_node_count(PxModelAnimation const* man);
PXC_API float px_man_fps(PxModelAnimation const* man);
PXC_API PxAABB px_man_bbox(PxModelAnimation const* man);
PXC_API uint32_t px_man_checksum(PxModelAnimation const* man);
PXC_API void px_man_sample(PxModelAnimation const* man, uint32_t i, PxVec3* position, PxQuat* rotation);
PXC_API uint32_t const* px_man_node_indices(PxModelAnimation const* man, uint32_t* length);
PXC_API void px_man_destroy(PxModelAnimation* ani);
