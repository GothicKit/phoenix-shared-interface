// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Vdf.h>
#include <phoenix/vdfs.hh>

PxVdf* pxVdfNew(char const* comment) {
	return RC(PxVdf, new px::vdf_file {comment});
}

PxVdf* pxVdfLoad(PxBuffer* buffer) {
	try {
		auto buf = buffer->duplicate();
		auto vdf = px::vdf_file::open(buf);
		return new px::vdf_file(std::move(vdf));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxVdf: ", e.what());
		return nullptr;
	}
}

PxVdf* pxVdfLoadFromFile(char const* path) {
	try {
		auto buf = px::buffer::mmap(path);
		auto vdf = px::vdf_file::open(buf);
		return new px::vdf_file(std::move(vdf));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxVdf: ", e.what());
		return nullptr;
	}
}

void pxVdfDestroy(PxVdf* vdf) {
	delete vdf;
}

void pxVdfMerge(PxVdf* vdf, PxVdf* other, PxBool override) {
	vdf->merge(*other, override);
}

PxVdfEntry const* pxVdfGetEntryByName(PxVdf const* vdf, char const* name) {
	return vdf->find_entry(name);
}

PxBuffer* pxVdfEntryOpenBuffer(PxVdfEntry const* entry) {
	return new phoenix::buffer {entry->open()};
}
