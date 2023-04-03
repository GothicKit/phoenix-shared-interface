// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_ModelMesh PxModelMesh;

// TODO
PXC_API PxModelMesh* px_mdm_parse(PxBuffer* buffer);
PXC_API void px_mdm_destroy(PxModelMesh* mdm);
