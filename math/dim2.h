/*
solution:	raytracing
project:	math
file:		dim2.h
author:		cj
*/

#pragma once

namespace M {

	template<typename TYPE>
	struct Dim2 {
		TYPE width, height;

		Dim2(TYPE width, TYPE height);
	};

	typedef Dim2<int> dim2i_t;

} // namespace M

#include "dim2_inl.h"