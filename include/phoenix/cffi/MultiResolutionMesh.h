// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

typedef struct PxInternal_MultiResolutionMesh PxMultiResolutionMesh;

// TODO
PXC_API PxMultiResolutionMesh* pxMrmLoad(PxBuffer* buffer);
PXC_API PxMultiResolutionMesh* pxMrmLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMrmDestroy(PxMultiResolutionMesh* mrm);
