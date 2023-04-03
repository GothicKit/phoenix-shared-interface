// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/world.hh>
#include <phoenix/cffi/World.h>

PxWorld* px_world_parse(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<px::buffer*>(buffer)->duplicate();
		auto scr = px::world::parse(buf);
		return reinterpret_cast<PxWorld*>(new px::world(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void px_world_destroy(PxWorld* world) {
	delete reinterpret_cast<px::world*>(world);
}
