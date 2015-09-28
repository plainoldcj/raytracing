/*
solution:	raytracing
project:	rtengine2
file:		world.h
author:		cj
*/

#include "cuda.h"
#include "world.h"

namespace RT2 {

	void World::Resize(unsigned size) {
		if(_capacity >= size) {
			_size = size;
			return;
		}

		unsigned capacity = size + size % GRANULATION;
		Sphere* mem = NULL;
		CUDA_CALL(cudaMalloc((void**)&mem, sizeof(Sphere) * size));

		CUDA_CALL(cudaMemcpy(&mem[1], _devSpheres, sizeof(Sphere) * _size, cudaMemcpyDeviceToDevice));
		
		std::swap(_devSpheres, mem);
		_size = size;
		_capacity = capacity;

		cudaFree(mem);
	}

	World::World(void) 
		:	_devSpheres(NULL), _size(0), _capacity(0),
			_devGlobals(NULL)
	{
		Globals* mem = NULL;
		CUDA_CALL(cudaMalloc((void**)&mem, sizeof(Globals)));
		_devGlobals = mem;

		CUDA_CALL(cudaMalloc((void**)&_devSpheres, sizeof(Sphere) * 100));
	}

	World::~World(void) {
		if(_devSpheres) cudaFree(_devSpheres);
		if(_devGlobals) cudaFree(_devGlobals);
	}

	void World::AddSphere(const Sphere& sphere) {
		unsigned at = _size;
		// Resize(_size + 1);
		CUDA_CALL(cudaMemcpy(&_devSpheres[at], &sphere, sizeof(Sphere), cudaMemcpyHostToDevice));
		_size++;
	}

	void World::SetLightPosition(const CM::Vector3& lightPos) {
		_globals.lightPos = lightPos;
		CUDA_CALL(cudaMemcpy(_devGlobals, &_globals, sizeof(Globals), cudaMemcpyHostToDevice));
	}

	void World::SetWorldMatrix(const CM::Matrix4& world) {
		_globals.invWorld = CM::RigidInverse(world);
		CUDA_CALL(cudaMemcpy(_devGlobals, &_globals, sizeof(Globals), cudaMemcpyHostToDevice));
	}

} // namespace RT2