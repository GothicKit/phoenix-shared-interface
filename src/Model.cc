// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/model.hh>
#include <phoenix/cffi/Model.h>

PxModel* px_mdl_parse(PxBuffer* buffer) {
	try {
		auto* buf = RC(phoenix::buffer, buffer);
		auto mat = px::model::parse(buf->duplicate());
		return RC(PxModel, new phoenix::model(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModelHierarchy const* px_mdl_hierarchy(PxModel const* mdl) {
	return RCC(PxModelHierarchy, &RCC(px::model, mdl)->hierarchy);
}

PxModelMesh const* px_mdl_mesh(PxModel const* mdl) {
	return RCC(PxModelMesh, &RCC(px::model, mdl)->mesh);
}

void px_mdl_destroy(PxModel* mdl) {
	delete RC(phoenix::model, mdl);
}
