/*
solution:	raytracing
project:	rtengine1
file:		world.cpp
author:		cj
*/

#include "program.h"
#include "world.h"

namespace RT1 {

	World::World(void) 
		:	_sphereGeometryTexId(0),
			_sphereColorTexId(0),
			_sphereTexCapacity(0) 
	{
	}

	void World::UpdateSpheres(void) {
		if(_sphereTexCapacity < _sphereGeometry.size()) {
			if(_sphereGeometryTexId) glDeleteTextures(1, &_sphereGeometryTexId);
			if(_sphereColorTexId) glDeleteTextures(1, &_sphereColorTexId);
			
			glGenTextures(1, &_sphereGeometryTexId);
			glBindTexture(GL_TEXTURE_2D, _sphereGeometryTexId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _sphereGeometry.capacity(), 1, 0, GL_RGBA,
				GL_FLOAT, NULL);

			// you have to set these filters for texturing to work ...
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glGenTextures(1, &_sphereColorTexId);
			glBindTexture(GL_TEXTURE_2D, _sphereColorTexId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, _sphereColors.capacity(), 1, 0, GL_RGB,
				GL_FLOAT, NULL);

			// ... for each texture ...
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			_sphereTexCapacity = _sphereGeometry.capacity();
		}

		glBindTexture(GL_TEXTURE_2D, _sphereGeometryTexId);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _sphereGeometry.size(), 1, GL_RGBA,
			GL_FLOAT, &_sphereGeometry[0]);

		glBindTexture(GL_TEXTURE_2D, _sphereColorTexId);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _sphereColors.size(), 1, GL_RGB,
			GL_FLOAT, &_sphereColors[0]);
	}

} // namespace RT1