// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "Api.h"

#include <stdint.h>

typedef void(*PxLogCallback)(uint8_t level, char const* message);

PXC_API void px_set_logger(PxLogCallback cb);
PXC_API void px_set_logger_default();
