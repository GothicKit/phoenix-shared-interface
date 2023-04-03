// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/model_script.hh>
#include <phoenix/cffi/ModelScript.h>

PxModelScript* px_mds_parse(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::model_script::parse(buf->duplicate());
		return reinterpret_cast<PxModelScript*>(new phoenix::model_script(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void px_mds_destroy(PxModelScript* mdm) {
	delete reinterpret_cast<phoenix::model_script*>(mdm);
}
