/*
solution:	raytracing
project:	rtengine0
file:		color.h
author:		cj
*/

#pragma once

namespace RT0 {

	struct Color {
		float r, g, b, a;

		Color(void) { }
		Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) { }

		Color& operator=(const Color& other) {
			if(this == &other) return *this;
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
			return *this;
		}

		Color& operator+=(const Color& other) {
			r += other.r;
			g += other.g;
			b += other.b;
			a += other.a;
			return *this;
		}

		static Color FromBytes(unsigned char r, 
			unsigned char g, unsigned char b) 
		{
			const float f = 1.0f / 255.0f;
			return Color(f * r, f * g, f * b);
		}

		static Color Black;
		static Color White;
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color CornflowerBlue; // very attractive background color :)
	};

	inline Color operator+(const Color& lhp, const Color& rhp) {
		return Color(lhp.r + rhp.r, lhp.g + rhp.g, lhp.b + rhp.b, lhp.a + rhp.a);
	}

	inline Color operator*(const Color& lhp, const Color& rhp) {
		return Color(lhp.r * rhp.r, lhp.g * rhp.g, lhp.b * rhp.b, lhp.a * rhp.a);
	}

	inline Color operator*(float f, const Color& color) {
		return Color(f * color.r, f * color.g, f * color.b, f * color.a);
	}

	inline Color operator*(const Color& color, float f) {
		return Color(f * color.r, f * color.g, f * color.b, f * color.a);
	}

	// f * lhp + (1.0f - f) * rhp
	Color Blend(float blend, const Color& src, const Color& dst);

} // namespace RT0