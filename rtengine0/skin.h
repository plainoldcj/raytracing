/*
solution:	raytracing
project:	rtengine0
file:		skin.h
author:		cj
*/

#include "color.h"

namespace RT0 {

	class Skin {
	private:
		Color _diffuseColor;
		Color _specularColor;
		float _shininess;
		float _reflectivity;
	public:
		Skin(void) {
			_diffuseColor = Color::White;
			_specularColor = Color::White;
			_shininess = 10.0f;
			_reflectivity = 0.0f;
		}

		void SetDiffuseColor(const Color& color) { _diffuseColor = color; }
		const Color& GetDiffuseColor(void) const { return _diffuseColor; }

		void SetSpecularColor(const Color& color) { _specularColor = color; }
		const Color& GetSpecularColor(void) const { return _specularColor; }

		void SetShininess(float value) { _shininess = value; }
		float GetShininess(void) const { return _shininess; }

		void SetReflectivity(float value) { _reflectivity = value; }
		float GetReflectivity(void) const { return _reflectivity; }
	};

} // namespace RT0