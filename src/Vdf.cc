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

uint32_t pxVdfGetRootEntryCount(PxVdf const* vdf) {
    return (uint32_t) vdf->entries.size();
}

PxVdfEntry const* pxVdfGetRootEntry(PxVdf const* vdf, uint32_t i) {
	return &*std::next(vdf->entries.begin(), i);
}

char const* pxVdfEntryGetName(PxVdfEntry const* entry) {
    return entry->name.c_str();
}

PxBool pxVdfEntryIsDirectory(PxVdfEntry const* entry) {
    return entry->is_directory();
}

uint32_t pxVdfEntryGetChildCount(PxVdfEntry const* entry) {
	return (uint32_t) entry->children.size();
}

PxVdfEntry const* pxVdfEntryGetChild(PxVdfEntry const* entry, uint32_t i) {
	return &*std::next(entry->children.begin(), i);
}
