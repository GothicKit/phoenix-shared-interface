// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/font.hh>
#include <phoenix/cffi/Font.h>

PxFont* pxFntLoad(PxBuffer* buffer) {
	try {
		auto* buf = RC(px::buffer, buffer);
		auto ani = px::font::parse(buf->duplicate());
		return RC(PxFont, new phoenix::font(std::move(ani)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxFont* pxFntLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxFont* result = pxFntLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

char const* pxFntGetName(PxFont const* fnt) {
	return RCC(px::font, fnt)->name.c_str();
}

uint32_t pxFntGetHeight(PxFont const* fnt) {
	return RCC(px::font, fnt)->height;
}

uint32_t pxFntGetGlyphCount(PxFont const* fnt) {
	return (uint32_t) RCC(px::font, fnt)->glyphs.size();
}

void pxFntGetGlyph(PxFont const* fnt, uint32_t i, uint8_t* width, PxVec2* upper, PxVec2* lower) {
	auto const& src = RCC(px::font, fnt)->glyphs[i];
	*width = src.width;
	upper->x = src.uv[0].x;
	upper->y = src.uv[0].y;
	lower->x = src.uv[1].x;
	lower->y = src.uv[1].y;
}

void pxFntDestroy(PxFont* fnt) {
	delete RC(phoenix::font, fnt);
}
