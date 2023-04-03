// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_CutsceneLib PxCutsceneLib;

PXC_API PxCutsceneLib* px_csl_parse(PxBuffer* buffer);
PXC_API char const* px_csl_get(PxCutsceneLib const* csl, char const* name, uint32_t* type);
PXC_API void px_csl_destroy(PxCutsceneLib* csl);
