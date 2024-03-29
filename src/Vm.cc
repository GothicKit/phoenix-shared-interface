// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Vm.h>
#include <phoenix/ext/daedalus_classes.hh>
#include <phoenix/vm.hh>

#include <cstdarg>
#include <cstring>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

static void fixVmStackForMissingExternal(px::vm& v, phoenix::symbol& sym) {
	auto params = v.find_parameters_for_function(&sym);
	for (int32_t i = (int32_t) params.size() - 1; i >= 0; --i) {
		auto par = params[(uint32_t) i];

		if (par->type() == px::datatype::integer)
			(void) v.pop_int();
		else if (par->type() == px::datatype::float_)
			(void) v.pop_float();
		else if (par->type() == px::datatype::instance || par->type() == px::datatype::string)
			(void) v.pop_reference();
	}

	if (sym.has_return()) {
		if (sym.rtype() == px::datatype::float_)
			v.push_float(0.0f);
		else if (sym.rtype() == px::datatype::integer)
			v.push_int(0);
		else if (sym.rtype() == px::datatype::string)
			v.push_string("");
		else if (sym.rtype() == px::datatype::instance)
			v.push_instance(nullptr);
	}
}

struct PxInternal_Vm {
	phoenix::vm vm;
	std::unordered_map<phoenix::symbol*, PxVmExternalCallback> externals {};
	PxVmExternalDefaultCallback defaultExternal {[](PxVm*, char const* name) {
		px::logging::log(px::logging::level::warn, "CAPI:PxVm", "external %s not registered", name);
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
				fixVmStackForMissingExternal(result->vm, sym);
				result->defaultExternal(result, sym.name().c_str());
				return;
			}

			handler->second(result);
		});

		return result;
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception while parsing PxVm: %s",
		                 e.what());
		return nullptr;
	}
}

PxVm* pxVmLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetNodeByName(vfs, name);
	if (node == nullptr) return nullptr;

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
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
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception during pxVmPopInstance(): %s",
		                 e.what());
		return nullptr;
	}
}

char const* pxVmStackPopString(PxVm* vm) {
	try {
		return vm->vm.pop_string().c_str();
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception during pxVmPopString(): %s",
		                 e.what());
		return nullptr;
	}
}

float pxVmStackPopFloat(PxVm* vm) {
	try {
		return vm->vm.pop_float();
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception during pxVmPopFloat(): %s",
		                 e.what());
		return 0;
	}
}

int32_t pxVmStackPopInt(PxVm* vm) {
	try {
		return vm->vm.pop_int();
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception during pxVmPopInt(): %s",
		                 e.what());
		return 0;
	}
}

void pxVmStackPushInstance(PxVm* vm, PxVmInstance* instance) {
	if (instance == nullptr) {
		vm->vm.push_instance(nullptr);
		return;
	}

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
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "failed to find external in pxVmRegisterExternal(): %s",
		                 name);
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

	if (instance != nullptr) {
		auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
		vm->vm.global_self()->set_instance(instSym->get_instance());
	} else {
		vm->vm.global_self()->set_instance(nullptr);
	}

	return old;
}

PxVmInstance* pxVmSetGlobalOther(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalOther(vm);

	if (instance != nullptr) {
		auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
		vm->vm.global_other()->set_instance(instSym->get_instance());
	} else {
		vm->vm.global_other()->set_instance(nullptr);
	}

	return old;
}

PxVmInstance* pxVmSetGlobalVictim(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalVictim(vm);
	if (instance != nullptr) {
		auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
		vm->vm.global_victim()->set_instance(instSym->get_instance());
	} else {
		vm->vm.global_victim()->set_instance(nullptr);
	}
	return old;
}

PxVmInstance* pxVmSetGlobalHero(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalHero(vm);

	if (instance != nullptr) {
		auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
		vm->vm.global_hero()->set_instance(instSym->get_instance());
	} else {
		vm->vm.global_hero()->set_instance(nullptr);
	}

	return old;
}

PxVmInstance* pxVmSetGlobalItem(PxVm* vm, PxVmInstance* instance) {
	auto* old = pxVmGetGlobalItem(vm);

	if (instance != nullptr) {
		auto* instSym = vm->vm.find_symbol_by_index(instance->symbol_index());
		vm->vm.global_item()->set_instance(instSym->get_instance());
	} else {
		vm->vm.global_item()->set_instance(nullptr);
	}

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
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception during pxVmCallFunction(): %s",
		                 e.what());
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

