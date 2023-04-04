// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include <phoenix/cffi/Vm.h>
#include <phoenix/ext/daedalus_classes.hh>
#include <phoenix/vm.hh>

#include <unordered_map>

struct PxInternal_Vm {
	phoenix::vm vm;
	std::unordered_map<phoenix::symbol*, PxVmExternalCallback> externals {};
	PxVmExternalDefaultCallback defaultExternal {nullptr};
};

PxVm* pxVmLoad(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<phoenix::buffer*>(buffer)->duplicate();
		auto scr = phoenix::script::parse(buf);
		phoenix::register_all_script_classes(scr);

		auto* result = new PxVm {phoenix::vm(std::move(scr))};
		result->vm.register_exception_handler(phoenix::lenient_vm_exception_handler);
		result->vm.register_default_external([result](std::string_view name) {
			auto* sym = result->vm.find_symbol_by_name(name);
			if (sym == nullptr) {
				result->defaultExternal(result, name.data());
				return;
			}

			auto handler = result->externals.find(sym);
			if (handler == result->externals.end()) {
				result->defaultExternal(result, name.data());
				return;
			}

			handler->second(result);
		});

		return result;
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxVm* pxVmLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxVm* result = pxVmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxVmDestroy(PxVm* vm) {
	delete vm;
}

char const* pxVmPopString(PxVm* vm) {
	return vm->vm.pop_string().c_str();
}

float pxVmPopFloat(PxVm* vm) {
	return vm->vm.pop_float();
}

int32_t pxVmPopInt(PxVm* vm) {
	return vm->vm.pop_int();
}

void pxVmRegisterExternal(PxVm* vm, char const* name, PxVmExternalCallback cb) {
	auto* sym = vm->vm.find_symbol_by_name(name);
	if (sym == nullptr) return;
	vm->externals[sym] = cb;
}

void pxVmRegisterExternalDefault(PxVm* vm, PxVmExternalDefaultCallback cb) {
	vm->defaultExternal = cb;
}
