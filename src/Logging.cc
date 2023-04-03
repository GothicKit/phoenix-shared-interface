// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"
#include "phoenix/phoenix.hh"

#include <phoenix/cffi/Logging.h>

void pxLoggerSet(PxLogCallback cb) {
	phoenix::logging::use_logger([cb](phoenix::logging::level lvl, std::string const& message) {
		cb((uint8_t) lvl, message.c_str());
	});
}

void pxLoggetSetDefault() {
	phoenix::logging::use_default_logger();
}
