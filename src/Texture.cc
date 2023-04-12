// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/cffi/Texture.h>
#include <phoenix/texture.hh>

PxTexture* pxTexLoad(PxBuffer* buffer) {
	try {
		auto scr = phoenix::texture::parse(buffer->duplicate());
		return new phoenix::texture(std::move(scr));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error, "encountered exception while parsing PxTexture: ", e.what());
		return nullptr;
	}
}

PxTexture* pxTexLoadFromVdf(PxVdf const* vdf, char const* name) {
	PxVdfEntry const* entry = pxVdfGetEntryByName(vdf, name);
	if (entry == nullptr) {
		px::logging::log(px::logging::level::error, "failed to find vdf entry ", name);
		return nullptr;
	}

	PxBuffer* buf = pxVdfEntryOpenBuffer(entry);
	PxTexture* result = pxTexLoad(buf);
	pxBufferDestroy(buf);
	return result;
}

void pxTexDestroy(PxTexture* tex) {
	delete tex;
}

void pxTexGetMeta(PxTexture const* tex,
                  PxTextureFormat* format,
                  uint32_t* width,
                  uint32_t* height,
                  uint32_t* mipmapCount,
                  uint32_t* averageColor) {
	*format = static_cast<PxTextureFormat>(tex->format());
	*width = tex->width();
	*height = tex->height();
	*mipmapCount = tex->mipmaps();
	*averageColor = tex->average_color();
}

uint8_t const*
pxTexGetMipmap(PxTexture const* tex, uint32_t* length, uint32_t level, uint32_t* width, uint32_t* height) {
	auto& data = tex->data(level);
	*length = (uint32_t) data.size();
	*width = tex->mipmap_width(level);
	*height = tex->mipmap_height(level);
	return data.data();
}

uint8_t* pxTexGetDecompressedData(PxTexture const* tex, uint32_t level, uint32_t* size) {
	auto rgb = tex->as_rgba8(level);
	*size = (uint32_t) rgb.size();

	// TODO: Performance!
	auto* mem = static_cast<uint8_t*>(malloc(*size));
	std::copy_n(rgb.data(), *size, mem);
	return mem;
}

void pxTexFreeDecompressedData(PxTexture const* tex, uint8_t* data) {
	free(data);
}
