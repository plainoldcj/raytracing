/*
solution:	raytracing
project:	rtengine0
file:		ent_sphere.h
author:		cj
*/

#include "entity.h"

namespace RT0 {
namespace ENT {

	class Sphere : public Entity {
	private:
		float _radius;
	public:
		explicit Sphere(float radius);
		virtual ~Sphere(void) { }

		bool Intersects(const M::Ray& ray, IntersectionInfo* info = NULL) const;
	};

} // namespace ENT
} // namespace RT0