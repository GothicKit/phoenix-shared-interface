// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_Texture PxTexture;

PXC_API PxTexture* px_tex_parse(PxBuffer* buffer);
PXC_API void px_tex_get_meta(PxTexture const* tex, uint32_t* format, uint32_t* width, uint32_t* height, uint32_t* mipmapCount, uint32_t* averageColor);
PXC_API uint8_t const* px_tex_get_mipmap(PxTexture const* tex, uint32_t level, uint32_t* width, uint32_t* height);
PXC_API void px_tex_destroy(PxTexture* tex);
