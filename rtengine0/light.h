/*
solution:	raytracing
project:	rtengine0
file:		light.h
author:		cj
*/

#pragma once

#include "../math/vector3.h"

namespace RT0 {

	class World;

	class Light {
	private:
		M::Vector3 _position;
	public:
		virtual ~Light(void) { }

		void SetPosition(const M::Vector3& position) { _position = position; }
		const M::Vector3& GetPosition(void) const { return _position; } 

		virtual float Illuminate(const World& world, const M::Vector3& point) const = 0;
	};

} // namespace RT0