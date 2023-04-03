// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/model_script.hh>
#include <phoenix/cffi/ModelScript.h>

PxModelScript* pxMdsLoad(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::model_script::parse(buf->duplicate());
		return reinterpret_cast<PxModelScript*>(new phoenix::model_script(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModelScript* pxMdsLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxModelScript* result = pxMdsLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdsDestroy(PxModelScript* mdm) {
	delete reinterpret_cast<phoenix::model_script*>(mdm);
}
