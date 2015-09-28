/*
solution:	raytracing
project:	rtengine0
file:		framebuffer.cpp
author:		cj
*/

#include "framebuffer.h"

namespace RT0 {

	inline COM::size_t Framebuffer::Index(COM::size_t x, COM::size_t y) const {
		// seems like glTexImage2D takes images column-major
		return x + _height * y;
	}

	Framebuffer::Framebuffer(COM::size_t width, COM::size_t height)
		:	_width(width), _height(height),
			_buffer(NULL)
	{
		_buffer = new Pixel[_width * _height];
		memset(_buffer, 0, sizeof(Pixel) * _width * _height);
	}

	Framebuffer::~Framebuffer(void) {
		if(_buffer) {
			delete[] _buffer;
		}
	}

	void Framebuffer::Clear(void) {
		memset(_buffer, 0, sizeof(Pixel) * _width * _height);
	}

	void Framebuffer::SetPixel(COM::size_t x, COM::size_t y, const Pixel& pixel) {
		_buffer[Index(x, y)] = pixel;
	}

} // namespace RT0