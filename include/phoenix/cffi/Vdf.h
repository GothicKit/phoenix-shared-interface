// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/vdfs.hh>
typedef phoenix::vdf_file PxVdf;
typedef phoenix::vdf_entry PxVdfEntry;
#else
typedef struct PxInternal_Vdf PxVdf;
typedef struct PxInternal_VdfEntry PxVdfEntry;
#endif

PXC_API PxVdf* pxVdfNew(char const* comment);
PXC_API PxVdf* pxVdfLoad(PxBuffer* buffer);
PXC_API PxVdf* pxVdfLoadFromFile(char const* path);
PXC_API void pxVdfDestroy(PxVdf* vdf);

PXC_API void pxVdfMerge(PxVdf* vdf, PxVdf* other, PxBool override);
PXC_API PxVdfEntry const* pxVdfGetEntryByName(PxVdf const* vdf, char const* name);
PXC_API PxBuffer* pxVdfEntryOpenBuffer(PxVdfEntry const* entry);
