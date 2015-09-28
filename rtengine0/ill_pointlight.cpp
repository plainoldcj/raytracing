/*
solution:	raytracing
project:	rtengine0
file:		ill_pointlight.cpp
author:		cj
*/

#include "../math/ray.h"
#include "world.h"
#include "ill_pointlight.h"

namespace RT0 {
namespace ILL {

	float Pointlight::Illuminate(const World& world, const M::Vector3& point) const {
		M::Ray ray;
		ray.origin = point;
		ray.direction = M::Normalize(GetPosition() - point);
		if(world.Intersects(ray)) return 0.0f;
		else return 1.0f;
	}

} // namespace ILL
} // namespace RT0