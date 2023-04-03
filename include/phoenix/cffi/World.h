// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "Vdf.h"
#include "Mesh.h"

#include <stdint.h>

typedef struct PxInternal_World PxWorld;

// TODO
PXC_API PxWorld* pxWorldLoad(PxBuffer* buffer);
PXC_API PxWorld* pxWorldLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxWorldDestroy(PxWorld* world);

PXC_API PxMesh const* pxWorldGetMesh(PxWorld const* world);
PXC_API uint32_t pxWorldGetWayPointCount(PxWorld const* world);
PXC_API void pxWorldGetWayPoint(PxWorld const* world, uint32_t i, char const** name, PxVec3* position, PxVec3* direction, PxBool* freePoint, PxBool* underwater, int32_t* waterDepth);
PXC_API uint32_t pxWorldGetWayEdgeCount(PxWorld const* world);
PXC_API void pxWorldGetWayEdge(PxWorld const* world, uint32_t i, uint32_t* a, uint32_t* b);
