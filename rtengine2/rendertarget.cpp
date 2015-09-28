/*
solution:	raytracing
project:	rtengine2
file:		rendertarget.cpp
author:		cj
*/

#include "cuda.h"
#include "rendertarget.h"

namespace RT2 {

	RenderTarget::RenderTarget(COM::size_t width, COM::size_t height)
		: _texture(width, height, GL_RGBA32F, GL_RGBA, GL_FLOAT)
	{
		int sdfheight = _texture.Height();
		CUDA_CALL(cudaMallocPitch((void**)&_deviceMem, &_pitch,
			width * sizeof(float) * 4, height));

		CUDA_CALL(cudaGraphicsGLRegisterImage(&_resource, _texture.GetID(),
			GL_TEXTURE_2D, cudaGraphicsMapFlagsNone));
	}

	RenderTarget::~RenderTarget(void) {
		CUDA_CALL(cudaGraphicsUnregisterResource(_resource));
	}

	void RenderTarget::Map(void) {
		glBindTexture(GL_TEXTURE_2D, 0);
		CUDA_CALL(cudaGraphicsMapResources(1, &_resource, 0));
		CUDA_CALL(cudaGraphicsSubResourceGetMappedArray(&_array,
			_resource, 0, 0));
	}

	void RenderTarget::Unmap(void) {
		cudaMemcpy2DToArray(_array, 0, 0,
			_deviceMem, _pitch,
			_texture.Width() * sizeof(float) * 4, _texture.Height(),
			cudaMemcpyDeviceToDevice);

		CUDA_CALL(cudaGraphicsUnmapResources(1, &_resource, 0));
	}

} // namespace RT2