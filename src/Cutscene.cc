// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/messages.hh>
#include <phoenix/cffi/Cutscene.h>

PxCutsceneLib* pxCslLoad(PxBuffer* buffer) {
	try {
		auto* buf = RC(phoenix::buffer, buffer);
		auto mat = px::messages::parse(buf->duplicate());
		return RC(PxCutsceneLib, new phoenix::messages(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxCutsceneLib* pxCslLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxCutsceneLib* result = pxCslLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxCslDestroy(PxCutsceneLib* csl) {
	delete RC(phoenix::messages, csl);
}

char const* pxCslGetBlock(PxCutsceneLib const* csl, char const* name, uint32_t* type) {
	auto* src = RCC(phoenix::messages, csl)->block_by_name(name);
	*type = src->message.type;
	return src->message.text.c_str();
}
