// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

typedef struct PxInternal_DaedalusVm PxDaedalusVm;

// TODO
PXC_API PxDaedalusVm* pxVmLoad(PxBuffer* buffer);
PXC_API PxDaedalusVm* pxVmLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxVmDestroy(PxDaedalusVm* vm);
