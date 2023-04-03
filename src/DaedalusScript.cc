// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/script.hh>
#include <phoenix/cffi/DaedalusScript.h>

PxDaedalusScript* pxScriptLoad(PxBuffer* buffer) {
	try {
		auto buf = RC(px::buffer, buffer)->duplicate();
		auto scr = px::script::parse(buf);
		return RC(PxDaedalusScript, new px::script(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxDaedalusScript* pxScriptLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxDaedalusScript* result = pxScriptLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxScriptDestroy(PxDaedalusScript* scr) {
	delete RC(px::script, scr);
}

PxDaedalusSymbol const* pxScriptGetSymbolById(PxDaedalusScript const* scr, uint32_t id) {
	return RCC(PxDaedalusSymbol, RCC(px::script, scr)->find_symbol_by_index(id));
}

PxDaedalusSymbol const* pxScriptGetSymbolByName(PxDaedalusScript const* scr, char const* name) {
	return RCC(PxDaedalusSymbol, RCC(px::script, scr)->find_symbol_by_name(name));
}

