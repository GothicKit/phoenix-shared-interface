// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/ModelMesh.h>
#include <phoenix/model_mesh.hh>

PxModelMesh* pxMdmLoad(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::model_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxModelMesh*>(new phoenix::model_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModelMesh* pxMdmLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxModelMesh* result = pxMdmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdmDestroy(PxModelMesh* mdm) {
	delete reinterpret_cast<phoenix::model_mesh*>(mdm);
}
