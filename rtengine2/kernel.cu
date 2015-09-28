/*
solution:	raytracing
project:	rtengine2
file:		kernel.cpp
author:		cj
*/

#include "../cmath/ray.cuh"
#include "../cmath/sphere.cuh"
#include "../cmath/plane.cuh"
#include "../cmath/intersections.cuh"
#include "cuda.h"
#include "rendertarget.h"
#include "world.h"
#include "kernel.h"

namespace RT2 {

	struct WInfo {
		CM::Ray ray;
		CM::IS::Info minfo;
		CM::Color color;
		float refIndex;
		float reflectivity;
		float refractivity;
		float transparency;
	};

	__device__ bool WorldIntersects(CM::Ray ray, WInfo* info, Sphere* spheres, unsigned numSpheres) {
		bool hit = false;
		float minDist = 0.0f;
		int minIndex = 0;
		int i = 0;

		const float eps = 0.001f;

		CM::IS::Info minfo;
		for(; i < numSpheres; ++i) {
			Sphere sphere = spheres[i];
			if(CM::IS::IntersectAnalytically(ray, sphere.geometry, &minfo)) {
				float dist = minfo.distance;
				if(abs(dist) > eps) {
					if(!hit) {
						hit = true;
						minDist = dist;
						minIndex = i;
						info->minfo = minfo;
					} else if(minDist > dist) {
						minDist = dist;
						minIndex = i;
						info->minfo = minfo;
					}
				}
			}
		}

		if(hit) {
			info->color = spheres[minIndex].color;
			info->ray = ray;
			info->reflectivity = spheres[minIndex].reflectivity;
			info->refractivity = spheres[minIndex].refractivity;
			info->transparency = spheres[minIndex].transparency;
			info->refIndex = spheres[minIndex].refIndex;
		}

		// hard coded floor intersection
		const CM::Plane floorPlane(CM::Vector3(0.0f, 0.0f, 1.0f), -0.5f);
		bool planeHit = false;
		if(CM::IS::IntersectAnalytically(ray, floorPlane, &minfo)) {
			float dist = minfo.distance;
			if(abs(dist) > eps) {
				if(!hit) {
					hit = true;
					minDist = dist;
					info->minfo = minfo;
					planeHit = true;
				} else if(minDist > dist) {
					minDist = dist;
					info->minfo = minfo;
					planeHit = true;
				}
			}
		}

		if(planeHit) {
			info->color = CM::Color(1.0f, 1.0f, 1.0f);
			info->ray = ray;
			info->reflectivity = 0.2f;
			info->refractivity = 0.0f;
			info->transparency = 0.0f;
		}

		return hit;
	}

	__device__ CM::Color Miss(void) {
		return CM::Color(0.8f, 0.7f, 1.0f);
	}