static PxVmInstance* pxInternalVmInstanceAllocate(PxVm* vm, phoenix::symbol* sym, PxVmInstanceType type) {
	try {
		phoenix::instance* instance = nullptr;
		switch (type) {
		case PxVm_InstanceTypeNpc:
			instance = vm->vm.allocate_instance<phoenix::c_npc>(sym).get();
			break;
		case PxVm_InstanceTypeItem:
			instance = vm->vm.allocate_instance<phoenix::c_item>(sym).get();
			break;
		case PxVm_InstanceTypeSfx:
			instance = vm->vm.allocate_instance<phoenix::c_sfx>(sym).get();
			break;
		case PxVm_InstanceTypeMusic:
			instance = vm->vm.allocate_instance<phoenix::c_music_theme>(sym).get();
			break;
		case PxVm_InstanceTypeMenu:
			instance = vm->vm.allocate_instance<phoenix::c_menu>(sym).get();
			break;
		case PxVm_InstanceTypeMenuItem:
			instance = vm->vm.allocate_instance<phoenix::c_menu_item>(sym).get();
			break;
		case PxVm_InstanceTypePfx:
			instance = vm->vm.allocate_instance<phoenix::c_particle_fx>(sym).get();
			break;
		}

		return instance;
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception during pxVmInstanceAllocate(): %s",
		                 e.what());
		return nullptr;
	}
}

PxVmInstance* pxVmInstanceAllocateByIndex(PxVm* vm, uint32_t index, PxVmInstanceType type) {
	auto* sym = vm->vm.find_symbol_by_index(index);
	if (sym == nullptr) return nullptr;
	return pxInternalVmInstanceAllocate(vm, sym, type);
}

PxVmInstance* pxVmInstanceAllocateByName(PxVm* vm, char const* name, PxVmInstanceType type) {
	auto* sym = vm->vm.find_symbol_by_name(name);
	if (sym == nullptr) return nullptr;
	return pxInternalVmInstanceAllocate(vm, sym, type);
}

static PxVmInstance*
pxInternalVmInstanceInitialize(PxVm* vm, phoenix::symbol* sym, PxVmInstanceType type, PxVmInstance* existing) {
	if (existing == nullptr) existing = pxInternalVmInstanceAllocate(vm, sym, type);
	if (existing == nullptr) return nullptr;

	try {
		switch (type) {
		case PxVm_InstanceTypeNpc: {
			auto* v = reinterpret_cast<px::c_npc*>(sym->get_instance().get());
			vm->vm.init_instance<phoenix::c_npc>({sym->get_instance(), v}, sym);
			break;
		}
		case PxVm_InstanceTypeItem: {
			auto* v = reinterpret_cast<px::c_item*>(sym->get_instance().get());
			vm->vm.init_instance<phoenix::c_item>({sym->get_instance(), v}, sym);
			break;
		}
		case PxVm_InstanceTypeSfx: {
			auto* v = reinterpret_cast<px::c_sfx*>(sym->get_instance().get());
			vm->vm.init_instance<phoenix::c_sfx>({sym->get_instance(), v}, sym);
			break;
		}
		case PxVm_InstanceTypeMusic: {
			auto* v = reinterpret_cast<px::c_music_theme*>(sym->get_instance().get());
			vm->vm.init_instance<phoenix::c_music_theme>({sym->get_instance(), v}, sym);
			break;
		}
		case PxVm_InstanceTypeMenu: {
			auto* v = reinterpret_cast<px::c_menu*>(sym->get_instance().get());
			vm->vm.init_instance<phoenix::c_menu>({sym->get_instance(), v}, sym);
			break;
		}
		case PxVm_InstanceTypeMenuItem: {
			auto* v = reinterpret_cast<px::c_menu_item*>(sym->get_instance().get());
			vm->vm.init_instance<phoenix::c_menu_item>({sym->get_instance(), v}, sym);
			break;
		}
		case PxVm_InstanceTypePfx:
			auto* v = reinterpret_cast<px::c_particle_fx*>(sym->get_instance().get());
			vm->vm.init_instance<phoenix::c_particle_fx>({sym->get_instance(), v}, sym);
			break;
		}

		return existing;
	} catch (std::runtime_error const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxVm",
		                 "encountered exception during pxVmInitialize(): %s",
		                 e.what());
		return nullptr;
	}
}

