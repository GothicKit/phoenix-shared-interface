// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"

#ifdef __cplusplus
	#include <phoenix/world/bsp_tree.hh>
typedef phoenix::bsp_tree PxBspTree;
#else
typedef PxInternal_BspTree PxBspTree;
#endif

typedef enum {
	PxBspIndoor = 0,
	PxBspOutdoor = 1,
} PxBspTreeMode;

PXC_API PxBspTreeMode pxBspGetMode(PxBspTree const* slf);
PXC_API size_t pxBspGetPolygonIndicesLength(PxBspTree const* slf);
PXC_API uint32_t const* pxBspGetPolygonIndices(PxBspTree const* slf, size_t* size);
PXC_API size_t pxBspGetLeafPolygonIndicesLength(PxBspTree const* slf);
PXC_API uint32_t const* pxBspGetLeafPolygonIndices(PxBspTree const* slf, size_t* size);
PXC_API size_t pxBspGetPortalPolygonIndicesLength(PxBspTree const* slf);
PXC_API uint32_t const* pxBspGetPortalPolygonIndices(PxBspTree const* slf, size_t* size);
PXC_API size_t pxBspGetLightPointsLength(PxBspTree const* slf);
PXC_API PxVec3 pxBspGetLightPoint(PxBspTree const* slf, size_t idx);
PXC_API size_t pxBspGetLeafNodeIndicesLength(PxBspTree const* slf);
PXC_API uint64_t const* pxBspGetLeafNodeIndices(PxBspTree const* slf, size_t* size);

PXC_API size_t pxBspGetSectorsLength(PxBspTree const* slf);
PXC_API void pxBspGetSector(PxBspTree const* slf,
                            size_t idx,
                            char const** name,
                            uint32_t const** nodeIndices,
                            size_t* nodeIndicesLength,
                            uint32_t const** portalPolygonIndices,
                            size_t* portalPolygonIndicesLength);

PXC_API size_t pxBspGetNodesLength(PxBspTree const* slf);
PXC_API void pxBspGetNode(PxBspTree const* slf,
                          size_t idx,
                          PxVec4* plane,
                          PxAABB* bbox,
                          uint32_t* polygonIndex,
                          uint32_t* polygonCount,
                          int32_t* frontNodeIndex,
                          int32_t* backNodeIndex,
                          int32_t* parentNodeIndex);
