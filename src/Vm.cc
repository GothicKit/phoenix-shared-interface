// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Vm.h>
#include <phoenix/ext/daedalus_classes.hh>
#include <phoenix/vm.hh>

#include <memory>
#include <stdexcept>
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

PxVmInstance* pxVmStackPopInstance(PxVm* vm) {
	return RC(PxVmInstance, vm->vm.pop_instance().get());
}

char const* pxVmStackPopString(PxVm* vm) {
	return vm->vm.pop_string().c_str();
}

float pxVmStackPopFloat(PxVm* vm) {
	return vm->vm.pop_float();
}

int32_t pxVmStackPopInt(PxVm* vm) {
	return vm->vm.pop_int();
}

void pxVmStackPushInstance(PxVm* vm, PxVmInstance* instance) {
	auto* inst = RC(px::instance, instance);
	auto* sym = vm->vm.find_symbol_by_index(inst->symbol_index());
	vm->vm.push_instance(sym->get_instance());
}

void pxVmStackPushString(PxVm* vm, char const* string) {
	vm->vm.push_string(string);
}

void pxVmStackPushFloat(PxVm* vm, float f) {
	vm->vm.push_float(f);
}

void pxVmStackPushInt(PxVm* vm, int i) {
	vm->vm.push_int(i);
}

void pxVmRegisterExternal(PxVm* vm, char const* name, PxVmExternalCallback cb) {
	auto* sym = vm->vm.find_symbol_by_name(name);
	if (sym == nullptr) return;
	vm->externals[sym] = cb;
}

void pxVmRegisterExternalDefault(PxVm* vm, PxVmExternalDefaultCallback cb) {
	vm->defaultExternal = cb;
}

PxVmInstance* pxVmInstanceAllocate(PxVm* vm, char const* name, PxVmInstanceType type) {
	try {
		auto* sym = vm->vm.find_symbol_by_name(name);
		if (sym == nullptr) return nullptr;

		phoenix::instance* instance = nullptr;
		switch (type) {
		case PxVmInstanceTypeNpc:
			instance = vm->vm.allocate_instance<phoenix::c_npc>(sym).get();
			break;
		}

		return RC(PxVmInstance, instance);
	} catch (std::runtime_error const& exc) {
		return nullptr;
	}
}

PxVmInstance* pxVmInstanceInitialize(PxVm* vm, char const* name, PxVmInstanceType type, PxVmInstance* existing) {
	if (existing == nullptr) existing = pxVmInstanceAllocate(vm, name, type);
	if (existing == nullptr) return nullptr;

	try {
		auto* sym = vm->vm.find_symbol_by_name(name);
		if (sym == nullptr) return nullptr;

		switch (type) {
		case PxVmInstanceTypeNpc:
			vm->vm.init_instance<phoenix::c_npc>(std::reinterpret_pointer_cast<px::c_npc>(sym->get_instance()), sym);
			break;
		}

		return existing;
	} catch (std::runtime_error const& exc) {
		return nullptr;
	}
}

uint32_t pxVmInstanceNpcGetNameLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->name_count;
}

char const* pxVmInstanceNpcGetName(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_npc, instance)->name[i].c_str();
}

int32_t pxVmInstanceNpcGetRoutine(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->daily_routine;
}
