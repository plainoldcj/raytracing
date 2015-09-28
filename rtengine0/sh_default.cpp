/*
solution:	raytracing
project:	rtengine0
file:		sh_default.cpp
author:		cj
*/

#include "sh_default.h"
#include "../common/common.h"

namespace RT0 {
namespace SH {

	Color Default::Miss(void) const {
		return Color::CornflowerBlue;
	}

	Color Default::Hit(int depth, const World& world, const World::IntersectionInfo& info) {
		if(0 >= depth) return Miss();

		entPtr_t entity = info.entity;
		Skin& skin = entity->GetSkin();

		if(info.primary) _eye = info.ray.origin;

		M::Vector3 where = info.einfo.minfo.where;

		_shadowData.frag = Color::Black;
		_shadowData.where = where;
		_shadowData.normal = info.einfo.minfo.normal;
		_shadowData.skin = &entity->GetSkin();
		world.CastShadowRays(*this, where);
		Color frag = _shadowData.frag;

		Color ref = skin.GetReflectivity() * world.CastReflectionRay(depth - 1, *this, where, info.ray.direction, info.einfo.minfo.normal);

		return frag + ref;
	}

	void Default::ShadowUnblocked(lightPtr_t light) {
		M::Vector3 dir = M::Normalize(light->GetPosition() - _shadowData.where);
		float d = M::Clamp(M::Dot(dir, _shadowData.normal), 0.0f, 1.0f);
		
		_shadowData.frag += _shadowData.skin->GetDiffuseColor() * d;
		
		if(0.0f < d) {
			M::Vector3 s = M::Normalize(dir + _eye - _shadowData.where);
			d = M::Max(M::Dot(s, _shadowData.normal), 0.0f);
			_shadowData.frag += powf(d, _shadowData.skin->GetShininess()) * _shadowData.skin->GetSpecularColor();
		}
	}

} // namespace SH
} // namespace RT0