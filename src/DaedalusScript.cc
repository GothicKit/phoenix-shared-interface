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
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxDaedalusScript",
		                 "encountered exception while parsing PxDaedalusScript: %s",
		                 e.what());
		return nullptr;
	}
}

PxDaedalusScript* pxScriptLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetNodeByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "CAPI:PxDaedalusScript", "failed to find vfs entry: %s", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
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

PxDaedalusSymbol const* pxScriptGetSymbolByAddress(PxDaedalusScript const* scr, uint32_t address) {
	return scr->find_symbol_by_address(address);
}

PxDaedalusSymbol const* pxScriptGetSymbolByName(PxDaedalusScript const* scr, char const* name) {
	return scr->find_symbol_by_name(name);
}

uint8_t pxScriptGetInstruction(PxDaedalusScript const* scr, uint32_t ip, PxDaedalusInstruction* info) {
	auto i = scr->instruction_at(ip);
	info->code = static_cast<int>(i.op);

	switch (i.op) {
	case phoenix::opcode::bl:
	case phoenix::opcode::bz:
	case phoenix::opcode::b:
		info->p1 = static_cast<int32_t>(i.address);
		return 5;
	case phoenix::opcode::pushi:
		info->p1 = i.immediate;
		return 5;
	case phoenix::opcode::be:
	case phoenix::opcode::pushv:
	case phoenix::opcode::pushvi:
	case phoenix::opcode::gmovi:
		info->p1 = static_cast<int32_t>(i.symbol);
		return 5;
	case phoenix::opcode::pushvv:
		info->p1 = static_cast<int32_t>(i.symbol);
		info->p2 = i.index;
		return 6;
	default:
		return 1;
	}
}

size_t pxScriptGetSymbolCount(PxDaedalusScript const* scr) {
	return scr->symbols().size();
}

void pxScriptEnumerateSymbols(PxDaedalusScript const* scr, PxDaedalusEnumerateCallback cb) {
	for (auto& sym : scr->symbols()) {
		if (!cb(scr, &sym)) break;
	}
}

size_t pxScriptSymbolGetId(PxDaedalusSymbol const* sym) {
	return sym->index();
}

char const* pxScriptSymbolGetName(PxDaedalusSymbol const* sym) {
	return sym->name().c_str();
}

void pxScriptSymbolGetInfo(PxDaedalusSymbol const* sym, PxDaedalusSymbolInfo* info) {
	info->name = sym->name().c_str();
	info->const_ = sym->is_const();
	info->member = sym->is_member();
	info->external = sym->is_external();
	info->merged = sym->is_merged();
	info->generated = sym->is_generated();
	info->return_ = sym->has_return();
	info->address = sym->address();
	info->parent = sym->parent();
	info->count = sym->count();
	info->index = sym->index();
	info->type = static_cast<PxDaedalusSymbolType>(sym->type());
	info->return_type = static_cast<PxDaedalusSymbolType>(sym->rtype());
}

int pxScriptSymbolGetInt(PxDaedalusSymbol const* sym, size_t index) {
	return sym->get_int(index);
}

float pxScriptSymbolGetFloat(PxDaedalusSymbol const* sym, size_t index) {
	return sym->get_float(index);
}

char const* pxScriptSymbolGetString(PxDaedalusSymbol const* sym, size_t index) {
	return sym->get_string(index).c_str();
}
