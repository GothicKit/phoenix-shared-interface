// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vfs.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/script.hh>
typedef phoenix::script PxDaedalusScript;
typedef phoenix::symbol PxDaedalusSymbol;
#else
typedef struct PxInternal_DaedalusScript PxDaedalusScript;
typedef struct PxInternal_DaedalusSymbol PxDaedalusSymbol;
#endif

// TODO
PXC_API PxDaedalusScript* pxScriptLoad(PxBuffer* buffer);
PXC_API PxDaedalusScript* pxScriptLoadFromVfs(PxVfs const* vfs, char const* name);
PXC_API void pxScriptDestroy(PxDaedalusScript* scr);

PXC_API PxDaedalusSymbol const* pxScriptGetSymbolById(PxDaedalusScript const* scr, uint32_t id);
PXC_API PxDaedalusSymbol const* pxScriptGetSymbolByName(PxDaedalusScript const* scr, char const* name);
