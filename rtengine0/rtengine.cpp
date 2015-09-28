/*
solution:	raytracing
project:	rtengine0
file:		rtengine.cpp
author:		cj
*/

#include "../math/ray.h"
#include "../common/config.h"
#include "../system/timer.h"
#include "../system/thread.h"
#include "framebuffer.h"
#include "world.h"
#include "shader.h"
#include "raycaster.h"
#include "rtengine.h"

namespace RT0 {

	// orthographic camera, one ray per pixel
	void Render(Framebuffer& framebuffer, const World& world, shaderAlloc_t shaderAlloc) {
		COM::Config& config = COM::Config::Instance();
		int numThreads = config.Get("numthreads", 4);

		GEN::Pointer<RayCaster>* rayCaster = new GEN::Pointer<RayCaster>[numThreads];

		int frameHeight = framebuffer.GetHeight() / numThreads;
		for(int i = 0; i < numThreads; ++i) {
			rayCaster[i] = GEN::Pointer<RayCaster>(new RayCaster(framebuffer, world, shaderAlloc(),
				M::Mat4::Identity(), // not exposed!
				0, i * frameHeight, framebuffer.GetWidth(), frameHeight));
		}
		
		SYS::Timer timer;

		timer.Start();
		for(int i = 0; i < numThreads; ++i) rayCaster[i]->Start();
		for(int i = 0; i < numThreads; ++i) rayCaster[i]->Join();
		float secsPassed = timer.Stop();

		COM::log << "Rendering with multiple threads took " << secsPassed << " seconds" << std::endl;

		delete[] rayCaster;
	}

	void RenderST(Framebuffer& framebuffer, const World& world, shaderAlloc_t shaderAlloc) {
		SYS::Timer timer;

		timer.Start();
		RayCaster raycaster(framebuffer, world, shaderAlloc(), 
			M::Mat4::Identity(), // not exposed! 
			0, 0, 800, 800);
		raycaster.Start();
		raycaster.Join();
		float secsPassed = timer.Stop();

		COM::log << "Rendering with one thread took " << secsPassed << " seconds" << std::endl;
	}

} // namespace RT0