/*
solution:	raytracing
project:	rtengine0
file:		raycaster.h
author:		cj
*/

#pragma once

#include "../common/common.h"
#include "../common/pointer.h"
#include "../system/thread.h"
#include "../math/matrix4.h"
#include "../math/vector3.h"

namespace RT0 {

	class Framebuffer;
	class World;
	class Shader;
	class Renderer;

	class FrameListener {
	private:
		unsigned _threadsRendering;
	public:
		FrameListener(void) : _threadsRendering(0) { }
		virtual ~FrameListener(void) { }

		void BeginRendering(void) { InterlockedIncrement(&_threadsRendering); }
		void EndRendering(void) { InterlockedDecrement(&_threadsRendering); }

		bool IsRendering(void) const { return 0 < _threadsRendering; }
	};

	class RayCaster : public SYS::Thread {
	private:
		Framebuffer& _framebuffer;
		const World& _world;
		GEN::Pointer<Shader> _shader;
		int _depth; // recursion depth
		COM::size_t _x, _y, _w, _h; // subframe
		M::Matrix4 _invWorld;
		M::Vector3 _rayDir;

		FrameListener* _frameListener;
	public:
		RayCaster(Framebuffer& framebuffer,
			const World& world, 
			GEN::Pointer<Shader> shader,
			const M::Matrix4& worldMatrix,
			COM::size_t x, COM::size_t y,
			COM::size_t w, COM::size_t h);

		void SetFrameListener(FrameListener* frameListener);

		DWORD Run(void);
	};

} // namespace RT0