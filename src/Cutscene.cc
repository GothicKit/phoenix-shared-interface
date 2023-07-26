// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Cutscene.h>
#include <phoenix/messages.hh>

PxCutsceneLib* pxCslLoad(PxBuffer* buffer) {
	try {
		auto mat = px::messages::parse(buffer->duplicate());
		return new phoenix::messages(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxCutsceneLib: ", e.what());
		return nullptr;
	}
}

PxCutsceneLib* pxCslLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetEntryByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vfs entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
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
