// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/texture.hh>
#include <phoenix/cffi/Texture.h>

PxTexture* pxTexLoad(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto scr = phoenix::texture::parse(buf->duplicate());
		return reinterpret_cast<PxTexture*>(new phoenix::texture(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

PxTexture* pxTexLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) return nullptr;

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxTexture* result = pxTexLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxTexDestroy(PxTexture* tex) {
	delete reinterpret_cast<phoenix::texture*>(tex);
}

void pxTexGetMeta(PxTexture const* tex, uint32_t* format, uint32_t* width, uint32_t* height, uint32_t* mipmapCount, uint32_t* averageColor) {
	auto* t = reinterpret_cast<phoenix::texture const*>(tex);
	*format = t->format();
	*width = t->width();
	*height = t->height();
	*mipmapCount = t->mipmaps();
	*averageColor = t->average_color();
}

uint8_t const* pxTexGetMipmap(PxTexture const* tex, uint32_t level, uint32_t* width, uint32_t* height) {
	auto* t = reinterpret_cast<phoenix::texture const*>(tex);
	*width = t->mipmap_width(level);
	*height = t->mipmap_height(level);
	return t->data(level).data();
}

