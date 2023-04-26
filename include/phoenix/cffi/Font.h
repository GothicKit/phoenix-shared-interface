// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/font.hh>
typedef phoenix::font PxFont;
#else
typedef struct PxInternal_Font PxFont;
#endif

PXC_API PxFont* pxFntLoad(PxBuffer* buffer);PXC_API PxFont* pxFntLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxFntDestroy(PxFont* fnt);

PXC_API char const* pxFntGetName(PxFont const* fnt);
PXC_API uint32_t pxFntGetHeight(PxFont const* fnt);
PXC_API uint32_t pxFntGetGlyphCount(PxFont const* fnt);
PXC_API void pxFntGetGlyph(PxFont const* fnt, uint32_t i, uint8_t* width, PxVec2* upper, PxVec2* lower);
