/*
solution:	raytracing
project:	rtengine0
file:		renderer.cpp
author:		cj
*/

#include "../common/config.h"
#include "raycaster.h"
#include "renderer.h"

namespace RT0 {

	void Renderer::Render(Framebuffer& framebuffer, const World& world, 
		shaderAlloc_t shaderAlloc, const M::Matrix4& worldMatrix,
		FrameListener* frameListener)
	{
		COM::Config& config = COM::Config::Instance();
		int numThreads = config.Get("numthreads", 4);

		_rayCaster.clear();

		int frameHeight = framebuffer.GetHeight() / numThreads;
		int i;
		for(i = 0; i < numThreads; ++i) {
			GEN::Pointer<RayCaster> rayCaster(new RayCaster(framebuffer, world, shaderAlloc(),
				worldMatrix, 0, i * frameHeight, framebuffer.GetWidth(), frameHeight));
			_rayCaster.push_back(rayCaster);
			rayCaster->SetFrameListener(frameListener);
			rayCaster->Start();
		}

		int d = framebuffer.GetHeight() - numThreads * frameHeight;
		if(d > 0) {
			GEN::Pointer<RayCaster> rayCaster(new RayCaster(framebuffer, world, shaderAlloc(),
				worldMatrix, 0, i * frameHeight, framebuffer.GetWidth(), d));
			_rayCaster.push_back(rayCaster);
			rayCaster->SetFrameListener(frameListener);
			rayCaster->Start();
		}
	}

	void Renderer::Kill(void) {
		for(std::list<GEN::Pointer<RayCaster> >::iterator casterIt(_rayCaster.begin());
			casterIt != _rayCaster.end(); ++casterIt) 
		{
			(*casterIt)->Kill();
		}
		_rayCaster.clear();
	}

	void Renderer::Join(void) {
		for(std::list<GEN::Pointer<RayCaster> >::iterator casterIt(_rayCaster.begin());
			casterIt != _rayCaster.end(); ++casterIt) 
		{
			(*casterIt)->Join();
		}
	}

} // namespace RT0