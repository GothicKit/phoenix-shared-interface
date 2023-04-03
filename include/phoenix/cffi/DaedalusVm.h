// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_DaedalusVm PxDaedalusVm;

// TODO
PXC_API PxDaedalusVm* px_vm_parse(PxBuffer* buffer);
PXC_API void px_vm_destroy(PxDaedalusVm* vm);
