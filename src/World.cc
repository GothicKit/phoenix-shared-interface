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

PxWorld* pxWorldLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
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

glm::vec2 pxVobGetDecalDimension(PxVob const* vob) {
	return vob->visual_decal->dimension;
}

glm::vec2 pxVobGetDecalOffset(PxVob const* vob) {
	return vob->visual_decal->offset;
}

bool pxVobGetDecalTwoSided(PxVob const* vob) {
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

bool pxVobGetDecalIgnoreDaylight(PxVob const* vob) {
	return vob->visual_decal->ignore_daylight;
}

// Vob - Item
char const* pxVobItemGetInstance(PxVobItem const* item) {
	return item->instance.c_str();
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
// Vob - ZoneMusic
void pxWorldVobGetZoneMusic(PxVobZoneMusic const* zoneMusic,
                            bool* enabled,
                            int32_t* priority,
                            bool* ellipsoid,
                            float* reverb,
                            float* volume,
                            bool* loop) {
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
                          glm::u8vec4* color,
                          bool* fade_out_sky,
                          bool* override_color) {
	*range_center = zoneFog->range_center;
	*inner_range_percentage = zoneFog->inner_range_percentage;
	*color = zoneFog->color;
	*fade_out_sky = zoneFog->fade_out_sky;
	*override_color = zoneFog->override_color;
}