PxVmInstance* pxVmInstanceInitializeByIndex(PxVm* vm, uint32_t index, PxVmInstanceType type, PxVmInstance* existing) {
	auto* sym = vm->vm.find_symbol_by_index(index);
	if (sym == nullptr) return nullptr;
	return pxInternalVmInstanceInitialize(vm, sym, type, existing);
}

PxVmInstance* pxVmInstanceInitializeByName(PxVm* vm, char const* name, PxVmInstanceType type, PxVmInstance* existing) {
	auto* sym = vm->vm.find_symbol_by_name(name);
	if (sym == nullptr) return nullptr;
	return pxInternalVmInstanceInitialize(vm, sym, type, existing);
}

uint32_t pxVmInstanceGetSymbolIndex(PxVmInstance const* instance) {
	return instance->symbol_index();
}

void pxVmPrintStackTrace(PxVm const* vm) {
	vm->vm.print_stack_trace();
}

void pxVmEnumerateInstancesByClassName(PxVm* vm, char const* name, PxVmEnumerateInstancesCallback cb) {
	std::function<void(phoenix::symbol&)> internalCallback = {
	    [cb](phoenix::symbol& symbol) { cb(symbol.name().c_str()); }};

	vm->vm.enumerate_instances_by_class_name(name, internalCallback);
}

// C_Npc
int32_t pxVmInstanceNpcGetId(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->id;
}

uint32_t pxVmInstanceNpcGetNameLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->name_count;
}

char const* pxVmInstanceNpcGetName(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_npc, instance)->name[i].c_str();
}

char const* pxVmInstanceNpcGetSlot(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->slot.c_str();
}

uint32_t pxVmInstanceNpcGetNpcType(PxVmInstance const* instance) {
	return static_cast<uint32_t>(RCC(phoenix::c_npc, instance)->type);
}

uint32_t pxVmInstanceNpcGetFlags(PxVmInstance const* instance) {
	return static_cast<uint32_t>(RCC(phoenix::c_npc, instance)->flags);
}

uint32_t pxVmInstanceNpcGetAttributeLength(PxVmInstance const* instance) {
	return zenkit::NpcAttribute::_NUM;
}

int32_t pxVmInstanceNpcGetAttribute(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_npc, instance)->attribute[i];
}

uint32_t pxVmInstanceNpcGetProtectionLength(PxVmInstance const* instance) {
	return zenkit::DamageType::_NUM;
}

int32_t pxVmInstanceNpcGetProtection(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_npc, instance)->protection[i];
}

uint32_t pxVmInstanceNpcGetDamageLength(PxVmInstance const* instance) {
	return zenkit::DamageType::_NUM;
}

int32_t pxVmInstanceNpcGetDamage(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_npc, instance)->damage[i];
}

int32_t pxVmInstanceNpcGetDamageType(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->damage_type;
}

int32_t pxVmInstanceNpcGetGuild(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->guild;
}

int32_t pxVmInstanceNpcGetLevel(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->level;
}

uint32_t pxVmInstanceNpcGetMissionLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->mission_count;
}

int32_t pxVmInstanceNpcGetMission(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_npc, instance)->mission[i];
}

int32_t pxVmInstanceNpcGetFightTactic(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->fight_tactic;
}

int32_t pxVmInstanceNpcGetWeapon(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->weapon;
}

int32_t pxVmInstanceNpcGetVoice(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->voice;
}

int32_t pxVmInstanceNpcGetVoicePitch(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->voice_pitch;
}

int32_t pxVmInstanceNpcGetBodyMass(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->body_mass;
}

int32_t pxVmInstanceNpcGetRoutine(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->daily_routine;
}

int32_t pxVmInstanceNpcGetStartAiState(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->start_aistate;
}

char const* pxVmInstanceNpcGetSpawnPoint(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->spawnpoint.c_str();
}

int32_t pxVmInstanceNpcGetSpawnDelay(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->spawn_delay;
}

int32_t pxVmInstanceNpcGetSenses(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->senses;
}

int32_t pxVmInstanceNpcGetSensesRange(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->senses_range;
}

uint32_t pxVmInstanceNpcGetAiLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->aivar_count;
}

