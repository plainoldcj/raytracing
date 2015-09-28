/*
solution:	raytracing
project:	rtengine0
file:		renderer.h
author:		cj
*/

#pragma once

#include "../common/singleton.h"
#include "../system/glx.h"
#include "../system/thread.h"
#include "rtengine.h"
#include "framebuffer.h"

namespace M { struct Matrix4; }

namespace RT0 {

	class World;
	class RayCaster;
	class FrameListener;

	class Renderer : public GEN::Singleton<Renderer> {
		friend class GEN::Singleton<Renderer>;
	private:
		std::list<GEN::Pointer<RayCaster> > _rayCaster;
	public:
		~Renderer(void) { Kill(); }

		void Render(Framebuffer& _framebuffer, const World& world, 
			shaderAlloc_t shaderAlloc, const M::Matrix4& worldMatrix,
			FrameListener* frameListener = NULL);
		void Kill(void);
		void Join(void);
	};

} // namespace RT0