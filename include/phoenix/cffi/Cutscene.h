// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
#include <phoenix/messages.hh>
typedef phoenix::messages PxCutsceneLib;
#else
typedef struct PxInternal_CutsceneLib PxCutsceneLib;
#endif

PXC_API PxCutsceneLib* pxCslLoad(PxBuffer* buffer);
PXC_API PxCutsceneLib* pxCslLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxCslDestroy(PxCutsceneLib* csl);

PXC_API char const* pxCslGetBlock(PxCutsceneLib const* csl, char const* name, uint32_t* type);
