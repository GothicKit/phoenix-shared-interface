// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/Vfs.hh>
#include <phoenix/cffi/Vfs.h>

PxVfs* pxVfsNew() {
	return RC(PxVfs, new phoenix::Vfs());
}

void pxVfsMountFile(PxVfs* vfs, char const* path) {
	try {
		vfs->mount_disk(std::filesystem::path(path), px::VfsOverwriteBehavior::NEWER);
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxVfs: ", e.what());
	}
}

void pxVfsDestroy(PxVfs* vfs) {
	delete vfs;
}

PxVfsNode const* pxVfsGetNodeByName(PxVfs const* vfs, char const* name) {
	return vfs->find(name);
}

PxBuffer* pxVfsNodeOpenBuffer(PxVfsNode const* node) {
	return new phoenix::buffer {node->open()};
}
