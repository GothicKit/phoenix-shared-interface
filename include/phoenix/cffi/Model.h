// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "ModelMesh.h"
#include "ModelHierarchy.h"

#include <stdint.h>

typedef struct PxInternal_Model PxModel;

PXC_API PxModel* px_mdl_parse(PxBuffer* buffer);
PXC_API PxModelHierarchy const* px_mdl_hierarchy(PxModel const* mdl);
PXC_API PxModelMesh const* px_mdl_mesh(PxModel const* mdl);
PXC_API void px_mdl_destroy(PxModel* mdl);
