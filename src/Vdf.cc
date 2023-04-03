// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/vdfs.hh>
#include <phoenix/cffi/Vdf.h>

PxVdf* px_vdf_parse(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<px::buffer*>(buffer)->duplicate();
		auto vdf = px::vdf_file::open(buf);
		return reinterpret_cast<PxVdf*>(new px::vdf_file(std::move(vdf)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxVdfEntry const* px_vdf_search(PxVdf const* vdf, char const* name) {
	auto* entry = RCC(px::vdf_file, vdf)->find_entry(name);
	return reinterpret_cast<PxVdfEntry const*>(entry);
}

PxVdfEntry const* px_vdf_resolve(PxVdf const* vdf, char const* resolve) {
	auto* entry = RCC(px::vdf_file, vdf)->resolve_path(resolve);
	return reinterpret_cast<PxVdfEntry const*>(entry);
}

PxBuffer* px_vdf_entry_open(PxVdfEntry const* entry) {
	auto* e = reinterpret_cast<phoenix::vdf_entry const*>(entry);
	return reinterpret_cast<PxBuffer*>(new phoenix::buffer {e->open()});
}

void px_vdf_destroy(PxVdf* vdf) {
	delete reinterpret_cast<phoenix::vdf_file*>(vdf);
}
