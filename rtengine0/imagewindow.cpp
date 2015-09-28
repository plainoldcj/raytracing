/*
solution:	raytracing
project:	rtengine0
file:		imagewindow.cpp
author:		cj
*/

#include "framebuffer.h"
#include "renderer.h"
#include "imagewindow.h"

namespace RT0 {

	void ImageWindow::CloseEvent(void) {
		RT0::Renderer::Instance().Kill();
	}

	ImageWindow::ImageWindow(const Framebuffer& framebuffer, int width, int height)
		:	base_t(NULL, TEXT("Image Window"), width, height, SYS::WS_NONRESIZABLE),
			_framebuffer(framebuffer)
	{
		glEnable(GL_TEXTURE_2D);

		glGenTextures(1, &_texId);
		glBindTexture(GL_TEXTURE_2D, _texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, framebuffer.GetWidth(), framebuffer.GetHeight(),
			0, GL_RGBA, GL_UNSIGNED_BYTE, framebuffer.GetPixels());

		// you have to set these filters for texturing to work ...
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void ImageWindow::UpdateSubFrame(int x, int y, int w, int h) {
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, _framebuffer.GetPixels());
	}

	void ImageWindow::Render(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, _texId);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
		glEnd();

		if(IsRendering())
			UpdateSubFrame(0, 0, _framebuffer.GetWidth(), _framebuffer.GetHeight());
	}

} // namespace RT0