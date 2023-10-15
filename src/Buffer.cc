// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "Prelude.h"

#include <phoenix/buffer.hh>
#include <phoenix/cffi/Buffer.h>

class raw_buffer_backing : public px::buffer_backing {
public:
	raw_buffer_backing(uint8_t const* bytes, uint64_t length) : _m_buffer(bytes), _m_size(length) {}

	[[nodiscard]] bool direct() const noexcept override {
		return false;
	}

	[[nodiscard]] bool readonly() const noexcept override {
		return false;
	}

	[[nodiscard]] uint64_t size() const noexcept override {
		return _m_size;
	}

	[[nodiscard]] const std::byte* array() const override {
		return reinterpret_cast<std::byte const*>(_m_buffer);
	}

	void read(std::byte* buf, std::uint64_t size, std::uint64_t offset) const override {
		if (this->readonly()) {
			throw px::buffer_readonly {};
		}

		if (offset + size > this->size()) {
			throw px::buffer_overflow {offset, size, "in backing"};
		}

		std::copy_n(reinterpret_cast<std::byte const*>(_m_buffer) + static_cast<long>(offset), size, buf);
	}

private:
	uint8_t const* _m_buffer;
	uint64_t _m_size;
};

PxBuffer* pxBufferCreate(uint8_t const* bytes, uint64_t size) {
	auto back = std::make_shared<raw_buffer_backing>(bytes, size);
	return new px::buffer(std::move(back));
}

PxBuffer* pxBufferMmap(char const* file) {
	try {
		auto buf = px::buffer::mmap(file);
		return new px::buffer(std::move(buf));
	} catch (std::exception const& e) {
		px::logging::log(px::logging::level::error,
		                 "CAPI:PxBuffer",
		                 "encountered exception while memory-mapping PxBuffer: %s",
		                 e.what());
		return nullptr;
	}
}

void pxBufferDestroy(PxBuffer* buffer) {
	delete buffer;
}

uint64_t pxBufferSize(PxBuffer* buffer) {
	return buffer->limit();
}

uint8_t* pxBufferArray(PxBuffer* buffer) {
	auto* data = new std::uint8_t[buffer->limit()];
	buffer->get(data, buffer->limit());
	return data;
}
