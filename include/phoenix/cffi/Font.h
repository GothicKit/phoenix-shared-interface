// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_Font PxFont;

PXC_API PxFont* px_fnt_parse(PxBuffer* buffer);
PXC_API char const* px_fnt_name(PxFont const* fnt);
PXC_API uint32_t px_fnt_height(PxFont const* fnt);
PXC_API uint32_t px_fnt_glyph_count(PxFont const* fnt);
PXC_API void px_fnt_glyph(PxFont const* fnt, uint32_t i, uint8_t* width, PxVec2* upper, PxVec2* lower);
PXC_API void px_fnt_destroy(PxFont* fnt);
