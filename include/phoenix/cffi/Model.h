// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"
#include "ModelHierarchy.h"
#include "ModelMesh.h"
#include "Vdf.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/model.hh>
typedef phoenix::model PxModel;
#else
typedef struct PxInternal_Model PxModel;
#endif

PXC_API PxModel* pxMdlLoad(PxBuffer* buffer);
PXC_API PxModel* pxMdlLoadFromVdf(PxVdf const* vdf, char const* name);
PXC_API void pxMdlDestroy(PxModel* mdl);

PXC_API PxModelHierarchy const* pxMdlGetHierarchy(PxModel const* mdl);
PXC_API PxModelMesh const* pxMdlGetMesh(PxModel const* mdl);
