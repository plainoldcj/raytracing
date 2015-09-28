/*
solution:	raytracing
project:	rtengine0
file:		ent_sphere.cpp
author:		cj
*/

#include "../math/ray.h"
#include "../math/sphere.h"
#include "../math/intersections.h"
#include "ent_sphere.h"

namespace RT0 {
namespace ENT {

	Sphere::Sphere(float radius) : _radius(radius) { }

	bool Sphere::Intersects(const M::Ray& ray, IntersectionInfo* info) const {
		M::IS::Info* minfo = NULL;
		if(info) minfo = &info->minfo;

		return M::IS::Analytically(ray, M::Sphere(GetPosition(), _radius), minfo);
	}

} // namespace ENT
} // namespace RT0