/*
solution:	raytracing
project:	rtengine2
file:		world.h
author:		cj
*/

#pragma once

#include "../cmath/color.cuh"
#include "../cmath/sphere.cuh"
#include "../cmath/matrix4.cuh"

namespace RT2 {

	struct Sphere {
		CM::Sphere geometry;
		CM::Color color;
		float refIndex;
		float reflectivity;
		float refractivity;
		float transparency;
	};

	struct Globals {
		CM::Vector3 lightPos;
		CM::Matrix4 invWorld;
		CM::Vector3 eyePos; // set in kernel
	};

	class World {
	private:
		enum { GRANULATION = 25 };

		Sphere* _devSpheres;
		unsigned _size;
		unsigned _capacity;

		void Resize(unsigned size);

		Globals _globals;
		Globals* _devGlobals;
	public:
		World(void);
		~World(void);

		Sphere* GetSphereMemory(void) const { return _devSpheres; }
		unsigned GetSize(void) const { return _size; }
		Globals* GetGlobalsMemory(void) const { return _devGlobals; }

		void AddSphere(const Sphere& sphere);

		void SetLightPosition(const CM::Vector3& position);
		void SetWorldMatrix(const CM::Matrix4& world);
	};

} // namespace RT2