int32_t pxVmInstanceNpcGetAiVar(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_npc, instance)->aivar[i];
}

char const* pxVmInstanceNpcGetWP(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->wp.c_str();
}

void pxVmInstanceNpcSetWP(PxVmInstance* instance, char const* wpName) {
	RC(phoenix::c_npc, instance)->wp = wpName;
}

int32_t pxVmInstanceNpcGetExp(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->exp;
}

int32_t pxVmInstanceNpcGetExpNext(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->exp_next;
}

int32_t pxVmInstanceNpcGetLp(PxVmInstance const* instance) {
	return RCC(phoenix::c_npc, instance)->lp;
}

// C_Item
int32_t pxVmInstanceItemGetId(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->id;
}

char const* pxVmInstanceItemGetName(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->name.c_str();
}

char const* pxVmInstanceItemGetNameId(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->name_id.c_str();
}

int32_t pxVmInstanceItemGetHp(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->hp;
}

int32_t pxVmInstanceItemGetHpMax(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->hp_max;
}

int32_t pxVmInstanceItemGetMainFlag(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->main_flag;
}

uint32_t pxVmInstanceItemGetFlags(PxVmInstance const* instance) {
	return static_cast<uint32_t>(RCC(phoenix::c_item, instance)->flags);
}

int32_t pxVmInstanceItemGetWeight(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->weight;
}

int32_t pxVmInstanceItemGetValue(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->value;
}

int32_t pxVmInstanceItemGetDamageType(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->damage_type;
}

int32_t pxVmInstanceItemGetDamageTotal(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->damage_total;
}

uint32_t pxVmInstanceItemGetDamageLength() {
	return phoenix::damage_type::count;
}

int32_t pxVmInstanceItemGetDamage(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->damage[i];
}

int32_t pxVmInstanceItemGetWear(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->wear;
}

uint32_t pxVmInstanceItemGetProtectionLength() {
	return phoenix::damage_type::count;
}

int32_t pxVmInstanceItemGetProtection(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->protection[i];
}

int32_t pxVmInstanceItemGetNutrition(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->nutrition;
}

uint32_t pxVmInstanceItemGetCondAtrLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->condition_count;
}

int32_t pxVmInstanceItemGetCondAtr(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->cond_atr[i];
}

uint32_t pxVmInstanceItemGetCondValueLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->condition_count;
}

int32_t pxVmInstanceItemGetCondValue(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->cond_value[i];
}

uint32_t pxVmInstanceItemGetChangeAtrLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->condition_count;
}

int32_t pxVmInstanceItemGetChangeAtr(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->change_atr[i];
}

uint32_t pxVmInstanceItemGetChangeValueLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->condition_count;
}

int32_t pxVmInstanceItemGetChangeValue(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->change_value[i];
}

int32_t pxVmInstanceItemGetMagic(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->magic;
}

int32_t pxVmInstanceItemGetOnEquip(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->on_equip;
}

int32_t pxVmInstanceItemGetOnUnequip(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->on_unequip;
}

uint32_t pxVmInstanceItemGetOnStateLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->state_count;
}

int32_t pxVmInstanceItemGetOnState(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->on_state[i];
}

int32_t pxVmInstanceItemGetOwner(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->owner;
}

int32_t pxVmInstanceItemGetOwnerGuild(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->owner_guild;
}

int32_t pxVmInstanceItemGetDisguiseGuild(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->disguise_guild;
}

char const* pxVmInstanceItemGetVisual(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->visual.c_str();
}

char const* pxVmInstanceItemGetVisualChange(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->visual_change.c_str();
}

char const* pxVmInstanceItemGetEffect(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->effect.c_str();
}

int32_t pxVmInstanceItemGetVisualSkin(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->visual_skin;
}

char const* pxVmInstanceItemGetSchemeName(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->scheme_name.c_str();
}

int32_t pxVmInstanceItemGetMaterial(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->material;
}

int32_t pxVmInstanceItemGetMunition(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->munition;
}

int32_t pxVmInstanceItemGetSpell(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->spell;
}

int32_t pxVmInstanceItemGetRange(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->range;
}

int32_t pxVmInstanceItemGetMagCircle(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->mag_circle;
}

char const* pxVmInstanceItemGetDescription(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->description.c_str();
}

uint32_t pxVmInstanceItemGetTextLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->text_count;
}

char const* pxVmInstanceItemGetText(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->text[i].c_str();
}

uint32_t pxVmInstanceItemGetCountLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->text_count;
}

int32_t pxVmInstanceItemGetCount(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_item, instance)->count[i];
}

int32_t pxVmInstanceItemGetInvZbias(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->inv_zbias;
}

int32_t pxVmInstanceItemGetInvRotX(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->inv_rot_x;
}

int32_t pxVmInstanceItemGetInvRotY(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->inv_rot_y;
}

int32_t pxVmInstanceItemGetInvRotZ(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->inv_rot_z;
}

int32_t pxVmInstanceItemGetInvAnimate(PxVmInstance const* instance) {
	return RCC(phoenix::c_item, instance)->inv_animate;
}

// C_Menu
char const* pxVmInstanceMenuGetBackPic(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->back_pic.c_str();
}

char const* pxVmInstanceMenuGetBackWorld(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->back_world.c_str();
}

int32_t pxVmInstanceMenuGetPosX(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->pos_x;
}

int32_t pxVmInstanceMenuGetPosY(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->pos_y;
}

int32_t pxVmInstanceMenuGetDimX(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->dim_x;
}

int32_t pxVmInstanceMenuGetDimY(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->dim_y;
}

int32_t pxVmInstanceMenuGetAlpha(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->alpha;
}

char const* pxVmInstanceMenuGetMusicTheme(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->music_theme.c_str();
}

int32_t pxVmInstanceMenuGetEventTimerMsec(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->event_timer_msec;
}

uint8_t pxVmInstanceMenuGetItemsLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->item_count;
}

char const* pxVmInstanceMenuGetItems(PxVmInstance const* instance, uint8_t i) {
	return RCC(phoenix::c_menu, instance)->items[i].c_str();
}

uint32_t pxVmInstanceMenuGetFlags(PxVmInstance const* instance) {
	return static_cast<uint32_t>(RCC(phoenix::c_menu, instance)->flags);
}

int32_t pxVmInstanceMenuGetDefaultOutgame(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->default_outgame;
}

int32_t pxVmInstanceMenuGetDefaultIngame(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu, instance)->default_ingame;
}

// C_Menu_Item
char const* pxVmInstanceMenuItemGetFontname(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->fontname.c_str();
}

uint32_t pxVmInstanceMenuItemGetTextLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->text_count;
}

char const* pxVmInstanceMenuItemGetText(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_menu_item, instance)->text[i].c_str();
}

char const* pxVmInstanceMenuItemGetBackpic(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->backpic.c_str();
}

char const* pxVmInstanceMenuItemGetAlphamode(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->alphamode.c_str();
}

int32_t pxVmInstanceMenuItemGetAlpha(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->alpha;
}

uint32_t pxVmInstanceMenuItemGetType(PxVmInstance const* instance) {
	return static_cast<uint32_t>(RCC(phoenix::c_menu_item, instance)->type);
}

uint32_t pxVmInstanceMenuItemGetOnSelActionLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->select_action_count;
}

int32_t pxVmInstanceMenuItemGetOnSelAction(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_menu_item, instance)->on_sel_action[i];
}

uint32_t pxVmInstanceMenuItemGetOnSelActionSLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->select_action_count;
}

char const* pxVmInstanceMenuItemGetOnSelActionS(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_menu_item, instance)->on_sel_action_s[i].c_str();
}

char const* pxVmInstanceMenuItemGetOnChgSetOption(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->on_chg_set_option.c_str();
}

char const* pxVmInstanceMenuItemGetOnChgSetOptionSection(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->on_chg_set_option_section.c_str();
}

uint32_t pxVmInstanceMenuItemGetOnEventActionLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->event_action_count;
}

int32_t pxVmInstanceMenuItemGetOnEventAction(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_menu_item, instance)->on_event_action[i];
}

int32_t pxVmInstanceMenuItemGetPosX(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->pos_x;
}

int32_t pxVmInstanceMenuItemGetPosY(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->pos_y;
}

int32_t pxVmInstanceMenuItemGetDimX(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->dim_x;
}

int32_t pxVmInstanceMenuItemGetDimY(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->dim_y;
}

float pxVmInstanceMenuItemGetSizeStartScale(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->size_start_scale;
}

