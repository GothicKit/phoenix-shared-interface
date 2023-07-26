// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

#ifdef __cplusplus
	#include <phoenix/Vfs.hh>
typedef phoenix::Vfs PxVfs;
typedef phoenix::VfsNode PxVfsNode;
#else
typedef struct PxInternal_Vfs PxVfs;
typedef struct PxInternal_VfsNode PxVfsNode;
#endif

PXC_API PxVfs* pxVfsNew();
PXC_API void pxVfsMountFile(PxVfs* vfs, char const* path);
PXC_API void pxVfsDestroy(PxVfs* vfs);

PXC_API PxVfsNode const* pxVfsGetEntryByName(PxVfs const* vfs, char const* name);
PXC_API PxBuffer* pxVfsNodeOpenBuffer(PxVfsNode const* node);
