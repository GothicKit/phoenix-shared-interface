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

typedef enum {
	PxDaedalusSymbolType_Void = 0U,
	PxDaedalusSymbolType_Float = 1U,
	PxDaedalusSymbolType_Int = 2U,
	PxDaedalusSymbolType_String = 3U,
	PxDaedalusSymbolType_Class = 4U,
	PxDaedalusSymbolType_Function = 5U,
	PxDaedalusSymbolType_Prototype = 6U,
	PxDaedalusSymbolType_Instance = 7U,
} PxDaedalusSymbolType;

typedef struct {
	char const* name;
	PxBool const_;
	PxBool member;
	PxBool external;
	PxBool merged;
	PxBool generated;
	PxBool return_;

	uint32_t address;
	uint32_t parent;
	uint32_t count;
	uint32_t index;

	PxDaedalusSymbolType type;
	PxDaedalusSymbolType return_type;
} PxDaedalusSymbolInfo;

typedef struct {
	int code;
	int32_t p1;
	uint8_t p2;
} PxDaedalusInstruction;

typedef PxBool (*PxDaedalusEnumerateCallback)(PxDaedalusScript const*, PxDaedalusSymbol const*);

// TODO
PXC_API PxDaedalusScript* pxScriptLoad(PxBuffer* buffer);
PXC_API PxDaedalusScript* pxScriptLoadFromVfs(PxVfs const* vfs, char const* name);
PXC_API void pxScriptDestroy(PxDaedalusScript* scr);

PXC_API PxDaedalusSymbol const* pxScriptGetSymbolById(PxDaedalusScript const* scr, uint32_t id);
PXC_API PxDaedalusSymbol const* pxScriptGetSymbolByAddress(PxDaedalusScript const* scr, uint32_t address);
PXC_API PxDaedalusSymbol const* pxScriptGetSymbolByName(PxDaedalusScript const* scr, char const* name);

PXC_API uint8_t pxScriptGetInstruction(PxDaedalusScript const* scr, uint32_t ip, PxDaedalusInstruction* info);

PXC_API size_t pxScriptGetSymbolCount(PxDaedalusScript const* scr);
PXC_API void pxScriptEnumerateSymbols(PxDaedalusScript const* scr, PxDaedalusEnumerateCallback cb);

PXC_API size_t pxScriptSymbolGetId(PxDaedalusSymbol const* sym);
PXC_API char const* pxScriptSymbolGetName(PxDaedalusSymbol const* sym);
PXC_API void pxScriptSymbolGetInfo(PxDaedalusSymbol const* sym, PxDaedalusSymbolInfo* info);

PXC_API int pxScriptSymbolGetInt(PxDaedalusSymbol const* sym, size_t index);
PXC_API float pxScriptSymbolGetFloat(PxDaedalusSymbol const* sym, size_t index);
PXC_API char const* pxScriptSymbolGetString(PxDaedalusSymbol const* sym, size_t index);
