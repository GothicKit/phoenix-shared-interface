// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/morph_mesh.hh>
#include <phoenix/cffi/MorphMesh.h>

PxMorphMesh* px_mmb_parse(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::morph_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxMorphMesh*>(new phoenix::morph_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void px_mmb_destroy(PxMorphMesh* mmb) {
	delete reinterpret_cast<phoenix::morph_mesh*>(mmb);
}
