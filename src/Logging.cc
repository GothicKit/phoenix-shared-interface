// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"
#include "phoenix/phoenix.hh"

#include <phoenix/cffi/Logging.h>

void px_set_logger(PxLogCallback cb) {
	phoenix::logging::use_logger([cb](phoenix::logging::level lvl, std::string const& message) {
		cb((uint8_t) lvl, message.c_str());
	});
}

void px_set_logger_default() {
	phoenix::logging::use_default_logger();
}
