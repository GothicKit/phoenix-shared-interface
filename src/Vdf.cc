// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/vdfs.hh>
#include <phoenix/cffi/Vdf.h>

PxVdf* pxVdfLoad(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<px::buffer*>(buffer)->duplicate();
		auto vdf = px::vdf_file::open(buf);
		return reinterpret_cast<PxVdf*>(new px::vdf_file(std::move(vdf)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void pxVdfDestroy(PxVdf* vdf) {
	delete reinterpret_cast<phoenix::vdf_file*>(vdf);
}

PxVdfEntry const* pxVdfGetEntryByName(PxVdf const* vdf, char const* name) {
	auto* entry = RCC(px::vdf_file, vdf)->find_entry(name);
	return reinterpret_cast<PxVdfEntry const*>(entry);
}

PxBuffer* pxVdfEntryOpen(PxVdfEntry const* entry) {
	auto* e = reinterpret_cast<phoenix::vdf_entry const*>(entry);
	return reinterpret_cast<PxBuffer*>(new phoenix::buffer {e->open()});
}

