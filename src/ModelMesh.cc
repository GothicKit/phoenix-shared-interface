// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/ModelMesh.h>
#include <phoenix/model_mesh.hh>

PxModelMesh* pxMdmLoad(PxBuffer* buffer) {
	try {
		auto mat = phoenix::model_mesh::parse(buffer->duplicate());
		return new phoenix::model_mesh(std::move(mat));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxModelMesh",
		                 "encountered exception while parsing PxModelMesh: %s",
		                 e.what());
		return nullptr;
	}
}

PxModelMesh* pxMdmLoadFromVfs(PxVfs const* vfs, char const* name) {
	PxVfsNode const* node = pxVfsGetNodeByName(vfs, name);
	if (node == nullptr) {
		px::logging::log(px::logging::level::error, "CAPI:PxModelMesh", "failed to find vfs entry: %s", name);
		return nullptr;
	}

	PxBuffer* buf = pxVfsNodeOpenBuffer(node);
	PxModelMesh* result = pxMdmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdmDestroy(PxModelMesh* mdm) {
	delete mdm;
}

uint32_t pxMdmGetMeshCount(PxModelMesh const* mdm) {
	return (uint32_t) mdm->meshes.size();
}

PxSoftSkinMesh const* pxMdmGetMesh(PxModelMesh const* mdm, uint32_t i) {
	return &mdm->meshes[i];
}

uint32_t pxMdmGetAttachmentCount(PxModelMesh const* mdm) {
	return (uint32_t) mdm->attachments.size();
}

char const* pxMdmGetAttachmentKey(PxModelMesh const* mdm, uint32_t index) {
	auto& attachments = mdm->attachments;
	uint32_t currentIndex = 0;

	for (const auto& attachment : attachments) {
		if (currentIndex++ == index) return attachment.first.c_str();
	}

	return nullptr;
}

PxMultiResolutionMesh const* pxMdmGetAttachmentValue(PxModelMesh const* mdm, char const* name) {
	auto& attachments = mdm->attachments;
	auto rv = attachments.find(name);

	if (rv == attachments.end()) return nullptr;

	return &rv->second;
}

uint32_t pxMdmGetChecksum(PxModelMesh const* mdm) {
	return mdm->checksum;
}

PxMultiResolutionMesh const* pxSsmGetMesh(PxSoftSkinMesh const* ssm) {
	return &ssm->mesh;
}

uint32_t pxSsmGetWedgeNormalsCount(PxSoftSkinMesh const* ssm) {
	return (uint32_t) ssm->wedge_normals.size();
}

void pxSsmGetWedgeNormal(PxSoftSkinMesh const* ssm, uint32_t i, PxVec3* normal, uint32_t* index) {
	auto& wg = ssm->wedge_normals[i];
	normal->x = wg.normal.x;
	normal->y = wg.normal.y;
	normal->z = wg.normal.z;
	*index = wg.index;
}

uint32_t pxSsmGetNodeCount(PxSoftSkinMesh const* ssm) {
	return (uint32_t) ssm->weights.size();
}

uint32_t pxSsmGetNodeWeightCount(PxSoftSkinMesh const* ssm, uint32_t node) {
	return (uint32_t) ssm->weights[node].size();
}

void pxSsmGetNodeWeight(PxSoftSkinMesh const* ssm,
                        uint32_t node,
                        uint32_t i,
                        float* weight,
                        PxVec3* position,
                        uint8_t* index) {
	auto& w = ssm->weights[node][i];
	*weight = w.weight;
	*index = w.node_index;
	position->x = w.position.x;
	position->y = w.position.y;
	position->z = w.position.z;
}

int32_t const* pxSsmGetNodes(PxSoftSkinMesh const* ssm, uint32_t* length) {
	*length = (uint32_t) ssm->nodes.size();
	return ssm->nodes.data();
}
