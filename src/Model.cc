// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Model.h>
#include <phoenix/model.hh>

PxModel* pxMdlLoad(PxBuffer* buffer) {
	try {
		auto mat = px::model::parse(buffer->duplicate());
		return new phoenix::model(std::move(mat));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModel* pxMdlLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
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
