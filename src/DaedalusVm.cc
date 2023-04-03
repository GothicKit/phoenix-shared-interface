// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/vm.hh>
#include <phoenix/ext/daedalus_classes.hh>
#include <phoenix/cffi/DaedalusVm.h>

PxDaedalusVm* px_vm_parse(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<phoenix::buffer*>(buffer)->duplicate();
		auto scr = phoenix::script::parse(buf);
		phoenix::register_all_script_classes(scr);
		return reinterpret_cast<PxDaedalusVm*>(new phoenix::vm(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}
void px_vm_destroy(PxDaedalusVm* vm) {
	delete reinterpret_cast<phoenix::vm*>(vm);
}
