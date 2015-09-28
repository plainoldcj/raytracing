/*
solution:	raytracing
project:	rtengine0
file:		sh_default.h
author:		cj
*/

#pragma once

#include "../math/vector3.h"
#include "shader.h"

namespace RT0 {
namespace SH {

	class Default : public Shader {
	private:
		M::Vector3 _eye;

		struct ShadowData {
			Color frag;
			M::Vector3 where;
			M::Vector3 normal;
			Skin* skin;
		} _shadowData;
	public:
		Color Miss(void) const;
		Color Hit(int depth, const World& world, const World::IntersectionInfo& info);
		void ShadowUnblocked(lightPtr_t light);
	};

} // namespace SH
} // namespace RT0