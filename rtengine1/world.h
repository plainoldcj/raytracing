/*
solution:	raytracing
project:	rtengine1
file:		world.h
author:		cj
*/

#pragma once

#include <vector>
#include "../math/vector3.h"
#include "../math/sphere.h"
#include "../system/glx.h"
#include "color.h"

namespace RT1 {

	class Program;
	struct Color;

	class World {
	private:
		struct SphereColor {
			float r, g, b;

			SphereColor(const Color& color)
				: r(color.r), g(color.g), b(color.b) { }
		};

		std::vector<M::Sphere> _sphereGeometry;
		std::vector<SphereColor> _sphereColors;

		GLuint _sphereGeometryTexId;
		GLuint _sphereColorTexId;
		unsigned _sphereTexCapacity;
	public:
		World(void);

		void AddSphere(const M::Sphere& sphere, const Color& color) {
			_sphereGeometry.push_back(sphere);
			_sphereColors.push_back(color);
		}

		M::Sphere& GetSphereGeometry(int index) { return _sphereGeometry[index]; }


		void UpdateSpheres(void);

		int GetNumSpheres(void) const { return _sphereGeometry.size(); }
		GLuint GetSphereGeometryTexID(void) const { return _sphereGeometryTexId; }
		GLuint GetSphereColorTexID(void) const { return _sphereColorTexId; }
	};

} // namespace RT1