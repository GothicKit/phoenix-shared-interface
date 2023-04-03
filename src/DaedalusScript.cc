// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/script.hh>
#include <phoenix/cffi/DaedalusScript.h>

PxDaedalusScript* px_script_parse(PxBuffer* buffer) {
	try {
		auto buf = RC(px::buffer, buffer)->duplicate();
		auto scr = px::script::parse(buf);
		return RC(PxDaedalusScript, new px::script(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxDaedalusSymbol const* px_script_find_symbol_by_id(PxDaedalusScript const* scr, uint32_t id) {
	return RCC(PxDaedalusSymbol, RCC(px::script, scr)->find_symbol_by_index(id));
}

PxDaedalusSymbol const* px_script_find_symbol_by_name(PxDaedalusScript const* scr, char const* name) {
	return RCC(PxDaedalusSymbol, RCC(px::script, scr)->find_symbol_by_name(name));
}

void px_script_destroy(PxDaedalusScript* scr) {
	delete RC(px::script, scr);
}
