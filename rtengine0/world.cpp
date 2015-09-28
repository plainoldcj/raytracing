/*
solution:	raytracing
project:	rtengine0
file:		world.cpp
author:		cj
*/

#include "shader.h"
#include "world.h"

namespace RT0 {

	void World::AddEntity(entPtr_t entity) {
		_entities.push_back(entity);
	}

	void World::AddLight(lightPtr_t light) {
		_lights.push_back(light);
	}

	bool World::Intersects(const M::Ray& ray, IntersectionInfo* info) const {
		bool hit = false;
		float minDistance = 0.0f;

		const float eps = 0.001f;
		for(centIt_t entIt(_entities.begin()); entIt != _entities.end(); ++entIt) {
			entPtr_t entity(*entIt);
			Entity::IntersectionInfo einfo;
			if(entity->Intersects(ray, &einfo) &&
				M::Abs(einfo.minfo.distance) > eps)
			{
				if(!hit) {
					hit = true;
					minDistance = einfo.minfo.distance;
					if(info) {
						info->ray = ray;
						info->entity = entity;
						info->einfo = einfo;
					}
				} else if(minDistance > einfo.minfo.distance) {
					minDistance = einfo.minfo.distance;
					if(info) {
						info->ray = ray;
						info->entity = entity;
						info->einfo = einfo;
					}
				}
			}
		}

		return hit;
	}

	void World::CastShadowRays(Shader& shader, const M::Vector3& point) const {
		for(clightIt_t lightIt(_lights.begin()); lightIt != _lights.end(); ++lightIt) {
			const float intensity = (*lightIt)->Illuminate(*this, point);
			if(intensity > 0.0f) shader.ShadowUnblocked((*lightIt));
			else shader.ShadowBlocked();
		}
	}

	Color World::CastReflectionRay(int depth, Shader& shader, const M::Vector3& point, const M::Vector3& incident, const M::Vector3& normal) const {
		M::Vector3 reflected = M::ReflectNormalized(M::Normalize(incident), normal);
		M::Ray ray;
		ray.origin = point;
		ray.direction = reflected;
		IntersectionInfo info;
		info.primary = false;
		if(Intersects(ray, &info)) return shader.Hit(depth, *this, info);
		return shader.Miss();
	}

} // namespace RT0