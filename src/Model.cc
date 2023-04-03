// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/model.hh>
#include <phoenix/cffi/Model.h>

PxModel* pxMdlLoad(PxBuffer* buffer) {
	try {
		auto* buf = RC(phoenix::buffer, buffer);
		auto mat = px::model::parse(buf->duplicate());
		return RC(PxModel, new phoenix::model(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModel* pxMdlLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxModel* result = pxMdlLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdlDestroy(PxModel* mdl) {
	delete RC(phoenix::model, mdl);
}

PxModelHierarchy const* pxMdlGetHierarchy(PxModel const* mdl) {
	return RCC(PxModelHierarchy, &RCC(px::model, mdl)->hierarchy);
}

PxModelMesh const* pxMdlGetMesh(PxModel const* mdl) {
	return RCC(PxModelMesh, &RCC(px::model, mdl)->mesh);
}

