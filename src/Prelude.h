// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include <phoenix/phoenix.hh>

namespace px = phoenix;
#define RC(tp, vl) reinterpret_cast<tp*>(vl)
#define RCC(tp, vl) reinterpret_cast<tp const*>(vl)
