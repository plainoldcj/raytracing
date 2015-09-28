/*
solution:	raytracing
project:	rtengine1
file:		renderer.cpp
author:		cj
*/

#include "../common/config.h"
#include "../math/matrix4.h"
#include "world.h"
#include "renderer.h"

namespace RT1 {

	void RenderDummyScene(void) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f( 0.0f,  1.0f);
		glVertex2f( 1.0f, -1.0f);
		glEnd();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	Renderer::Renderer(int width, int height)
		:	_width(width), _height(height),
			_renderTarget(width, height, GL_RGB32F, GL_RGB),
			_depthBuffer(Renderbuffer::DEPTH_BUFFER, width, height),
			_world(NULL)
	{
		_framebuffer.Attach(Framebuffer::COLOR_BUFFER_0, _renderTarget);
		_framebuffer.Attach(Framebuffer::DEPTH_BUFFER, _depthBuffer);

		_program.Attach("Shader\\ps_rt0.txt", Shader::PIXEL_SHADER);
		_program.Attach("Shader\\vs_rt0.txt", Shader::VERTEX_SHADER);

		COM::Config& config = COM::Config::Instance();
		int fixedLight = config.Get("fixedlight", 0);
		int perspective = config.Get("perspective", 0);

		_program.Use();
		_program.SetUniform("uniFixedLight", fixedLight);
		_program.SetUniform("uniPerspective", perspective);
		UnbindProgram();

		SetWorldMatrix(M::Mat4::Identity());
	}

	void Renderer::SetDepth(int depth) {
		_program.Use();
		_program.SetUniform("uniDepth", depth);
		UnbindProgram();
	}

	void Renderer::SetWorld(const World& world) {
		_program.Use();
		_program.SetUniform("uniSphereGeometrySampler", (int)WORLD_SPHERE_GEOMETRY_TEX_LEVEL);
		_program.SetUniform("uniSphereColorSampler", (int)WORLD_SPHERE_COLOR_TEX_LEVEL);
		_program.SetUniform("uniNumSpheres", world.GetNumSpheres());
		UnbindProgram();
		_world = &world;
	}

	void Renderer::SetLightPosition(const M::Vector3& pos) {
		// i forgot to use the program at this point and
		// spent hours debugging... :(
		_program.Use();
		_program.SetUniform("uniLightPos", pos);
		UnbindProgram();
	}

	void Renderer::SetLightAttenuation(float constant, float linear, float quadric) {
		_program.Use();
		_program.SetUniform("uniLightConstantAttenuation", constant);
		_program.SetUniform("uniLightLinearAttenuation", linear);
		_program.SetUniform("uniLightQuadricAttenuation", quadric);
		UnbindProgram();
	}

	void Renderer::SetWorldMatrix(const M::Matrix4& worldMatrix) {
		M::Matrix4 invWorld = M::RigidInverse(worldMatrix);
		// i wonder how expensive using and unbinding a program is...
		_program.Use();
		_program.SetUniform("uniInvWorldMat", invWorld);
		UnbindProgram();
	}

	void Renderer::Render(void) {
		glPushAttrib(GL_VIEWPORT_BIT);
		glViewport(0, 0, _width, _height);

		_framebuffer.Bind();

		GLenum buffers[] = {
			Framebuffer::COLOR_BUFFER_0
		};
		const int numBuffers = sizeof(buffers) / sizeof(GLenum);
		glx.DrawBuffers(numBuffers, buffers);

		_program.Use();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(_world) {
			glx.ActiveTexture(GL_TEXTURE0 + WORLD_SPHERE_GEOMETRY_TEX_LEVEL);
			glBindTexture(GL_TEXTURE_2D, _world->GetSphereGeometryTexID());
			glx.ActiveTexture(GL_TEXTURE0 + WORLD_SPHERE_COLOR_TEX_LEVEL);
			glBindTexture(GL_TEXTURE_2D, _world->GetSphereColorTexID());
			glx.ActiveTexture(GL_TEXTURE0);
		}

		glBegin(GL_QUADS);
		glTexCoord2f(-1.0f, -1.0f); glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(-1.0f,  1.0f); glVertex2f(-1.0f,  1.0f);
		glTexCoord2f( 1.0f,  1.0f); glVertex2f( 1.0f,  1.0f);
		glTexCoord2f( 1.0f, -1.0f); glVertex2f( 1.0f, -1.0f);
		glEnd();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		UnbindProgram();

		UnbindFramebuffer();

		glPopAttrib();
	}

	void Renderer::RenderOverlay(void) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		_renderTarget.Bind(0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
		glEnd();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

} // namespace RT1