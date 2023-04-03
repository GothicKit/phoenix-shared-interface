// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_World PxWorld;

// TODO
PXC_API PxWorld* px_world_parse(PxBuffer* buffer);
PXC_API void px_world_destroy(PxWorld* world);
