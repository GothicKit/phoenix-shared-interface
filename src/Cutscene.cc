// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/messages.hh>
#include <phoenix/cffi/Cutscene.h>

PxCutsceneLib* px_csl_parse(PxBuffer* buffer) {
	try {
		auto* buf = RC(phoenix::buffer, buffer);
		auto mat = px::messages::parse(buf->duplicate());
		return RC(PxCutsceneLib, new phoenix::messages(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

char const* px_csl_get(PxCutsceneLib const* csl, char const* name, uint32_t* type) {
	auto* src = RCC(phoenix::messages, csl)->block_by_name(name);
	*type = src->message.type;
	return src->message.text.c_str();
}

void px_csl_destroy(PxCutsceneLib* csl) {
	delete RC(phoenix::messages, csl);
}
