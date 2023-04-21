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
