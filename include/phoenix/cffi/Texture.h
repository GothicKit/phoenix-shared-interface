// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

typedef struct PxInternal_Texture PxTexture;

PXC_API PxTexture* pxTexLoad(PxBuffer* buffer);
PXC_API PxTexture* pxTexLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxTexDestroy(PxTexture* tex);

PXC_API void pxTexGetMeta(PxTexture const* tex, uint32_t* format, uint32_t* width, uint32_t* height, uint32_t* mipmapCount, uint32_t* averageColor);
PXC_API uint8_t const* pxTexGetMipmap(PxTexture const* tex, uint32_t level, uint32_t* width, uint32_t* height);
