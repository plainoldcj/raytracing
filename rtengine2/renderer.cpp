/*
solution:	raytracing
project:	rtengine2
file:		renderer.cpp
author:		cj
*/

#include "cuda.h"
#include "world.h"
#include "renderer.h"
#include "kernel.h"

namespace RT2 {

	Renderer::Renderer(int width, int height)
		:	_width(width), _height(height)
	{
		CUDA_CALL(cudaGLSetGLDevice(0));
		_renderTarget = GEN::Pointer<RenderTarget>(new RenderTarget(width, height));
		
		/*
		recursion is only available since sm20
		unsigned stackLimit;
		CUDA_CALL(cudaDeviceGetLimit(&stackLimit, cudaLimitStackSize));
		COM::log << "INFO: the cuda stack size of device 0 is " << stackLimit << std::endl;
		*/
	}

	void Renderer::Render(World& world) {
		RunKernel(*_renderTarget, world);				

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		_renderTarget->Bind();
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

} // namespace RT2