uint32_t pxVmInstanceMenuItemGetFlags(PxVmInstance const* instance) {
	return static_cast<uint32_t>(RCC(phoenix::c_menu_item, instance)->flags);
}

float pxVmInstanceMenuItemGetOpenDelayTime(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->open_delay_time;
}

float pxVmInstanceMenuItemGetOpenDuration(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->open_duration;
}

uint32_t pxVmInstanceMenuItemGetUserFloatLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->user_item_count;
}

float pxVmInstanceMenuItemGetUserFloat(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_menu_item, instance)->user_float[i];
}

uint32_t pxVmInstanceMenuItemGetUserStringLength(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->user_item_count;
}

char const* pxVmInstanceMenuItemGetUserString(PxVmInstance const* instance, uint32_t i) {
	return RCC(phoenix::c_menu_item, instance)->user_string[i].c_str();
}

int32_t pxVmInstanceMenuItemGetFrameSizex(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->frame_sizex;
}

int32_t pxVmInstanceMenuItemGetFrameSizey(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->frame_sizey;
}

char const* pxVmInstanceMenuItemGetHideIfOptionSectionSet(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->hide_if_option_section_set.c_str();
}

char const* pxVmInstanceMenuItemGetHideIfOptionSet(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->hide_if_option_set.c_str();
}

int32_t pxVmInstanceMenuItemGetHideOnValue(PxVmInstance const* instance) {
	return RCC(phoenix::c_menu_item, instance)->hide_on_value;
}

// C_Sfx
char const* pxVmInstanceSfxGetFile(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->file.c_str();
}

int32_t pxVmInstanceSfxGetPitchOff(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->pitch_off;
}

int32_t pxVmInstanceSfxGetPitchVar(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->pitch_var;
}

int32_t pxVmInstanceSfxGetVol(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->vol;
}

int32_t pxVmInstanceSfxGetLoop(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->loop;
}

int32_t pxVmInstanceSfxGetLoopStartOffset(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->loop_start_offset;
}

int32_t pxVmInstanceSfxGetLoopEndOffset(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->loop_end_offset;
}

float pxVmInstanceSfxGetReverbLevel(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->reverb_level;
}

char const* pxVmInstanceSfxGetPfxName(PxVmInstance const* instance) {
	return RCC(phoenix::c_sfx, instance)->pfx_name.c_str();
}

// C_MUSIC_THEME
char const* pxVmInstanceMusicGetFile(PxVmInstance const* instance) {
	return RCC(phoenix::c_music_theme, instance)->file.c_str();
}

float pxVmInstanceMusicGetVol(PxVmInstance const* instance) {
	return RCC(phoenix::c_music_theme, instance)->vol;
}

int32_t pxVmInstanceMusicGetLoop(PxVmInstance const* instance) {
	return RCC(phoenix::c_music_theme, instance)->loop;
}

float pxVmInstanceMusicGetReverbMix(PxVmInstance const* instance) {
	return RCC(phoenix::c_music_theme, instance)->reverbmix;
}

float pxVmInstanceMusicGetReverbTime(PxVmInstance const* instance) {
	return RCC(phoenix::c_music_theme, instance)->reverbtime;
}

int32_t pxVmInstanceMusicGetTransitionType(PxVmInstance const* instance) {
	return (int32_t) RCC(phoenix::c_music_theme, instance)->transtype;
}

int32_t pxVmInstanceMusicGetTransitionSubType(PxVmInstance const* instance) {
	return (int32_t) RCC(phoenix::c_music_theme, instance)->transsubtype;
}

// C_PARTICLEFX
PXC_API float pxVmInstancePfxGetPpsValue(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->pps_value;
}

char const* pxVmInstancePfxGetPpsScaleKeys(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->pps_scale_keys_s.c_str();
}

PxBool pxVmInstancePfxGetPpsIsLooping(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->pps_is_looping;
}

PxBool pxVmInstancePfxGetPpsIsSmooth(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->pps_is_smooth;
}

float pxVmInstancePfxGetPpsFps(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->pps_fps;
}

char const* pxVmInstancePfxGetPpsCrateEm(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->pps_create_em_s.c_str();
}

float pxVmInstancePfxGetPpsCreateEmDelay(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->pps_create_em_delay;
}

char const* pxVmInstancePfxGetShpType(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_type_s.c_str();
}

