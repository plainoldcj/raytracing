/*
solution:	raytracing
project:	cmath
file:		sphere.cu
author:		cj
*/

#pragma once

#include "vector3.cuh"

namespace CM {

	struct Sphere {
		Vector3 center;
		float radius;

		CM_API Sphere(void) { }
		CM_API Sphere(const Vector3& center, float radius) : center(center), radius(radius) { }
	};

} // namespace CM