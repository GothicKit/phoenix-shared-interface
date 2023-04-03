// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/world.hh>
#include <phoenix/cffi/World.h>

PxWorld* pxWorldLoad(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<px::buffer*>(buffer)->duplicate();
		auto scr = px::world::parse(buf);
		return reinterpret_cast<PxWorld*>(new px::world(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxWorld* pxWorldLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxWorld* result = pxWorldLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxWorldDestroy(PxWorld* world) {
	delete reinterpret_cast<px::world*>(world);
}
