// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/vm.hh>
#include <phoenix/ext/daedalus_classes.hh>
#include <phoenix/cffi/DaedalusVm.h>

PxDaedalusVm* pxVmLoad(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<phoenix::buffer*>(buffer)->duplicate();
		auto scr = phoenix::script::parse(buf);
		phoenix::register_all_script_classes(scr);
		return reinterpret_cast<PxDaedalusVm*>(new phoenix::vm(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxDaedalusVm* pxVmLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpen(entry);
	PxDaedalusVm* result = pxVmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxVmDestroy(PxDaedalusVm* vm) {
	delete reinterpret_cast<phoenix::vm*>(vm);
}
