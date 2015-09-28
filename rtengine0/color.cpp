/*
solution:	raytracing
project:	rtengine0
file:		color.cpp
author:		cj
*/

#include "../math/math.h"
#include "color.h"

namespace RT0 {

	Color Color::Black			= Color(0.0f, 0.0f, 0.0f);
	Color Color::White			= Color(1.0f, 1.0f, 1.0f);
	Color Color::Red			= Color(1.0f, 0.0f, 0.0f);
	Color Color::Green			= Color(0.0f, 1.0f, 0.0f);
	Color Color::Blue			= Color(0.0f, 0.0f, 1.0f);
	Color Color::CornflowerBlue = Color(0.39215f, 0.58431f, 0.92941f);

	Color Blend(float blend, const Color& lhp, const Color& rhp) {
		float f = M::Clamp(blend, 0.0f, 1.0f);
		return f * lhp + (1.0f - f) * rhp;
	}

} // namespace RT0