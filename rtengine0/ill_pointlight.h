/*
solution:	raytracing
project:	rtengine0
file:		ill_pointlight.h
author:		cj
*/

#pragma once

#include "light.h"

namespace RT0 {
namespace ILL {

	class Pointlight : public Light {
	public:
		float Illuminate(const World& world, const M::Vector3& point) const;
	};

} // namespace ILL
} // namespace RT0