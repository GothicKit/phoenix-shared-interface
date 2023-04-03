// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

typedef struct s_PxMorphMesh PxMorphMesh;

// TODO
PXC_API PxMorphMesh* pxMmbLoad(PxBuffer* buffer);
PXC_API PxMorphMesh* pxMmbLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMmbDestroy(PxMorphMesh* mmb);
