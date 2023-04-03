// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_Vdf PxVdf;
typedef struct PxInternal_VdfEntry PxVdfEntry;

PXC_API PxVdf* px_vdf_parse(PxBuffer* buffer);
PXC_API PxVdfEntry const* px_vdf_search(PxVdf const* vdf, char const* name);
PXC_API PxVdfEntry const* px_vdf_resolve(PxVdf const* vdf, char const* path);
PXC_API PxBuffer* px_vdf_entry_open(PxVdfEntry const* entry);
PXC_API void px_vdf_destroy(PxVdf* vdf);
