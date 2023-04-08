// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Texture.h>
#include <phoenix/texture.hh>

PxTexture* pxTexLoad(PxBuffer* buffer) {
	try {
		auto scr = phoenix::texture::parse(buffer->duplicate());
		return new phoenix::texture(std::move(scr));
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
	delete tex;
}

void pxTexGetMeta(PxTexture const* tex,
                  phoenix::texture_format* format,
                  uint32_t* width,
                  uint32_t* height,
                  uint32_t* mipmapCount,
                  uint32_t* averageColor) {
	*format = tex->format();
	*width = tex->width();
	*height = tex->height();
	*mipmapCount = tex->mipmaps();
	*averageColor = tex->average_color();
}

uint8_t const* pxTexGetMipmap(PxTexture const* tex, uint32_t level, uint32_t* width, uint32_t* height) {
	*width = tex->mipmap_width(level);
	*height = tex->mipmap_height(level);
	return tex->data(level).data();
}
