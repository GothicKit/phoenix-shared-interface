// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Model.h>
#include <phoenix/model.hh>

PxModel* pxMdlLoad(PxBuffer* buffer) {
	try {
		auto mat = px::model::parse(buffer->duplicate());
		return new phoenix::model(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxModel: ", e.what());
		return nullptr;
	}
}

PxModel* pxMdlLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetEntryByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vfs entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
	PxModel* result = pxMdlLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdlDestroy(PxModel* mdl) {
	delete mdl;
}

PxModelHierarchy const* pxMdlGetHierarchy(PxModel const* mdl) {
	return &mdl->hierarchy;
}

PxModelMesh const* pxMdlGetMesh(PxModel const* mdl) {
	return &mdl->mesh;
}
