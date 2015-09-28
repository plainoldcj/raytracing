/*
solution:	raytracing
project:	cmath
file:		cmath.h
author:		cj
*/

#pragma once

#include "cmath_api.h"

namespace CM {

	const float PI		= 3.14159265f;
	const float TWO_PI	= 6.28318531f;

	template<typename TYPE>
	CM_API TYPE Abs(TYPE value) {
		return value < 0 ? -value : value;
	}

	template<>
	CM_API float Abs<float>(float value) {
		return value < 0.0f ? -value : value;
	}

	template<typename TYPE>
	CM_API TYPE Min(TYPE lhp, TYPE rhp) {
		return lhp < rhp ? lhp : rhp;
	}

	template<typename TYPE>
	CM_API TYPE Max(TYPE lhp, TYPE rhp) {
		return lhp > rhp ? lhp : rhp;
	}

	template<typename TYPE>
	CM_API TYPE Clamp(TYPE val, TYPE min, TYPE max) {
		return Min(Max(min, val), max);
	}

	CM_API float Deg2Rad(float deg) {
		const float factor = PI / 180.0f;
		return deg * factor;
	}

	CM_API float Rad2Deg(float rad) {
		const float factor = 180.0f / PI;
		return rad * factor;
	}

	CM_API bool AlmostEqual(float lhp, float rhp) {
		const float epsilon = 0.00001f;
		return Abs(lhp - rhp) < epsilon;
	}

} // namespace CM