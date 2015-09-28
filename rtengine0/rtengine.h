/*
solution:	raytracing
project:	rtengine0
file:		rtengine.h
author:		cj
*/

#pragma once

#include <list>
#include "../common/common.h"
#include "../common/pointer.h"
#include "../system/glx.h"

namespace RT0 {

	class Framebuffer;
	class World;
	class Shader;

	template<typename SHADER_TYPE>
	GEN::Pointer<Shader> AllocShader(void) {
		return GEN::Pointer<Shader>(new SHADER_TYPE());
	}

	typedef GEN::Pointer<Shader> (*shaderAlloc_t)(void);

	void Render(Framebuffer& framebuffer, const World& world, shaderAlloc_t shaderAlloc);
	void RenderST(Framebuffer& framebuffer, const World& world, shaderAlloc_t shaderAlloc);

} // namespace RT0