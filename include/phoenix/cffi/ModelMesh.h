// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

typedef struct PxInternal_ModelMesh PxModelMesh;

// TODO
PXC_API PxModelMesh* pxMdmLoad(PxBuffer* buffer);
PXC_API PxModelMesh* pxMdmLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMdmDestroy(PxModelMesh* mdm);
