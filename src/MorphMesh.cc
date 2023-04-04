// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/morph_mesh.hh>
#include <phoenix/cffi/MorphMesh.h>

PxMorphMesh* pxMmbLoad(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::morph_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxMorphMesh*>(new phoenix::morph_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxMorphMesh* pxMmbLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxMorphMesh* result = pxMmbLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMmbDestroy(PxMorphMesh* mmb) {
	delete reinterpret_cast<phoenix::morph_mesh*>(mmb);
}
