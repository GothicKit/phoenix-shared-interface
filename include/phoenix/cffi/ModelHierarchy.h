// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_ModelHierarchy PxModelHierarchy;
typedef struct PxInternal_ModelHierarchyNode PxModelHierarchyNode;

PXC_API PxModelHierarchy* px_mdh_parse(PxBuffer* buffer);
PXC_API PxAABB px_mdh_bbox(PxModelHierarchy const* mdh);
PXC_API PxAABB px_mdh_collision_bbox(PxModelHierarchy const* mdh);
PXC_API PxVec3 px_mdh_root_translation(PxModelHierarchy const* mdh);
PXC_API uint32_t px_mdh_checksum(PxModelHierarchy const* mdh);
PXC_API uint32_t px_mdh_node_count(PxModelHierarchy const* mdh);
PXC_API void px_mdh_node(PxModelHierarchy const* mdh, uint32_t i, int16_t* parent, char const** name /*, TODO: Node transform*/);
PXC_API int16_t px_mdh_node_parent(PxModelHierarchyNode const* node);
PXC_API char const* px_mdh_node_name(PxModelHierarchyNode const* node);
PXC_API void px_mdh_destroy(PxModelHierarchy* mdh);
