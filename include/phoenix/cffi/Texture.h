// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/texture.hh>
typedef phoenix::texture PxTexture;
#else
typedef struct PxInternal_Texture PxTexture;
#endif

typedef enum {
    PxTexture_B8G8R8A8 = 0x0,
    PxTexture_R8G8B8A8 = 0x1,
    PxTexture_A8B8G8R8 = 0x2,
    PxTexture_A8R8G8B8 = 0x3,
    PxTexture_B8G8R8 = 0x4,
    PxTexture_R8G8B8 = 0x5,
    PxTexture_A4R4G4B4 = 0x6,
    PxTexture_A1R5G5B5 = 0x7,
    PxTexture_R5G6B5 = 0x8,
    PxTexture_p8 = 0x9,
    PxTexture_dxt1 = 0xA,
    PxTexture_dxt2 = 0xB,
    PxTexture_dxt3 = 0xC,
    PxTexture_dxt4 = 0xD,
    PxTexture_dxt5 = 0xE
} PxTextureFormat;

PXC_API PxTexture* pxTexLoad(PxBuffer* buffer);
PXC_API PxTexture* pxTexLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxTexDestroy(PxTexture* tex);

PXC_API void pxTexGetMeta(PxTexture const* tex, PxTextureFormat* format, uint32_t* width, uint32_t* height, uint32_t* mipmapCount, uint32_t* averageColor);
PXC_API uint8_t const* pxTexGetMipmap(PxTexture const* tex, uint32_t level, uint32_t* width, uint32_t* height);

// TODO: Conversion!
