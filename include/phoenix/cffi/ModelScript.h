// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/model_script.hh>
typedef phoenix::model_script PxModelScript;
#else
typedef struct PxInternal_ModelScript PxModelScript;
#endif

// TODO
PXC_API PxModelScript* pxMdsLoad(PxBuffer* buffer);
PXC_API PxModelScript* pxMdsLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMdsDestroy(PxModelScript* mdm);
