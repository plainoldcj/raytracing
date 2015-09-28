/*
solution:	raytracing
project:	rtengine0
file:		entity.h
author:		cj
*/

#pragma once

#include "../math/vector3.h"
#include "../math/intersections.h"
#include "skin.h"

namespace M {
	struct Ray;
}

namespace RT0 {

	class Entity {
	private:
		M::Vector3 _position;
		Skin _skin;
	public:
		struct IntersectionInfo {
			M::IS::Info minfo;
		};

		virtual ~Entity(void) { }

		Skin& GetSkin(void) { return _skin; }
		const Skin& GetSkin(void) const { return _skin; }

		const M::Vector3& GetPosition(void) const { return _position; }
		void SetPosition(const M::Vector3& position) { _position = position; }

		virtual bool Intersects(const M::Ray& ray, IntersectionInfo* info = NULL) const = 0;
	};

} // namespace RT0