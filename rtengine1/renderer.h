/*
solution:	raytracing
project:	rtengine1
file:		renderer.h
author:		cj
*/

#pragma once

#include "../common/singleton.h"
#include "texture.h"
#include "renderbuffer.h"
#include "framebuffer.h"
#include "program.h"

namespace RT1 {

	class World;

	class Renderer {
	private:
		int _width, _height;
		Texture _renderTarget;
		Renderbuffer _depthBuffer;
		Framebuffer _framebuffer;
		Program _program;

		enum {
			WORLD_SPHERE_GEOMETRY_TEX_LEVEL = 1,
			WORLD_SPHERE_COLOR_TEX_LEVEL = 2
		};
		const World* _world;
	public:
		Renderer(int width, int height);

		const Texture& GetRenderTarget(void) const {
			return _renderTarget;
		}

		Program& GetProgram(void) { return _program; }

		void SetDepth(int depth);

		void SetWorld(const World& world);
		void SetWorldMatrix(const M::Matrix4& worldMatrix);

		void SetLightPosition(const M::Vector3& pos);
		void SetLightAttenuation(float constant, float linear, float quadric);

		void Render(void);
		void RenderOverlay(void);
	};

} // namespace RT1