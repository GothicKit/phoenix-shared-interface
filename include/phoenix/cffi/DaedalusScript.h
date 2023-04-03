// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"

#include <stdint.h>

typedef struct PxInternal_DaedalusScript PxDaedalusScript;
typedef struct PxInternal_DaedalusSymbol PxDaedalusSymbol;

// TODO
PXC_API PxDaedalusScript* pxScriptLoad(PxBuffer* buffer);
PXC_API PxDaedalusScript* pxScriptLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxScriptDestroy(PxDaedalusScript* scr);

PXC_API PxDaedalusSymbol const* pxScriptGetSymbolById(PxDaedalusScript const* scr, uint32_t id);
PXC_API PxDaedalusSymbol const* pxScriptGetSymbolByName(PxDaedalusScript const* scr, char const* name);
