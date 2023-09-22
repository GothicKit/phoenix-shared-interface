// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Mesh.h>
#include <phoenix/cffi/World.h>
#include <phoenix/world.hh>

PxWorld* pxWorldLoad(PxBuffer* buffer) {
	try {
		auto scr = px::world::parse(buffer->duplicate());
		return new px::world(std::move(scr));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxWorld* pxWorldLoadFromVfs(PxVfs const* vfs, char const* name) {
	auto* entry = pxVfsGetNodeByName(vfs, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVfsNodeOpenBuffer(entry);
	PxWorld* result = pxWorldLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxWorldDestroy(PxWorld* world) {
	delete world;
}

PxMesh const* pxWorldGetMesh(PxWorld const* world) {
	return &world->world_mesh;
}

uint32_t pxWorldGetWayPointCount(PxWorld const* world) {
	return (uint32_t) world->world_way_net.waypoints.size();
}

void pxWorldGetWayPoint(PxWorld const* world,
                        uint32_t i,
                        char const** name,
                        PxVec3* position,
                        PxVec3* direction,
                        PxBool* freePoint,
                        PxBool* underwater,
                        int32_t* waterDepth) {
	auto& wp = world->world_way_net.waypoints[i];
	*name = wp.name.c_str();
	position->x = wp.position.x;
	position->y = wp.position.y;
	position->z = wp.position.z;
	direction->x = wp.direction.x;
	direction->y = wp.direction.y;
	direction->z = wp.direction.z;
	*freePoint = wp.free_point;
	*underwater = wp.under_water;
	*waterDepth = wp.water_depth;
}

uint32_t pxWorldGetWayEdgeCount(PxWorld const* world) {
	return (uint32_t) world->world_way_net.edges.size();
}

void pxWorldGetWayEdge(PxWorld const* world, uint32_t i, uint32_t* a, uint32_t* b) {
	auto& we = world->world_way_net.edges[i];
	*a = we.a;
	*b = we.b;
}

uint32_t pxWorldGetRootVobCount(PxWorld const* world) {
	return (uint32_t) world->world_vobs.size();
}

PxVob* pxWorldGetRootVob(PxWorld const* world, uint32_t i) {
	return world->world_vobs[i].get();
}

PxVobType pxVobGetType(PxVob const* vob) {
	return static_cast<PxVobType>(vob->type);
}

uint32_t pxVobGetId(PxVob const* vob) {
	return vob->id;
}

PxAABB pxVobGetBbox(PxVob const* vob) {
	auto& bbox = vob->bbox;
	return PxAABB {
	    PxVec3 {bbox.min.x, bbox.min.y, bbox.min.z},
	    PxVec3 {bbox.max.x, bbox.max.y, bbox.max.z},
	};
}

PxVec3 pxVobGetPosition(PxVob const* vob) {
	auto& pos = vob->position;
	return {pos.x, pos.y, pos.z};
}

PxMat3x3 pxVobGetRotation(PxVob const* vob) {
	PxMat3x3 mat = {};
	auto& rot = vob->rotation;

	mat.m00 = rot[0][0];
	mat.m01 = rot[0][1];
	mat.m02 = rot[0][2];
	mat.m10 = rot[1][0];
	mat.m11 = rot[1][1];
	mat.m12 = rot[1][2];
	mat.m20 = rot[2][0];
	mat.m21 = rot[2][1];
	mat.m22 = rot[2][2];

	return mat;
}

PxBool pxVobGetShowVisual(PxVob const* vob) {
	return vob->show_visual;
}

PxVobSpriteAlignment pxVobGetSpriteAlignment(PxVob const* vob) {
	return static_cast<PxVobSpriteAlignment>(vob->sprite_camera_facing_mode);
}

PxBool pxVobGetCdStatic(PxVob const* vob) {
	return vob->cd_static;
}

PxBool pxVobGetCdDynamic(PxVob const* vob) {
	return vob->cd_dynamic;
}

PxBool pxVobGetVobStatic(PxVob const* vob) {
	return vob->vob_static;
}

PxVobShadowMode pxVobGetShadowMode(PxVob const* vob) {
	return static_cast<PxVobShadowMode>(vob->dynamic_shadows);
}

PxBool pxVobGetPhysicsEnabled(PxVob const* vob) {
	return vob->physics_enabled;
}

PxVobAnimationMode pxVobGetAnimationMode(PxVob const* vob) {
	return static_cast<PxVobAnimationMode>(vob->anim_mode);
}

int32_t pxVobGetBias(PxVob const* vob) {
	return vob->bias;
}

PxBool pxVobGetAmbient(PxVob const* vob) {
	return vob->ambient;
}

float pxVobGetAnimationStrength(PxVob const* vob) {
	return vob->anim_strength;
}

float pxVobGetFarClipScale(PxVob const* vob) {
	return vob->far_clip_scale;
}

char const* pxVobGetPresetName(PxVob const* vob) {
	return vob->preset_name.c_str();
}

char const* pxVobGetVobName(PxVob const* vob) {
	return vob->vob_name.c_str();
}

char const* pxVobGetVisualName(PxVob const* vob) {
	return vob->visual_name.c_str();
}

PxVobVisualType pxVobGetVisualType(PxVob const* vob) {
	return static_cast<PxVobVisualType>(vob->associated_visual_type);
}

uint32_t pxVobGetChildCount(PxVob const* vob) {
	return (uint32_t) vob->children.size();
}

PxVob* pxVobGetChild(PxVob const* vob, uint32_t i) {
	return vob->children[i].get();
}

// Decal
PxBool pxVobGetGetHasDecal(PxVob const* vob) {
	return vob->visual_decal.has_value();
}

char const* pxVobGetDecalName(PxVob const* vob) {
	return vob->visual_decal->name.c_str();
}

PxVec2 pxVobGetDecalDimension(PxVob const* vob) {
	return {vob->visual_decal->dimension.x, vob->visual_decal->dimension.y};
}

PxVec2 pxVobGetDecalOffset(PxVob const* vob) {
	return {vob->visual_decal->offset.x, vob->visual_decal->offset.y};
}

PxBool pxVobGetDecalTwoSided(PxVob const* vob) {
	return vob->visual_decal->two_sided;
}

PxMaterialAlphaFunction pxVobGetDecalAlphaFunc(PxVob const* vob) {
	return static_cast<PxMaterialAlphaFunction>(vob->visual_decal->alpha_func);
}

float pxVobGetDecalTextureAnimFps(PxVob const* vob) {
	return vob->visual_decal->texture_anim_fps;
}

std::uint8_t pxVobGetDecalAlphaWeight(PxVob const* vob) {
	return vob->visual_decal->alpha_weight;
}

PxBool pxVobGetDecalIgnoreDaylight(PxVob const* vob) {
	return vob->visual_decal->ignore_daylight;
}

// Light Preset
char const* pxLightPresetGetPreset(PxVobLightPreset const* lightPreset) {
	return lightPreset->preset.c_str();
}

PxVobLightMode pxLightPresetGetLightType(PxVobLightPreset const* lightPreset) {
	return static_cast<PxVobLightMode>(lightPreset->light_type);
}

float pxLightPresetGetRange(PxVobLightPreset const* lightPreset) {
	return lightPreset->range;
}

PxColor pxLightPresetGetColor(PxVobLightPreset const* lightPreset) {
	PxColor color;
	color.r = lightPreset->color.r;
	color.g = lightPreset->color.g;
	color.b = lightPreset->color.b;
	color.a = lightPreset->color.a;
	return color;
}

float pxLightPresetGetConeAngle(PxVobLightPreset const* lightPreset) {
	return lightPreset->cone_angle;
}

PxBool pxLightPresetGetIsStatic(PxVobLightPreset const* lightPreset) {
	return lightPreset->is_static;
}

PxVobLightQuality pxLightPresetGetQuality(PxVobLightPreset const* lightPreset) {
	return static_cast<PxVobLightQuality>(lightPreset->quality);
}

char const* pxLightPresetGetLensFlareFx(PxVobLight const* light) {
	return light->lensflare_fx.c_str();
}

PxBool pxLightPresetGetOn(PxVobLightPreset const* lightPreset) {
	return lightPreset->on;
}

uint32_t pxLightPresetGetRangeAnimationScaleCount(PxVobLightPreset const* lightPreset) {
	return (uint32_t) lightPreset->range_animation_scale.size();
}

float pxLightPresetGetRangeAnimationScale(PxVobLightPreset const* lightPreset, uint32_t i) {
	return lightPreset->range_animation_scale[i];
}

float pxLightPresetGetRangeAnimationFps(PxVobLightPreset const* lightPreset) {
	return lightPreset->range_animation_fps;
}

PxBool pxLightPresetGetRangeAnimationSmooth(PxVobLightPreset const* lightPreset) {
	return lightPreset->range_animation_smooth;
}

uint32_t pxLightPresetGetColorAnimationListCount(PxVobLightPreset const* lightPreset) {
	return (uint32_t) lightPreset->color_animation_list.size();
}

PxColor pxLightPresetGetColorAnimationList(PxVobLightPreset const* lightPreset, uint32_t i) {
	PxColor color;
	color.r = lightPreset->color_animation_list[i].r;
	color.g = lightPreset->color_animation_list[i].g;
	color.b = lightPreset->color_animation_list[i].b;
	color.a = lightPreset->color_animation_list[i].a;
	return color;
}

float pxLightPresetGetColorAnimationFps(PxVobLightPreset const* lightPreset) {
	return lightPreset->color_animation_fps;
}

PxBool pxLightPresetGetColorAnimationSmooth(PxVobLightPreset const* lightPreset) {
	return lightPreset->color_animation_smooth;
}

PxBool pxLightPresetGetCanMove(PxVobLightPreset const* lightPreset) {
	return lightPreset->can_move;
}
// Vob - Light
char const* pxVobLightGetPreset(PxVobLight const* light) {
	return light->preset.c_str();
}

PxVobLightMode pxVobLightGetLightType(PxVobLight const* light) {
	return static_cast<PxVobLightMode>(light->light_type);
}

float pxVobLightGetRange(PxVobLight const* light) {
	return light->range;
}

PxColor pxVobLightGetColor(PxVobLight const* light) {
	PxColor color;
	color.r = light->color.r;
	color.g = light->color.g;
	color.b = light->color.b;
	color.a = light->color.a;
	return color;
}

float pxVobLightGetConeAngle(PxVobLight const* light) {
	return light->cone_angle;
}

PxBool pxVobLightGetIsStatic(PxVobLight const* light) {
	return light->is_static;
}

PxVobLightQuality pxVobLightGetQuality(PxVobLight const* light) {
	return static_cast<PxVobLightQuality>(light->quality);
}

char const* pxVobLightGetLensFlareFx(PxVobLight const* light) {
	return light->lensflare_fx.c_str();
}

PxBool pxVobLightGetOn(PxVobLight const* light) {
	return light->on;
}

uint32_t pxVobLightGetRangeAnimationScaleCount(PxVobLight const* light) {
	return (uint32_t) light->range_animation_scale.size();
}

float pxVobLightGetRangeAnimationScale(PxVobLight const* light, uint32_t i) {
	return light->range_animation_scale[i];
}

float pxVobLightGetRangeAnimationFps(PxVobLight const* light) {
	return light->range_animation_fps;
}

PxBool pxVobLightGetRangeAnimationSmooth(PxVobLight const* light) {
	return light->range_animation_smooth;
}

uint32_t pxVobLightGetColorAnimationListCount(PxVobLight const* light) {
	return (uint32_t) light->color_animation_list.size();
}

PxColor pxVobLightGetColorAnimationList(PxVobLight const* light, uint32_t i) {
	PxColor color;
	color.r = light->color_animation_list[i].r;
	color.g = light->color_animation_list[i].g;
	color.b = light->color_animation_list[i].b;
	color.a = light->color_animation_list[i].a;
	return color;
}

float pxVobLightGetColorAnimationFps(PxVobLight const* light) {
	return light->color_animation_fps;
}

PxBool pxVobLightGetColorAnimationSmooth(PxVobLight const* light) {
	return light->color_animation_smooth;
}

PxBool pxVobLightGetCanMove(PxVobLight const* light) {
	return light->can_move;
}

// Vob - Animate
PxBool pxVobAnimateGetStartOn(PxVobAnimate const* animate) {
	return animate->start_on;
}

// Vob - Item
char const* pxVobItemGetInstance(PxVobItem const* item) {
	return item->instance.c_str();
}

// Vob - Lens Flare
char const* pxVobLensFlareGetFx(PxVobLensFlare const* lensFlare) {
	return lensFlare->fx.c_str();
}

// Vob - Pfx Controller
char const* pxVobPfxControllerGetPfxName(PxVobPfxController const* pfxController) {
	return pfxController->pfx_name.c_str();
}

PxBool pxVobPfxControllerGetKillWhenDone(PxVobPfxController const* pfxController) {
	return pfxController->kill_when_done;
}

PxBool pxVobPfxControllerGetInitiallyRunning(PxVobPfxController const* pfxController) {
	return (uint32_t) pfxController->initially_running;
}

// Vob - Message Filter
char const* pxVobMessageFilterGetTarget(PxVobMessageFilter const* messageFilter) {
	return messageFilter->target.c_str();
}

uint32_t pxVobMessageFilterGetOnTrigger(PxVobMessageFilter const* messageFilter) {
	return (uint32_t) messageFilter->on_trigger;
}

uint32_t pxVobMessageFilterGetOnUntrigger(PxVobMessageFilter const* messageFilter) {
	return (uint32_t) messageFilter->on_untrigger;
}

// Vob - Code Master
char const* pxVobCodeMasterGetTarget(PxVobCodeMaster const* codeMaster) {
	return codeMaster->target.c_str();
}

PxBool pxVobCodeMasterGetOrdered(PxVobCodeMaster const* codeMaster) {
	return codeMaster->ordered;
}

PxBool pxVobCodeMasterGetFirstFalseIsFailure(PxVobCodeMaster const* codeMaster) {
	return codeMaster->first_false_is_failure;
}

char const* pxVobCodeMasterGetFailureTarget(PxVobCodeMaster const* codeMaster) {
	return codeMaster->failure_target.c_str();
}

PxBool pxVobCodeMasterGetUntriggeredCancels(PxVobCodeMaster const* codeMaster) {
	return codeMaster->untriggered_cancels;
}

uint32_t pxVobCodeMasterGetSlavesCount(PxVobCodeMaster const* codeMaster) {
	return (uint32_t) codeMaster->slaves.size();
}

char const* pxVobCodeMasterGetSlaves(PxVobCodeMaster const* codeMaster, uint32_t i) {
	return codeMaster->slaves[i].c_str();
}

// Vob - Mover Controller
char const* pxVobMoverControllerGetTarget(PxVobMoverController const* moverController) {
	return moverController->target.c_str();
}

uint32_t pxVobMoverControllerGetMessage(PxVobMoverController const* moverController) {
	return (uint32_t) moverController->message;
}

int32_t pxVobMoverControllerGetKey(PxVobMoverController const* moverController) {
	return moverController->key;
}

// Vob - Touch Damage
float pxVobTouchDamageGetDamage(PxVobTouchDamage const* touchDamage) {
	return touchDamage->damage;
}

PxBool pxVobTouchDamageGetBarrier(PxVobTouchDamage const* touchDamage) {
	return touchDamage->barrier;
}

PxBool pxVobTouchDamageGetBlunt(PxVobTouchDamage const* touchDamage) {
	return touchDamage->blunt;
}

PxBool pxVobTouchDamageGetEdge(PxVobTouchDamage const* touchDamage) {
	return touchDamage->edge;
}

PxBool pxVobTouchDamageGetFire(PxVobTouchDamage const* touchDamage) {
	return touchDamage->fire;
}

PxBool pxVobTouchDamageGetFly(PxVobTouchDamage const* touchDamage) {
	return touchDamage->fly;
}

PxBool pxVobTouchDamageGetMagic(PxVobTouchDamage const* touchDamage) {
	return touchDamage->magic;
}

PxBool pxVobTouchDamageGetPoint(PxVobTouchDamage const* touchDamage) {
	return touchDamage->point;
}

PxBool pxVobTouchDamageGetFall(PxVobTouchDamage const* touchDamage) {
	return touchDamage->fall;
}

float pxVobTouchDamageGetRepearDelaySec(PxVobTouchDamage const* touchDamage) {
	return touchDamage->repeat_delay_sec;
}

float pxVobTouchDamageGetVolumeScale(PxVobTouchDamage const* touchDamage) {
	return touchDamage->volume_scale;
}

uint32_t pxVobTouchDamageGetCollision(PxVobTouchDamage const* touchDamage) {
	return (uint32_t) touchDamage->collision;
}

// Vob - Earthquake
float pxVobEarthquakeGetRadius(PxVobEarthquake const* earthquake) {
	return earthquake->radius;
}

float pxVobEarthquakeGetDuration(PxVobEarthquake const* earthquake) {
	return earthquake->duration;
}

PxVec3 pxVobEarthquakeGetAmplitude(PxVobEarthquake const* earthquake) {
	PxVec3 amplitude;
	amplitude.x = earthquake->amplitude.x;
	amplitude.y = earthquake->amplitude.y;
	amplitude.z = earthquake->amplitude.z;
	return amplitude;
}

// Vob - Npc
char const* pxVobNpcGetNpcInstance(PxVobNpc const* npc) {
	return npc->npc_instance.c_str();
}

PxVec3 pxVobNpcGetModelScale(PxVobNpc const* npc) {
	PxVec3 scale;
	scale.x = npc->model_scale.x;
	scale.y = npc->model_scale.y;
	scale.z = npc->model_scale.z;
	return scale;
}

float pxVobNpcGetModelFatness(PxVobNpc const* npc) {
	return npc->model_fatness;
}

uint32_t pxVobNpcGetOverlaysCount(PxVobNpc const* npc) {
	return (uint32_t) npc->overlays.size();
}

char const* pxVobNpcGetOverlays(PxVobNpc const* npc, uint32_t i) {
	return npc->overlays[i].c_str();
}

int pxVobNpcGetFlags(PxVobNpc const* npc) {
	return npc->flags;
}

int pxVobNpcGetGuild(PxVobNpc const* npc) {
	return npc->guild;
}

int pxVobNpcGetGuildTrue(PxVobNpc const* npc) {
	return npc->guild_true;
}

int pxVobNpcGetLevel(PxVobNpc const* npc) {
	return npc->level;
}

int pxVobNpcGetXp(PxVobNpc const* npc) {
	return npc->xp;
}

int pxVobNpcGetXpNextLevel(PxVobNpc const* npc) {
	return npc->xp_next_level;
}

int pxVobNpcGetLp(PxVobNpc const* npc) {
	return npc->lp;
}

uint32_t pxVobNpcGetTalentsCount(PxVobNpc const* npc) {
	return (uint32_t) npc->talents.size();
}

void pxVobNpcGetTalents(PxVobNpc const* npc, uint32_t i, int* talent, int* value, int* skill) {
	*talent = npc->talents[i].talent;
	*value = npc->talents[i].value;
	*skill = npc->talents[i].skill;
}

int pxVobNpcGetFightTactic(PxVobNpc const* npc) {
	return npc->fight_tactic;
}

int pxVobNpcGetFightMode(PxVobNpc const* npc) {
	return npc->fight_mode;
}

PxBool pxVobNpcGetWounded(PxVobNpc const* npc) {
	return npc->wounded;
}

PxBool pxVobNpcGetMad(PxVobNpc const* npc) {
	return npc->mad;
}

int pxVobNpcGetMadTime(PxVobNpc const* npc) {
	return npc->mad_time;
}

PxBool pxVobNpcGetPlayer(PxVobNpc const* npc) {
	return npc->player;
}

uint32_t pxVobNpcGetAttributesCount(PxVobNpc const* npc) {
	return 8;
}
int pxVobNpcGetAttributes(PxVobNpc const* npc, uint32_t i) {
	return npc->attributes[i];
}

uint32_t pxVobNpcGetHcsCount(PxVobNpc const* npc) {
	return 4;
}
int pxVobNpcGetHcs(PxVobNpc const* npc, uint32_t i) {
	return npc->hcs[i];
}

uint32_t pxVobNpcGetMissionsCount(PxVobNpc const* npc) {
	return 5;
}

int pxVobNpcGetMissions(PxVobNpc const* npc, uint32_t i) {
	return npc->missions[i];
}

char const* pxVobNpcGetStartAiState(PxVobNpc const* npc) {
	return npc->start_ai_state.c_str();
}

uint32_t pxVobNpcGetAivarCount(PxVobNpc const* npc) {
	return 100;
}
int pxVobNpcGetAivar(PxVobNpc const* npc, uint32_t i) {
	return npc->aivar[i];
}

char const* pxVobNpcGetScriptWaypoint(PxVobNpc const* npc) {
	return npc->script_waypoint.c_str();
}

int pxVobNpcGetAttitude(PxVobNpc const* npc) {
	return npc->attitude;
}

int pxVobNpcGetAttitudeTemp(PxVobNpc const* npc) {
	return npc->attitude_temp;
}

int pxVobNpcGetNameNr(PxVobNpc const* npc) {
	return npc->name_nr;
}

PxBool pxVobNpcGetMoveLock(PxVobNpc const* npc) {
	return npc->move_lock;
}

uint32_t pxVobNpcGetPackedCount(PxVobNpc const* npc) {
	return 9;
}
char const* pxVobNpcGetPacked(PxVobNpc const* npc, uint32_t i) {
	return npc->packed[i].c_str();
}

uint32_t pxVobNpcGetItemsCount(PxVobNpc const* npc) {
	return (uint32_t) npc->items.size();
}

PxVobItem const* pxVobNpcGetItems(PxVobNpc const* npc, uint32_t i) {
	return npc->items[i].get();
}

uint32_t pxVobNpcGetSlotsCount(PxVobNpc const* npc) {
	return (uint32_t) npc->slots.size();
}

void pxVobNpcGetSlots(PxVobNpc const* npc,
                              uint32_t i,
                              PxBool* used,
                              char const** name,
                              int* itemIndex,
                              PxBool* inInventory) {
	*used = npc->slots[i].used;
	*name = npc->slots[i].name.c_str();
	*itemIndex = npc->slots[i].item_index;
	*inInventory = npc->slots[i].in_inventory;
}

PxBool pxVobNpcGetCurrentStateValid(PxVobNpc const* npc) {
	return npc->current_state_valid;
}

char const* pxVobNpcGetCurrentStateName(PxVobNpc const* npc) {
	return npc->current_state_name.c_str();
}

int pxVobNpcGetCurrentStateIndex(PxVobNpc const* npc) {
	return npc->current_state_index;
}

PxBool pxVobNpcGetCurrentStateIsRoutine(PxVobNpc const* npc) {
	return npc->current_state_is_routine;
}

PxBool pxVobNpcGetNextStateValid(PxVobNpc const* npc) {
	return npc->next_state_valid;
}

char const* pxVobNpcGetNextStateName(PxVobNpc const* npc) {
	return npc->next_state_name.c_str();
}

int pxVobNpcGetNextStateIndex(PxVobNpc const* npc) {
	return npc->next_state_index;
}

PxBool pxVobNpcGetNextStateIsRoutine(PxVobNpc const* npc) {
	return npc->next_state_is_routine;
}

int pxVobNpcGetLastAiState(PxVobNpc const* npc) {
	return npc->last_ai_state;
}

PxBool pxVobNpcGetHasRoutine(PxVobNpc const* npc) {
	return npc->has_routine;
}

PxBool pxVobNpcGetRoutineChanged(PxVobNpc const* npc) {
	return npc->routine_changed;
}

PxBool pxVobNpcGetRoutineOverlay(PxVobNpc const* npc) {
	return npc->routine_overlay;
}

int pxVobNpcGetRoutineOverlayCount(PxVobNpc const* npc) {
	return npc->routine_overlay_count;
}

int pxVobNpcGetWalkmodeRoutine(PxVobNpc const* npc) {
	return npc->walkmode_routine;
}

PxBool pxVobNpcGetWeaponmodeRoutine(PxVobNpc const* npc) {
	return npc->weaponmode_routine;
}

PxBool pxVobNpcGetStartNewRoutine(PxVobNpc const* npc) {
	return npc->start_new_routine;
}

int pxVobNpcGetAiStateDriven(PxVobNpc const* npc) {
	return npc->ai_state_driven;
}

PxVec3 pxVobNpcGetAiStatePos(PxVobNpc const* npc) {
	PxVec3 ai_state_pos;
	ai_state_pos.x = npc->ai_state_pos.x;
	ai_state_pos.y = npc->ai_state_pos.y;
	ai_state_pos.z = npc->ai_state_pos.z;
	return ai_state_pos;
}

char const* pxVobNpcGetCurrentRoutine(PxVobNpc const* npc) {
	return npc->current_routine.c_str();
}

PxBool pxVobNpcGetRespawn(PxVobNpc const* npc) {
	return npc->respawn;
}

int pxVobNpcGetRespawnTime(PxVobNpc const* npc) {
	return npc->respawn_time;
}

uint32_t pxVobNpcGetProtectionCount(PxVobNpc const* npc) {
	return 8;
}
int pxVobNpcGetProtection(PxVobNpc const* npc, uint32_t i) {
	return npc->protection[i];
}

int pxVobNpcGetBsInterruptableOverride(PxVobNpc const* npc) {
	return npc->bs_interruptable_override;
}

int pxVobNpcGetNpcType(PxVobNpc const* npc) {
	return npc->npc_type;
}

int pxVobNpcGetSpellMana(PxVobNpc const* npc) {
	return npc->spell_mana;
}

// Vob - Mob
char const* pxVobMobGetName(PxVobMob const* mob) {
	return mob->name.c_str();
}

int32_t pxVobMobGetHp(PxVobMob const* mob) {
	return mob->hp;
}

int32_t pxVobMobGetDamage(PxVobMob const* mob) {
	return mob->damage;
}

PxBool pxVobMobGetMovable(PxVobMob const* mob) {
	return mob->movable;
}

PxBool pxVobMobGetTakable(PxVobMob const* mob) {
	return mob->takable;
}

PxBool pxVobMobGetFocusOverride(PxVobMob const* mob) {
	return mob->focus_override;
}

PxVobMobSoundMaterial pxVobMobGetMaterial(PxVobMob const* mob) {
	return static_cast<PxVobMobSoundMaterial>(mob->material);
}

char const* pxVobMobGetVisualDestroyed(PxVobMob const* mob) {
	return mob->visual_destroyed.c_str();
}

char const* pxVobMobGetOwner(PxVobMob const* mob) {
	return mob->owner.c_str();
}

char const* pxVobMobGetOwnerGuild(PxVobMob const* mob) {
	return mob->owner_guild.c_str();
}

PxBool pxVobMobGetDestroyed(PxVobMob const* mob) {
	return mob->destroyed;
}

// Vob - MobInter
int32_t pxVobMobInterGetState(PxVobMobInter const* mobInter) {
	return mobInter->state;
}

char const* pxVobMobInterGetTarget(PxVobMobInter const* mobInter) {
	return mobInter->target.c_str();
}

char const* pxVobMobInterGetItem(PxVobMobInter const* mobInter) {
	return mobInter->item.c_str();
}

char const* pxVobMobInterGetConditionFunction(PxVobMobInter const* mobInter) {
	return mobInter->condition_function.c_str();
}

char const* pxVobMobInterGetOnStateChangeFunction(PxVobMobInter const* mobInter) {
	return mobInter->on_state_change_function.c_str();
}

PxBool pxVobMobInterGetRewind(PxVobMobInter const* mobInter) {
	return mobInter->rewind;
}

// Vob - MobFire
char const* pxVobMobFireGetSlot(PxVobMobFire const* mobFire) {
	return mobFire->slot.c_str();
}

char const* pxVobMobFireGetVobTree(PxVobMobFire const* mobFire) {
	return mobFire->vob_tree.c_str();
}

// Vob - MobContainer
PxBool pxVobMobContainerGetLocked(PxVobMobContainer const* mobContainer) {
	return mobContainer->locked;
}

char const* pxVobMobContainerGetKey(PxVobMobContainer const* mobContainer) {
	return mobContainer->key.c_str();
}

char const* pxVobMobContainerGetPickString(PxVobMobContainer const* mobContainer) {
	return mobContainer->pick_string.c_str();
}

char const* pxVobMobContainerGetContents(PxVobMobContainer const* mobContainer) {
	return mobContainer->contents.c_str();
}

// Vob - MobDoor
PxBool pxVobMobDoorGetLocked(PxVobMobDoor const* mobDoor) {
	return mobDoor->locked;
}

char const* pxVobMobDoorGetKey(PxVobMobDoor const* mobDoor) {
	return mobDoor->key.c_str();
}

char const* pxVobMobDoorGetPickString(PxVobMobDoor const* mobDoor) {
	return mobDoor->pick_string.c_str();
}

// Vob - Sound
float pxVobSoundGetVolume(PxVobSound const* sound) {
	return sound->volume;
}

PxVobSoundMode pxVobSoundGetSoundMode(PxVobSound const* sound) {
	return static_cast<PxVobSoundMode>(sound->mode);
}

float pxVobSoundGetRandomDelay(PxVobSound const* sound) {
	return sound->random_delay;
}

float pxVobSoundGetRandomDelayVar(PxVobSound const* sound) {
	return sound->random_delay_var;
}

PxBool pxVobSoundGetInitiallyPlaying(PxVobSound const* sound) {
	return sound->initially_playing;
}

PxBool pxVobSoundGetAmbient3d(PxVobSound const* sound) {
	return sound->ambient3d;
}

PxBool pxVobSoundGetObstruction(PxVobSound const* sound) {
	return sound->obstruction;
}

float pxVobSoundGetConeAngle(PxVobSound const* sound) {
	return sound->cone_angle;
}

PxVobSoundTriggerVolume pxVobSoundGetSoundTriggerVolume(PxVobSound const* sound) {
	return static_cast<PxVobSoundTriggerVolume>(sound->mode);
}

float pxVobSoundGetRadius(PxVobSound const* sound) {
	return sound->radius;
}

char const* pxVobSoundGetSoundName(PxVobSound const* sound) {
	return sound->sound_name.c_str();
}

// Vob - SoundDaytime
float pxVobSoundDaytimeStartTime(PxVobSoundDaytime const* soundDaytime) {
	return soundDaytime->start_time;
}

float pxVobSoundDaytimeEndTime(PxVobSoundDaytime const* soundDaytime) {
	return soundDaytime->end_time;
}

char const* pxVobSoundDaytimeSoundName2(PxVobSoundDaytime const* soundDaytime) {
	return soundDaytime->sound_name2.c_str();
}

// Trigger
char const* pxVobTriggerGetTarget(PxVobTrigger const* trigger) {
	return trigger->target.c_str();
}

std::uint8_t pxVobTriggerGetFlags(PxVobTrigger const* trigger) {
	return static_cast<std::uint8_t>(trigger->flags);
}

std::uint8_t pxVobTriggerGetFilterFlags(PxVobTrigger const* trigger) {
	return static_cast<std::uint8_t>(trigger->filter_flags);
}

char const* pxVobTriggerGetVobTarget(PxVobTrigger const* trigger) {
	return trigger->vob_target.c_str();
}

int32_t pxVobTriggerGetMaxActivationCount(PxVobTrigger const* trigger) {
	return trigger->max_activation_count;
}

float pxVobTriggerGetRetriggerDelaySec(PxVobTrigger const* trigger) {
	return trigger->retrigger_delay_sec;
}

float pxVobTriggerGetDamageThreshold(PxVobTrigger const* trigger) {
	return trigger->damage_threshold;
}

float pxVobTriggerGetFireDelaySec(PxVobTrigger const* trigger) {
	return trigger->fire_delay_sec;
}

// Trigger save-game only variables
float pxVobTriggerGetSNextTimeTriggerable(PxVobTrigger const* trigger) {
	return trigger->s_next_time_triggerable;
}

int pxVobTriggerGetSCountCanBeActivated(PxVobTrigger const* trigger) {
	return trigger->s_count_can_be_activated;
}

PxBool pxVobTriggerGetSIsEnabled(PxVobTrigger const* trigger) {
	return trigger->s_is_enabled;
}

// Trigger - Mover
PxVobTriggerMoverBehaviour pxVobTriggerMoverGetBehaviour(PxVobTriggerMover const* trigger) {
	return static_cast<PxVobTriggerMoverBehaviour>(trigger->behavior);
}

float pxVobTriggerMoverGetTouchBlockerDamage(PxVobTriggerMover const* trigger) {
	return trigger->touch_blocker_damage;
}

float pxVobTriggerMoverGetStayOpenTimeSec(PxVobTriggerMover const* trigger) {
	return trigger->stay_open_time_sec;
}

PxBool pxVobTriggerMoverGetLocked(PxVobTriggerMover const* trigger) {
	return trigger->locked;
}

PxBool pxVobTriggerMoverGetAutoLink(PxVobTriggerMover const* trigger) {
	return trigger->auto_link;
}

PxBool pxVobTriggerMoverGetAutoRotate(PxVobTriggerMover const* trigger) {
	return trigger->auto_rotate;
}

float pxVobTriggerMoverGetSpeed(PxVobTriggerMover const* trigger) {
	return trigger->speed;
}

PxVobTriggerMoverLerpMode pxVobTriggerMoverGetLerpMode(PxVobTriggerMover const* trigger) {
	return static_cast<PxVobTriggerMoverLerpMode>(trigger->lerp_mode);
}

PxVobTriggerMoverSpeedMode pxVobTriggerMoverGetSpeedMode(PxVobTriggerMover const* trigger) {
	return static_cast<PxVobTriggerMoverSpeedMode>(trigger->speed_mode);
}

uint32_t pxVobTriggerMoverGetKeyframeCount(PxVobTriggerMover const* trigger) {
	return (uint32_t) trigger->keyframes.size();
}

void pxVobTriggerMoverGetKeyframe(PxVobTriggerMover const* trigger, uint32_t i, PxVec3* position, PxQuat* rotation) {
	auto const& src = trigger->keyframes[i];
	position->x = src.position.x;
	position->y = src.position.y;
	position->z = src.position.z;
	rotation->x = src.rotation.x;
	rotation->y = src.rotation.y;
	rotation->z = src.rotation.z;
	rotation->w = src.rotation.w;
}

char const* pxVobTriggerMoverGetSfxOpenStart(PxVobTriggerMover const* trigger) {
	return trigger->sfx_open_start.c_str();
}

char const* pxVobTriggerMoverGetSfxOpenEnd(PxVobTriggerMover const* trigger) {
	return trigger->sfx_open_end.c_str();
}

char const* pxVobTriggerMoverGetSfxTransitioning(PxVobTriggerMover const* trigger) {
	return trigger->sfx_transitioning.c_str();
}

char const* pxVobTriggerMoverGetSfxCloseStart(PxVobTriggerMover const* trigger) {
	return trigger->sfx_close_start.c_str();
}

char const* pxVobTriggerMoverGetSfxCloseEnd(PxVobTriggerMover const* trigger) {
	return trigger->sfx_close_end.c_str();
}

char const* pxVobTriggerMoverGetSfxLock(PxVobTriggerMover const* trigger) {
	return trigger->sfx_lock.c_str();
}

char const* pxVobTriggerMoverGetSfxUnlock(PxVobTriggerMover const* trigger) {
	return trigger->sfx_unlock.c_str();
}

char const* pxVobTriggerMoverGetSfxUseLocked(PxVobTriggerMover const* trigger) {
	return trigger->sfx_use_locked.c_str();
}

// Trigger - Mover save-game only variables
PxVec3 pxVobTriggerMoverGetSActKeyPosDelta(PxVobTriggerMover const* trigger) {
	PxVec3 vector;
	vector.x = trigger->s_act_key_pos_delta.x;
	vector.y = trigger->s_act_key_pos_delta.y;
	vector.z = trigger->s_act_key_pos_delta.z;
	return vector;
}

float pxVobTriggerMoverGetSActKeyframeF(PxVobTriggerMover const* trigger) {
	return trigger->s_act_keyframe_f;
}

int pxVobTriggerMoverGetSActKeyframe(PxVobTriggerMover const* trigger) {
	return trigger->s_act_keyframe;
}

int pxVobTriggerMoverGetSNextKeyFrame(PxVobTriggerMover const* trigger) {
	return trigger->s_next_keyframe;
}

float pxVobTriggerMoverGetMoveSpeedUnit(PxVobTriggerMover const* trigger) {
	return trigger->s_move_speed_unit;
}

float pxVobTriggerMoverGetSAdvanceDir(PxVobTriggerMover const* trigger) {
	return trigger->s_advance_dir;
}

uint32_t pxVobTriggerMoverGetSMoverState(PxVobTriggerMover const* trigger) {
	return trigger->s_mover_state;
}

int pxVobTriggerMoverGetSTriggerEventCount(PxVobTriggerMover const* trigger) {
	return trigger->s_trigger_event_count;
}

float pxVobTriggerMoverGetSStayOpenTimeDest(PxVobTriggerMover const* trigger) {
	return trigger->s_stay_open_time_dest;
}

// Trigger - List
PxVobTriggerBatchMode pxVobTriggerListGetTriggerBatchMode(PxVobTriggerList const* trigger) {
	return static_cast<PxVobTriggerBatchMode>(trigger->mode);
}

uint32_t pxVobTriggerListGetTargetsCount(PxVobTriggerList const* trigger) {
	return (uint32_t) trigger->targets.size();
}
char const* pxVobTriggerListGetTargetName(PxVobTriggerList const* trigger, uint32_t i) {
	auto const& src = trigger->targets[i];
	return src.name.c_str();
}
float pxVobTriggerListGetTargetDelay(PxVobTriggerList const* trigger, uint32_t i) {
	auto const& src = trigger->targets[i];
	return src.delay;
}

// Trigger - List save-game only variables
uint8_t pxVobTriggerListGetSActTarget(PxVobTriggerList const* trigger) {
	return trigger->s_act_target;
}

PxBool pxVobTriggerListGetSSendOnTrigger(PxVobTriggerList const* trigger) {
	return trigger->s_send_on_trigger;
}

// Trigger - Script
char const* pxVobTriggerScriptGetFunction(PxVobTriggerScript const* trigger) {
	return trigger->function.c_str();
}

// Trigger - Change Level
char const* pxVobTriggerChangeLevelGetLevelName(PxVobTriggerChangeLevel const* trigger) {
	return trigger->level_name.c_str();
}

char const* pxVobTriggerChangeLevelGetStartVob(PxVobTriggerChangeLevel const* trigger) {
	return trigger->start_vob.c_str();
}

// Trigger - World Start
char const* pxVobTriggerWorldStartGetTarget(PxVobTriggerWorldStart const* trigger) {
	return trigger->target.c_str();
}

PxBool pxVobTriggerWorldStartGetFireOnce(PxVobTriggerWorldStart const* trigger) {
	return trigger->fire_once;
}

// Trigger - World Start save-game only variables
PxBool pxVobTriggerWorldStartGetSHasFired(PxVobTriggerWorldStart const* trigger) {
	return trigger->s_has_fired;
}

// Trigger - Untouch
char const* pxVobTriggerUntouchGetTarget(PxVobTriggerUntouch const* trigger) {
	return trigger->target.c_str();
}

// Vob - ZoneMusic
void pxWorldVobGetZoneMusic(PxVobZoneMusic const* zoneMusic,
                            PxBool* enabled,
                            int32_t* priority,
                            PxBool* ellipsoid,
                            float* reverb,
                            float* volume,
                            PxBool* loop) {
	*enabled = zoneMusic->enabled;
	*priority = zoneMusic->priority;
	*ellipsoid = zoneMusic->ellipsoid;
	*reverb = zoneMusic->reverb;
	*volume = zoneMusic->volume;
	*loop = zoneMusic->loop;
}

// Vob - ZoneFarPlane
void pxWorldVobGetZoneFarPlane(PxVobZoneFarPlane* zoneFarPlane, float* vob_far_plane_z, float* inner_range_percentage) {
	*vob_far_plane_z = zoneFarPlane->vob_far_plane_z;
	*inner_range_percentage = zoneFarPlane->inner_range_percentage;
}

// Vob - ZoneFog
void pxWorldVobGetZoneFog(PxVobZoneFog* zoneFog,
                          float* range_center,
                          float* inner_range_percentage,
                          PxColor* color,
                          PxBool* fade_out_sky,
                          PxBool* override_color) {
	*range_center = zoneFog->range_center;
	*inner_range_percentage = zoneFog->inner_range_percentage;
	color->r = zoneFog->color.r;
	color->g = zoneFog->color.g;
	color->b = zoneFog->color.b;
	color->a = zoneFog->color.a;
	*fade_out_sky = zoneFog->fade_out_sky;
	*override_color = zoneFog->override_color;
}
