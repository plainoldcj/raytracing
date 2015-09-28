/*
solution:	glib
			raytracing
project:	prenderer
			rtengine1
			glutil
file:		renderbuffer.cpp
author:		cj
*/

#include "renderbuffer.h"

namespace GLU {

	Renderbuffer::Renderbuffer(GLenum type, int width, int height)
		: _width(width), _height(height)
	{
		glx.GenRenderbuffers(1, &_id);
		glx.BindRenderbuffer(GL_RENDERBUFFER, _id);
		glx.RenderbufferStorage(GL_RENDERBUFFER, type, width, height);
	}

	Renderbuffer::~Renderbuffer(void) {
		glx.DeleteRenderbuffers(1, &_id);
	}

} // namespace GLU