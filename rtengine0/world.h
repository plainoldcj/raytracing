/*
solution:	raytracing
project:	rtengine0
file:		world.h
author:		cj
*/

#pragma once

#include <list>
#include "../common/pointer.h"
#include "../math/ray.h"
#include "../math/matrix4.h"
#include "entity.h"
#include "light.h"

namespace RT0 {

	class Shader;

	typedef GEN::Pointer<Entity> entPtr_t;
	typedef GEN::Pointer<Light> lightPtr_t;

	class World {
	private:
		typedef std::list<entPtr_t>::const_iterator centIt_t;
		typedef std::list<lightPtr_t>::const_iterator clightIt_t;

		std::list<entPtr_t> _entities;
		std::list<lightPtr_t> _lights;
	public:
		struct IntersectionInfo {
			bool primary;
			M::Ray ray;
			entPtr_t entity;
			Entity::IntersectionInfo einfo;
		};

		void AddEntity(entPtr_t entity);
		void AddLight(lightPtr_t light);

		bool Intersects(const M::Ray& ray, IntersectionInfo* info = NULL) const;

		void CastShadowRays(Shader& shader, const M::Vector3& point) const;
		Color CastReflectionRay(int depth, Shader& shader, const M::Vector3& point, const M::Vector3& incident, const M::Vector3& normal) const;
	};

} // namespace RT0