char const* pxVmInstancePfxGetShpFor(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_for_s.c_str();
}

char const* pxVmInstancePfxGetShpOffsetVec(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_offset_vec_s.c_str();
}

char const* pxVmInstancePfxGetShpDistribType(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_distrib_type_s.c_str();
}

float pxVmInstancePfxGetShpDistribWalkSpeed(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_distrib_walk_speed;
}

PxBool pxVmInstancePfxGetShpIsVolume(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->shp_is_volume;
}

char const* pxVmInstancePfxGetShpDim(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_dim_s.c_str();
}

char const* pxVmInstancePfxGetShpMesh(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_mesh_s.c_str();
}

PxBool pxVmInstancePfxGetShpMeshRender(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->shp_mesh_render_b;
}

char const* pxVmInstancePfxGetShpScaleKeys(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_scale_keys_s.c_str();
}

PxBool pxVmInstancePfxGetShpScaleIsLooping(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->shp_scale_is_looping;
}

PxBool pxVmInstancePfxGetShpScaleIsSmooth(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->shp_scale_is_smooth;
}

float pxVmInstancePfxGetShpScaleFps(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->shp_scale_fps;
}

char const* pxVmInstancePfxGetDirMode(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_mode_s.c_str();
}

char const* pxVmInstancePfxGetDirFor(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_for_s.c_str();
}

char const* pxVmInstancePfxGetDirModeTargetFor(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_mode_target_for_s.c_str();
}

char const* pxVmInstancePfxGetDirModeTargetPos(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_mode_target_pos_s.c_str();
}

float pxVmInstancePfxGetDirAngleHead(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_angle_head;
}

float pxVmInstancePfxGetDirAngleHeadVar(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_angle_head_var;
}

float pxVmInstancePfxGetDirAngleElev(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_angle_elev;
}

float pxVmInstancePfxGetDirAngleElevVar(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->dir_angle_elev_var;
}

float pxVmInstancePfxGetVelAvg(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vel_avg;
}

float pxVmInstancePfxGetVelVar(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vel_var;
}

float pxVmInstancePfxGetLspPartAvg(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->lsp_part_avg;
}

float pxVmInstancePfxGetLspPartVar(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->lsp_part_var;
}

char const* pxVmInstancePfxGetFlyGravity(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->fly_gravity_s.c_str();
}

PxBool pxVmInstancePfxGetFlyCollDet(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->fly_colldet_b;
}

char const* pxVmInstancePfxGetVisName(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_name_s.c_str();
}

char const* pxVmInstancePfxGetVisOrientation(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_orientation_s.c_str();
}

PxBool pxVmInstancePfxGetVisTexIsQuadPoly(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->vis_tex_is_quadpoly;
}

float pxVmInstancePfxGetVisTexAniFps(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_tex_ani_fps;
}

PxBool pxVmInstancePfxGetVisTexAniIsLooping(PxVmInstance const* instance) {
	return (PxBool) RCC(phoenix::c_particle_fx, instance)->vis_tex_ani_is_looping;
}

char const* pxVmInstancePfxGetVisTexColorStart(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_tex_color_start_s.c_str();
}

char const* pxVmInstancePfxGetVisTexColorEnd(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_tex_color_end_s.c_str();
}

char const* pxVmInstancePfxGetVisSizeStart(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_size_start_s.c_str();
}

float pxVmInstancePfxGetVisSizeEndScale(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_size_end_scale;
}

char const* pxVmInstancePfxGetVisAlphaFunc(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_alpha_func_s.c_str();
}

float pxVmInstancePfxGetVisAlphaStart(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_alpha_start;
}

float pxVmInstancePfxGetVisAlphaEnd(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->vis_alpha_end;
}

float pxVmInstancePfxGetTrlFadeSpeed(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->trl_fade_speed;
}

char const* pxVmInstancePfxGetTrlTexture(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->trl_texture_s.c_str();
}

float pxVmInstancePfxGetTrlWidth(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->trl_width;
}

float pxVmInstancePfxGetMrkFadeSpeed(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->mrk_fades_peed;
}

char const* pxVmInstancePfxGetMrkTexture(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->mrkt_exture_s.c_str();
}

float pxVmInstancePfxGetMrkSize(PxVmInstance const* instance) {
	return RCC(phoenix::c_particle_fx, instance)->mrk_size;
}
