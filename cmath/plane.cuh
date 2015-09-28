/*
solution:	raytracing
project:	cmath
file:		plane.cuh
author:		cj
*/

#pragma once

#include "vector3.cuh"

namespace CM {

	struct Plane {
		Vector3 normal;
		float distance;

		CM_API Plane(void) { }
		CM_API Plane(const Vector3& normal, float distance)
			: normal(normal), distance(distance) { }
	};

} // namespace CM