// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/Vfs.hh>
#include <phoenix/cffi/Vfs.h>

PxVfs* pxVfsNew() {
	return new phoenix::Vfs();
}

void pxVfsMountDisk(PxVfs* vfs, char const* path, PxVfsOverwriteBehavior overwriteFlag) {
	try {
		vfs->mount_disk(std::filesystem::path(path), static_cast<px::VfsOverwriteBehavior>(overwriteFlag));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVfs",
		                 "encountered exception while parsing PxVfs: %s",
		                 e.what());
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
