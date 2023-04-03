// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_DaedalusScript PxDaedalusScript;
typedef struct PxInternal_DaedalusSymbol PxDaedalusSymbol;

// TODO
PXC_API PxDaedalusScript* px_script_parse(PxBuffer* buffer);
PXC_API PxDaedalusSymbol const* px_script_find_symbol_by_id(PxDaedalusScript const* scr, uint32_t id);
PXC_API PxDaedalusSymbol const* px_script_find_symbol_by_name(PxDaedalusScript const* scr, char const* name);
PXC_API void px_script_destroy(PxDaedalusScript* scr);
