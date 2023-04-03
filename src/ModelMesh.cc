// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/model_mesh.hh>
#include <phoenix/cffi/ModelMesh.h>

PxModelMesh* px_mdm_parse(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::model_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxModelMesh*>(new phoenix::model_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void px_mdm_destroy(PxModelMesh* mdm) {
	delete reinterpret_cast<phoenix::model_mesh*>(mdm);
}
