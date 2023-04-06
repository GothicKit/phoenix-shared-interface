// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Cutscene.h>
#include <phoenix/messages.hh>

PxCutsceneLib* pxCslLoad(PxBuffer* buffer) {
	try {
		auto mat = px::messages::parse(buffer->duplicate());
		return new phoenix::messages(std::move(mat));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxCutsceneLib* pxCslLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxCutsceneLib* result = pxCslLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxCslDestroy(PxCutsceneLib* csl) {
	delete csl;
}

char const* pxCslGetBlock(PxCutsceneLib const* csl, char const* name, uint32_t* type) {
	auto* src = csl->block_by_name(name);
	*type = src->message.type;
	return src->message.text.c_str();
}
