// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/texture.hh>
#include <phoenix/cffi/Texture.h>

PxTexture* px_tex_parse(PxBuffer* buffer) {
	try {
		auto buf = reinterpret_cast<phoenix::buffer*>(buffer);
		auto scr = phoenix::texture::parse(buf->duplicate());
		return reinterpret_cast<PxTexture*>(new phoenix::texture(std::move(scr)));
	} catch (std::exception const&) {
		return nullptr;
	}
}

void px_tex_get_meta(PxTexture const* tex, uint32_t* format, uint32_t* width, uint32_t* height, uint32_t* mipmapCount, uint32_t* averageColor) {
	auto* t = reinterpret_cast<phoenix::texture const*>(tex);
	*format = t->format();
	*width = t->width();
	*height = t->height();
	*mipmapCount = t->mipmaps();
	*averageColor = t->average_color();
}

uint8_t const* px_tex_get_mipmap(PxTexture const* tex, uint32_t level, uint32_t* width, uint32_t* height) {
	auto* t = reinterpret_cast<phoenix::texture const*>(tex);
	*width = t->mipmap_width(level);
	*height = t->mipmap_height(level);
	return t->data(level).data();
}

void px_tex_destroy(PxTexture* tex) {
	delete reinterpret_cast<phoenix::texture*>(tex);
}
