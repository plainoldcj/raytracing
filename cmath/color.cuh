/*
solution:	raytracing
project:	cmath
file:		color.cuh
author:		cj
*/

#pragma once

#include "cmath_api.h"
#include "cmath.cuh"

#define CM_COLOR(r, g, b) (CM::Color(r, g, b))

namespace CM {

	struct Color {
		float r, g, b, a;

		CM_API Color(void) { }
		CM_API Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) { }

		CM_API Color& operator=(const Color& other) {
			if(this == &other) return *this;
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
			return *this;
		}

		CM_API Color& operator+=(const Color& other) {
			r += other.r;
			g += other.g;
			b += other.b;
			a += other.a;
			return *this;
		}

		static CM_API Color FromBytes(unsigned char r, 
			unsigned char g, unsigned char b) 
		{
			const float f = 1.0f / 255.0f;
			return Color(f * r, f * g, f * b);
		}
	};

	CM_API Color operator+(const Color& lhp, const Color& rhp) {
		return Color(lhp.r + rhp.r, lhp.g + rhp.g, lhp.b + rhp.b, lhp.a + rhp.a);
	}

	CM_API Color operator*(const Color& lhp, const Color& rhp) {
		return Color(lhp.r * rhp.r, lhp.g * rhp.g, lhp.b * rhp.b, lhp.a * rhp.a);
	}

	CM_API Color operator*(float f, const Color& color) {
		return Color(f * color.r, f * color.g, f * color.b, f * color.a);
	}

	CM_API Color operator*(const Color& color, float f) {
		return Color(f * color.r, f * color.g, f * color.b, f * color.a);
	}

	// f * lhp + (1.0f - f) * rhp
	CM_API Color Blend(float blend, const Color& lhp, const Color& rhp) {
		float f = Clamp(blend, 0.0f, 1.0f);
		return f * lhp + (1.0f - f) * rhp;
	}

} // namespace CM