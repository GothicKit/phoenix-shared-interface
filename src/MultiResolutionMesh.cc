// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/proto_mesh.hh>
#include <phoenix/cffi/MultiResolutionMesh.h>

PxMultiResolutionMesh* pxMrmLoad(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::proto_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxMultiResolutionMesh*>(new phoenix::proto_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxMultiResolutionMesh* pxMrmLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxMultiResolutionMesh* result = pxMrmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMrmDestroy(PxMultiResolutionMesh* mrm) {
	delete reinterpret_cast<phoenix::proto_mesh*>(mrm);
}
