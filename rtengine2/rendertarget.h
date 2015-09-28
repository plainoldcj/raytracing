/*
solution:	raytracing
project:	rtengine2
file:		rendertarget.h
author:		cj
*/

#pragma once

#include "../common/common.h"
#include "../common/uncopyable.h"
#include "../glutil/texture.h"

struct cudaGraphicsResource;
struct cudaArray;
typedef cudaGraphicsResource* cudaRes_t;

namespace RT2 {

	class RenderTarget : private GEN::Uncopyable {
	private:
		GLU::Texture _texture;
		COM::byte_t* _deviceMem;
		unsigned _pitch;
		cudaRes_t _resource;

		cudaArray* _array;
	public:
		RenderTarget(COM::size_t width, COM::size_t height);
		~RenderTarget(void);

		void Map(void);
		void Unmap(void);
		COM::byte_t* GetDeviceMemory(void) const { return _deviceMem; }
		unsigned GetPitch(void) const { return _pitch; }

		int Width(void) const { return _texture.Width(); }
		int Height(void) const { return _texture.Height(); }
		void Bind(void) const { _texture.Bind(0); }
	};

} // namespace RT2