	template<unsigned DEPTH>
	__device__ CM::Color Hit(WInfo* info,
								Sphere* spheres, unsigned numSpheres,
								Globals* globals) 
	{
		CM::Vector3 where = info->minfo.where;
		CM::Vector3 normal = info->minfo.normal;

		CM::Vector3 dir = CM::Normalize(globals->lightPos - where);
		CM::Ray shadowRay(where, dir);

		CM::Color fragColor = CM::Color(0.0f, 0.0f, 0.0f);

		// cast shadow ray
		WInfo linfo;
		if(!WorldIntersects(shadowRay, &linfo, spheres, numSpheres)) {
			// diffuse
			float d = CM::Clamp(CM::Dot(dir, normal), 0.0f, 1.0f);
			CM::Color diff = info->color * d;
			fragColor += diff;

			// specular
			const float shininess = 20.0f;
			CM::Color spec = CM::Color(0.0f, 0.0f, 0.0f);
			if(0.0f < d) {
				CM::Vector3 s = CM::Normalize(dir + globals->eyePos - where);
				d = CM::Max(CM::Dot(s, normal), 0.0f);
				spec = powf(d, shininess) * CM::Color(1.0f, 1.0f, 1.0f);
			}
			fragColor += spec;
		}

		// cast reflection ray
		const float reflectivity = info->reflectivity;
		if(0.0f < reflectivity) {
			CM::Ray reflectionRay(where, CM::ReflectNormalized(info->ray.direction, normal));
			if(WorldIntersects(reflectionRay, &linfo, spheres, numSpheres)) {
				fragColor += reflectivity * Hit<DEPTH - 1>(&linfo, spheres, numSpheres, globals);
			} else {
				fragColor += reflectivity * Miss();
			}
		}

		// cast refraction ray
		/*const float refractivity = info->refractivity;
		if(0.0f < refractivity) {
			CM::Ray refractionRay(where, CM::RefractNormalized(info->ray.direction, normal, 1.003f, info->refIndex));
			if(WorldIntersects(refractionRay, &linfo, spheres, numSpheres)) {
				fragColor += refractivity * Hit<DEPTH - 1>(&linfo, spheres, numSpheres, globals);
			} else {
				fragColor += refractivity * Miss();
			}
		}*/

		// cast transparency ray
		/*
		const float transparency = info->transparency;
		if(0.0f < transparency) {
			CM::Ray transparencyRay(where, info->ray.direction);
			if(WorldIntersects(transparencyRay, &linfo, spheres, numSpheres)) {
				fragColor += transparency * Hit<DEPTH - 1>(&linfo, spheres, numSpheres, globals);
			} else {
				fragColor += transparency * Miss();
			}
		}
		*/

		return fragColor;
	}

	template<>
	__device__ CM::Color Hit<0>(WInfo*, Sphere*, unsigned, Globals*) {
		return CM::Color(0.0f, 0.0f, 0.0f);
	}

	__device__ CM::Color Saturate(CM::Color color) {
		if(1.0f <= color.r) color.r = 1.0f;
		if(1.0f <= color.g) color.g = 1.0f;
		if(1.0f <= color.b) color.b = 1.0f;
		if(1.0f <= color.a) color.a = 1.0f;
		return color;
	}

	__global__ void Kernel(COM::byte_t* renderTarget, unsigned pitch, float dx, float dy,
							Sphere* spheres, unsigned numSpheres,
							Globals* globals) 
	{
		int x = blockIdx.x * 16 + threadIdx.x;
		int y = blockIdx.y * 16 + threadIdx.y;
		CM::Color* pixel = (CM::Color*)(renderTarget + y * pitch) + x;

		float fx = -1.0f + x * dx;
		float fy = -1.0f + y * dy;
		const float viewDistance = 10.0f;

		CM::Vector3 viewDir = CM::Normalize(CM::Transform(globals->invWorld, CM::Vector3(fx, fy, -viewDistance)));
		CM::Vector3 eyePos = CM::Transform(globals->invWorld, CM::Vector3(0.0f, 0.0f, viewDistance));

		globals->lightPos = CM::Transform(globals->invWorld, globals->lightPos);

		CM::Ray ray;
		ray.origin = eyePos;
		ray.direction = viewDir;

		globals->eyePos = eyePos;

		CM::Color fragColor;

		WInfo info;
		if(WorldIntersects(ray, &info, spheres, numSpheres)) {
			fragColor = Hit<2>(&info, spheres, numSpheres, globals);
		} else {
			fragColor = Miss();
		}

		*pixel = Saturate(fragColor);
	}

	void RunKernel(RenderTarget& renderTarget, RT2::World& world) {
		const float dx = 2.0f / renderTarget.Width();
		const float dy = 2.0f / renderTarget.Height();

		glBindTexture(GL_TEXTURE_2D, 0);
		renderTarget.Map();
		Kernel<<<dim3(64, 64), dim3(16, 16)>>>(renderTarget.GetDeviceMemory(), renderTarget.GetPitch(), dx, dy,
												world.GetSphereMemory(), world.GetSize(),
												world.GetGlobalsMemory());
		renderTarget.Unmap();

		cudaError_t error = cudaGetLastError();
		if (error != cudaSuccess) {
			COM::log << "running kernel failed: "
				<< cudaGetErrorString(error) << std::endl;
		}
	}

} // namespace RT2