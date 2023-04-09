// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Vm.h>
#include <phoenix/ext/daedalus_classes.hh>
#include <phoenix/vm.hh>

#include <cstdarg>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

struct PxInternal_Vm {
	phoenix::vm vm;
	std::unordered_map<phoenix::symbol*, PxVmExternalCallback> externals {};
	PxVmExternalDefaultCallback defaultExternal {[](PxVm*, char const* name) {
		px::logging::log(px::logging::level::error, "external ", name, " not registered");
	}};
};

PxVm* pxVmLoad(PxBuffer* buffer) {
	try {
		auto buf = buffer->duplicate();
		auto scr = phoenix::script::parse(buf);
		phoenix::register_all_script_classes(scr);

		auto* result = new PxVm {phoenix::vm(std::move(scr))};
		result->vm.register_exception_handler(phoenix::lenient_vm_exception_handler);
		result->vm.register_default_external_custom([result](px::vm&, px::symbol& sym) {
			auto handler = result->externals.find(&sym);
			if (handler == result->externals.end()) {
				result->defaultExternal(result, sym.name().c_str());
				return;
			}

			handler->second(result);
		});

		return result;
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxVm: ", e.what());
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
	try {
		return vm->vm.pop_instance().get();
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error, "encountered exception during pxVmPopInstance(): ", e.what());
		return nullptr;
	}
}

char const* pxVmStackPopString(PxVm* vm) {
	try {
		return vm->vm.pop_string().c_str();
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error, "encountered exception during pxVmPopString(): ", e.what());
		return nullptr;
	}
}

float pxVmStackPopFloat(PxVm* vm) {
	try {
		return vm->vm.pop_float();
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error, "encountered exception during pxVmPopFloat(): ", e.what());
		return 0;
	}
}

int32_t pxVmStackPopInt(PxVm* vm) {
	try {
		return vm->vm.pop_int();
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error, "encountered exception during pxVmPopInt(): ", e.what());
		return 0;
	}
}

void pxVmStackPushInstance(PxVm* vm, PxVmInstance* instance) {
	auto* sym = vm->vm.find_symbol_by_index(instance->symbol_index());
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
	if (sym == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find external in pxVmRegisterExternal()");
		return;
	}
	vm->externals[sym] = cb;
}

void pxVmRegisterExternalDefault(PxVm* vm, PxVmExternalDefaultCallback cb) {
	vm->defaultExternal = cb;
}

PxVmInstance* pxVmGetGlobalSelf(PxVm* vm) {
	return vm->vm.global_self()->get_instance().get();
}

PxVmInstance* pxVmGetGlobalOther(PxVm* vm) {
	return vm->vm.global_other()->get_instance().get();
}

PxVmInstance* pxVmGetGlobalVictim(PxVm* vm) {
	return vm->vm.global_victim()->get_instance().get();
}

PxVmInstance* pxVmGetGlobalHero(PxVm* vm) {
	return vm->vm.global_hero()->get_instance().get();
}

PxVmInstance* pxVmGetGlobalItem(PxVm* vm) {
	return vm->vm.global_item()->get_instance().get();
}

PxVmInstance* pxVmSetGlobalSelf(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalSelf(vm);
	auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
	vm->vm.global_self()->set_instance(instSym->get_instance());
	return old;
}

PxVmInstance* pxVmSetGlobalOther(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalOther(vm);
	auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
	vm->vm.global_other()->set_instance(instSym->get_instance());
	return old;
}

PxVmInstance* pxVmSetGlobalVictim(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalVictim(vm);
	auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
	vm->vm.global_victim()->set_instance(instSym->get_instance());
	return old;
}

PxVmInstance* pxVmSetGlobalHero(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalHero(vm);
	auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
	vm->vm.global_hero()->set_instance(instSym->get_instance());
	return old;
}

PxVmInstance* pxVmSetGlobalItem(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalItem(vm);
	auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
	vm->vm.global_item()->set_instance(instSym->get_instance());
	return old;
}

static bool pxInternalVmCallFunction(PxVm* vm, px::symbol* sym, char const* args, va_list ap) {
	try {
		if (args == nullptr || *args == '\0' /* empty string */) {
			vm->vm.unsafe_call(sym);
			return true;
		}

		if (*args++ != '(') return false;
		while (*args != '\0') {
			auto type = *args++;

			if (type == ')') {
				// next is return type
				args += 1;
				break;
			}

			// FIXME: This breaks if an invalid args-string is provided since values might already have been pushed!
			switch (type) {
			case 'f':
				pxVmStackPushFloat(vm, (float) va_arg(ap, double));
				break;
			case 'd':
				pxVmStackPushInt(vm, va_arg(ap, int32_t));
				break;
			case 's':
				pxVmStackPushString(vm, va_arg(ap, char const*));
				break;
			case 'I':
				pxVmStackPushInstance(vm, va_arg(ap, PxVmInstance*));
				break;
			default:
				return false;
			}
		}

		vm->vm.unsafe_call(sym);

		if (*args != '\0') {
			switch (*args) {
			case 'f':
				*va_arg(ap, float*) = pxVmStackPopFloat(vm);
				break;
			case 'd':
				*va_arg(ap, int*) = pxVmStackPopInt(vm);
				break;
			case 's':
				*va_arg(ap, char const**) = pxVmStackPopString(vm);
				break;
			case 'I':
				*va_arg(ap, PxVmInstance**) = pxVmStackPopInstance(vm);
				break;
			case 'v':
				break;
			default:
				return false;
			}
		}

		return true;
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error, "encountered exception during pxVmCallFunction(): ", e.what());
		return false;
	}
}

PxBool pxVmCallFunction(PxVm* vm, char const* func, ...) {
	va_list ap;
	va_start(ap, func);

	auto* args = strchr(func, '(');
	px::symbol* sym;

	if (args == nullptr) {
		sym = vm->vm.find_symbol_by_name(func);
	} else {
		sym = vm->vm.find_symbol_by_name({func, static_cast<unsigned long>(args - func)});
	}

	auto r = pxInternalVmCallFunction(vm, sym, args, ap);

	va_end(ap);
	return r;
}

PxBool pxVmCallFunctionByIndex(PxVm* vm, uint32_t index, char const* args, ...) {
	va_list ap;
	va_start(ap, args);

	auto* sym = vm->vm.find_symbol_by_index(index);
	auto r = pxInternalVmCallFunction(vm, sym, args, ap);

	va_end(ap);
	return r;
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

		return instance;
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error, "encountered exception during pxVmInstanceAllocate(): ", e.what());
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
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error, "encountered exception during pxVmInitialize(): ", e.what());
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
