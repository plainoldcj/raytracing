/*
solution:	raytracing
project:	rtengine0
file:		framebuffer.h
author:		cj
*/

#pragma once

#include "../common/common.h"
#include "../common/uncopyable.h"

namespace RT0 {

	struct Pixel {
		COM::byte_t r, g, b, a;

		Pixel(void) { }
		Pixel(COM::byte_t r, COM::byte_t g, COM::byte_t b, COM::byte_t a = 0) : r(r), g(g), b(b), a(a) { }
	};

	class Framebuffer : private GEN::Uncopyable {
	private:
		Pixel* _buffer;
		COM::size_t _width, _height;

		COM::size_t Index(COM::size_t x, COM::size_t y) const;
	public:
		Framebuffer(COM::size_t width, COM::size_t height);
		~Framebuffer(void);

		COM::size_t GetWidth(void) const { return _width; }
		COM::size_t GetHeight(void) const { return _height; }
		const Pixel* const GetPixels(void) const { return _buffer; }

		void Clear(void);

		void SetPixel(COM::size_t x, COM::size_t y, const Pixel& pixel);
	};

} // namespace RT0