// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/ModelMesh.h>
#include <phoenix/model_mesh.hh>

PxModelMesh* pxMdmLoad(PxBuffer* buffer) {
	try {
		auto* buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto mat = phoenix::model_mesh::parse(buf->duplicate());
		return reinterpret_cast<PxModelMesh*>(new phoenix::model_mesh(std::move(mat)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxModelMesh* pxMdmLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxModelMesh* result = pxMdmLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxMdmDestroy(PxModelMesh* mdm) {
	delete reinterpret_cast<phoenix::model_mesh*>(mdm);
}

uint32_t pxMdmGetMeshCount(PxModelMesh const* mdm) {
	return (uint32_t) RCC(px::model_mesh, mdm)->meshes.size();
}

PxSoftSkinMesh const* pxMdmGetMesh(PxModelMesh const* mdm, uint32_t i) {
	return RCC(PxSoftSkinMesh, &RCC(px::model_mesh, mdm)->meshes[i]);
}

PxMultiResolutionMesh const* pxMdmGetAttachment(PxModelMesh const* mdm, char const* name) {
	auto& attachments = RCC(px::model_mesh, mdm)->attachments;

	auto rv = attachments.find(name);
	if (rv == attachments.end()) return nullptr;

	return RCC(PxMultiResolutionMesh, &rv->second);
}

uint32_t pxMdmGetChecksum(PxModelMesh const* mdm) {
	return RCC(px::model_mesh, mdm)->checksum;
}

PxMultiResolutionMesh const* pxSsmGetMesh(PxSoftSkinMesh const* ssm) {
	return RCC(PxMultiResolutionMesh, &RCC(px::softskin_mesh, ssm)->mesh);
}

uint32_t pxSsmGetWedgeNormalsCount(PxSoftSkinMesh const* ssm) {
	return (uint32_t) RCC(px::softskin_mesh, ssm)->wedge_normals.size();
}

void pxSsmGetWedgeNormal(PxSoftSkinMesh const* ssm, uint32_t i, PxVec3* normal, uint32_t* index) {
	auto& wg = RCC(px::softskin_mesh, ssm)->wedge_normals[i];
	normal->x = wg.normal.x;
	normal->y = wg.normal.y;
	normal->z = wg.normal.z;
	*index = wg.index;
}

uint32_t pxSsmGetNodeCount(PxSoftSkinMesh const* ssm) {
	return (uint32_t) RCC(px::softskin_mesh, ssm)->weights.size();
}

uint32_t pxSsmGetNodeWeightCount(PxSoftSkinMesh const* ssm, uint32_t node) {
	return (uint32_t) RCC(px::softskin_mesh, ssm)->weights[node].size();
}

void pxSsmGetNodeWeight(PxSoftSkinMesh const* ssm,
                        uint32_t node,
                        uint32_t i,
                        float* weight,
                        PxVec3* position,
                        uint8_t* index) {
	auto& w = RCC(px::softskin_mesh, ssm)->weights[node][i];
	*weight = w.weight;
	*index = w.node_index;
	position->x = w.position.x;
	position->y = w.position.y;
	position->z = w.position.z;
}

int32_t const* pxSsmGetNodes(PxSoftSkinMesh const* ssm, uint32_t* length) {
	*length = (uint32_t) RCC(px::softskin_mesh, ssm)->nodes.size();
	return RCC(px::softskin_mesh, ssm)->nodes.data();
}
