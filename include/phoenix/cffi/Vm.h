// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

typedef struct PxInternal_Vm PxVm;
typedef void (*PxVmExternalCallback)(PxVm* vm);
typedef void (*PxVmExternalDefaultCallback)(PxVm* vm, char const* name);

// TODO
PXC_API PxVm* pxVmLoad(PxBuffer* buffer);
PXC_API PxVm* pxVmLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxVmDestroy(PxVm* vm);

PXC_API char const* pxVmPopString(PxVm* vm);
PXC_API float pxVmPopFloat(PxVm* vm);
PXC_API int32_t pxVmPopInt(PxVm* vm);

PXC_API void pxVmRegisterExternal(PxVm* vm, char const* name, PxVmExternalCallback cb);
PXC_API void pxVmRegisterExternalDefault(PxVm* vm, PxVmExternalDefaultCallback cb);
