/*
solution:	raytracing
project:	cmath
file:		intersections.cu
author:		cj
*/

#pragma once

#ifndef NULL
#define NULL 0
#endif

#include "vector3.cuh"

namespace CM {

	struct Ray;
	struct Sphere;
	struct Plane;

	namespace IS {

		struct Info {
			Vector3 where;
			Vector3 normal;
			float distance;
			bool inside; // origin of ray is inside primitive
		};

		CM_API bool IntersectAnalytically(const Ray& ray, const Sphere& sphere, Info* info) {
			const float r2 = sphere.radius * sphere.radius;
			const CM::Vector3 a = ray.origin - sphere.center;
			const float b = CM::Dot(ray.direction, a);
			const float c = CM::Dot(a, a);
			const float d = r2 - c + b * b;
			if(0.0f < d) {
				const float e = sqrtf(d);
				
				bool hit = false;

				float dist = CM::Min(-e - b, e - b);
				if(0.0f < dist) hit = true;
			
				if(hit && info) {
					info->where = ray.origin + dist * ray.direction;
					info->distance = dist;
					info->normal = CM::Normalize(info->where - sphere.center);
					
					if(0.0f >= c - r2) {
						info->inside = true;
						// when the ray originates inside the sphere we flip the normal
						info->normal *= -1.0f;
					}
				}

				return hit;
			}
			return false;
		}

		CM_API bool IntersectAnalytically(const Ray& ray, const Plane& plane, Info* info) {
			float D = CM::Dot(plane.normal, ray.direction);
			if(D < 0.0f) {
				const float eps = 0.001f;
				float t = (plane.distance - CM::Dot(plane.normal, ray.origin)) / D;
				if(eps < t) {
					if(info) {
						info->distance = t;
						info->where = ray.origin + t * ray.direction;
						info->normal = plane.normal;
						info->inside = false; // we do not care at the moment
					}
					return true;
				}
			}

			return false;
		}

	} // namespace IS

} // namespace CM