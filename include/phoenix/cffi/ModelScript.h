// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"
#include "Buffer.h"

#include <stdint.h>

typedef struct PxInternal_ModelScript PxModelScript;

// TODO
PXC_API PxModelScript* px_mds_parse(PxBuffer* buffer);
PXC_API void px_mds_destroy(PxModelScript* mdm);
