/*
solution:	raytracing
project:	rtengine2
file:		renderer.h
author:		cj
*/

#pragma once

#include "../common/common.h"
#include "rendertarget.h"

namespace RT2 {

	class World;

	class Renderer {
	private:
		int _width, _height;
		GEN::Pointer<RenderTarget> _renderTarget;
	public:
		Renderer(int width, int height);

		void Render(World& world);
	};

} // namespace RT2