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

void pxVfsMountDiskData(PxVfs* vfs, PxBuffer* path, PxVfsOverwriteBehavior overwriteFlag) {
	try {
		vfs->mount_disk(*path, static_cast<px::VfsOverwriteBehavior>(overwriteFlag));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error,
		                 "API:PxVfs",
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

PxVfsNode const* pxVfsGetRootNode(const PxVfs* node) {
	return &node->root();
}

char const* pxVfsNodeGetName(const PxVfsNode* node) {
	return node->name().c_str();
}

size_t pxVfsNodeGetChildCount(const PxVfsNode* node) {
	if (node->type() == phoenix::VfsNodeType::FILE) return 0;
	return node->children().size();
}

PxVfsNode const* pxVfsNodeGetChild(const PxVfsNode* node, size_t i) {
	if (node->type() == phoenix::VfsNodeType::FILE) return nullptr;

	for (const auto& item : node->children()) {
		if (i == 0) return &item;
		i--;
	}

	return nullptr;
}

PxBool pxVfsNodeIsFile(const PxVfsNode* node) {
	return node->type() == phoenix::VfsNodeType::FILE;
}
