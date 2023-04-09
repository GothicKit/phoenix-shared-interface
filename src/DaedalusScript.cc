// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/DaedalusScript.h>
#include <phoenix/script.hh>

PxDaedalusScript* pxScriptLoad(PxBuffer* buffer) {
	try {
		auto buf = buffer->duplicate();
		auto scr = px::script::parse(buf);
		return new px::script(std::move(scr));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxDaedalusScript: ", e.what());
		return nullptr;
	}
}

PxDaedalusScript* pxScriptLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vdf entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxDaedalusScript* result = pxScriptLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxScriptDestroy(PxDaedalusScript* scr) {
	delete scr;
}

PxDaedalusSymbol const* pxScriptGetSymbolById(PxDaedalusScript const* scr, uint32_t id) {
	return scr->find_symbol_by_index(id);
}

PxDaedalusSymbol const* pxScriptGetSymbolByName(PxDaedalusScript const* scr, char const* name) {
	return scr->find_symbol_by_name(name);
}
