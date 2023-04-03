// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_Vdf PxVdf;
typedef struct PxInternal_VdfEntry PxVdfEntry;

PXC_API PxVdf* pxVdfLoad(PxBuffer* buffer);
PXC_API void pxVdfDestroy(PxVdf* vdf);

PXC_API PxVdfEntry const* pxVdfGetEntryByName(PxVdf const* vdf, char const* name);
PXC_API PxBuffer* pxVdfEntryOpen(PxVdfEntry const* entry);
