// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"

#include <stdint.h>

typedef struct PxInternal_Buffer PxBuffer;

PXC_API PxBuffer* pxBufferCreate(uint8_t const* bytes, uint64_t size);
PXC_API PxBuffer* pxBufferMmap(char const* file);
PXC_API void pxBufferDestroy(PxBuffer* buffer);
