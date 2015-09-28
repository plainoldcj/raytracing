/*
solution:	raytracing
project:	rtengine0
file:		shader.h
author:		cj
*/

#pragma once

#include "color.h"
#include "world.h"

namespace RT0 {

	class Shader {
	public:
		virtual ~Shader(void) { }

		virtual Color Miss(void) const { return Color::Black; }
		virtual Color Hit(int depth, const World& world, const World::IntersectionInfo& info) { return Color::Black; }
		virtual void ShadowUnblocked(lightPtr_t light) { }
		virtual void ShadowBlocked(void) const { }
	};

} // namespace RT0