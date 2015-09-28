/*
solution:	raytracing
project:	cmath
file:		ray.cu
author:		cj
*/

#pragma once

#include "vector3.cuh"

namespace CM {

	struct Ray {
		Vector3 origin;
		Vector3 direction;

		CM_API Ray(void) { }
		CM_API Ray(const Vector3& origin, const Vector3& direction)
			: origin(origin), direction(direction) { }
	};

} // namespace CM