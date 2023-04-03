// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/proto_mesh.hh>
#include <phoenix/cffi/MultiResolutionMesh.h>

PxMultiResolutionMesh* px_mrm_parse(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::proto_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxMultiResolutionMesh*>(new phoenix::proto_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void px_mrm_destroy(PxMultiResolutionMesh* mmb) {
	delete reinterpret_cast<phoenix::proto_mesh*>(mmb);
}
