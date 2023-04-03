// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"

#include <stdint.h>

typedef struct PxInternal_Buffer PxBuffer;

PXC_API PxBuffer* px_buffer_create(uint8_t const* bytes, uint64_t size);
PXC_API PxBuffer* px_buffer_mmap(char const* file);
PXC_API void px_buffer_destroy(PxBuffer* buffer);
