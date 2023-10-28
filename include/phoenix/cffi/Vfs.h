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

typedef enum {
	PxVfsOverwrite_None = 0,  ///< Overwrite no conflicting nodes.
	PxVfsOverwrite_All = 1,   ///< Overwrite all conflicting nodes.
	PxVfsOverwrite_Newer = 2, ///< Overwrite newer conflicting nodes. (i.e. use older versions)
	PxVfsOverwrite_Older = 3  ///< Overwrite older conflicting nodes. (i.e. use newer versions)
} PxVfsOverwriteBehavior;

PXC_API PxVfs* pxVfsNew();
PXC_API void pxVfsMountDisk(PxVfs* vfs, char const* path, PxVfsOverwriteBehavior overwriteFlag);
PXC_API void pxVfsMountDiskData(PxVfs* vfs, PxBuffer* path, PxVfsOverwriteBehavior overwriteFlag);
PXC_API void pxVfsDestroy(PxVfs* vfs);

PXC_API PxVfsNode const* pxVfsGetRootNode(PxVfs const* node);
PXC_API char const* pxVfsNodeGetName(PxVfsNode const* node);
PXC_API size_t pxVfsNodeGetChildCount(PxVfsNode const* node);
PXC_API PxVfsNode const* pxVfsNodeGetChild(PxVfsNode const* node, size_t i);
PXC_API PxBool pxVfsNodeIsFile(PxVfsNode const* node);

PXC_API PxVfsNode const* pxVfsGetNodeByName(PxVfs const* vfs, char const* name);
PXC_API PxBuffer* pxVfsNodeOpenBuffer(PxVfsNode const* node);
