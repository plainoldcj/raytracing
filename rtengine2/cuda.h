/*
solution:	raytracing
project:	rtengine2
file:		cuda.h
author:		cj
*/

#pragma once

#pragma comment(lib, "cudart.lib")

#include <Windows.h>

#include <cuda.h>
#include <builtin_types.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
#include <device_launch_parameters.h>

#include "../common/common.h"

#define CUDA_CALL(x) \
	do { \
		cudaError_t error = x; \
		if(cudaSuccess != error) { \
			COM::log << "cuda function " << #x << " failed with error code " \
				<< error << ", " << cudaGetErrorString(error) << std::endl; \
			throw std::exception(); \
		} \
	} while(false)