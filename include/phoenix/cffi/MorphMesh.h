// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct s_PxMorphMesh PxMorphMesh;

// TODO
PXC_API PxMorphMesh* px_mmb_parse(PxBuffer* buffer);
PXC_API void px_mmb_destroy(PxMorphMesh* mmb);
