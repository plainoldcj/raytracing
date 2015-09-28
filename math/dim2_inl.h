/*
solution:	raytracing
project:	math
file:		dim2_inl.h
author:		cj
*/

#pragma once

#include "math.h"
#include "dim2.h"

namespace M {

	template<typename TYPE>
	M_INLINE Dim2<TYPE>::Dim2(TYPE width, TYPE height)
		: width(width), height(height) { }

} // namespace M