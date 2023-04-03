// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_MultiResolutionMesh PxMultiResolutionMesh;

// TODO
PXC_API PxMultiResolutionMesh* px_mrm_parse(PxBuffer* buffer);
PXC_API void px_mrm_destroy(PxMultiResolutionMesh* mrm);
