// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/ModelScript.h>
#include <phoenix/model_script.hh>

PxModelScript* pxMdsLoad(PxBuffer* buffer) {
	try {
		auto mat = phoenix::model_script::parse(buffer->duplicate());
		return new phoenix::model_script(std::move(mat));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModelScript* pxMdsLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxModelScript* result = pxMdsLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdsDestroy(PxModelScript* mdm) {
	delete mdm;
}
