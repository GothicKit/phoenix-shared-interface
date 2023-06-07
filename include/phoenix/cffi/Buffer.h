// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/buffer.hh>
typedef phoenix::buffer PxBuffer;
#else
typedef struct PxInternal_Buffer PxBuffer;
#endif

PXC_API PxBuffer* pxBufferCreate(uint8_t const* bytes, uint64_t size);
PXC_API PxBuffer* pxBufferMmap(char const* file);
PXC_API void pxBufferDestroy(PxBuffer* buffer);
PXC_API uint64_t pxBufferSize(PxBuffer* buffer);
PXC_API std::byte* pxBufferArray(PxBuffer* buffer);
