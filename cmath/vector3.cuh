/*
solution:	raytracing
project:	cmath
file:		vector3.cu
author:		cj
*/

#pragma once

#include <math.h>
#include "cmath.cuh"
#include "cmath_api.h"

#define CM_VEC3(x, y, z) (Vector3(x, y, z))

namespace CM {

	struct Vector3 {
		union {
			struct {
				float x, y, z;
			};
			float vec[3];
		};

		CM_API Vector3(void) { }
		
		CM_API Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) { }

		CM_API Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

		CM_API Vector3& operator=(const Vector3& other) {
			if(&other == this) return *this;
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		CM_API Vector3 operator-(void) const {
			return Vector3(-x, -y, -z);
		}

		CM_API Vector3& operator+=(const Vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		CM_API Vector3& operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}
		
		CM_API Vector3& operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		CM_API float Length(void) const {
			return sqrt(x * x + y * y + z * z);
		}

		CM_API void Normalize(void) {
			const float len = Length();
			x /= len;
			y /= len;
			z /= len;
		}
	};

	CM_API Vector3 operator+(const Vector3& lhp, const Vector3& rhp) {
		return Vector3(lhp.x + rhp.x, lhp.y + rhp.y, lhp.z + rhp.z);
	}

	CM_API Vector3 operator-(const Vector3& lhp, const Vector3& rhp) {
		return Vector3(lhp.x - rhp.x, lhp.y - rhp.y, lhp.z - rhp.z);
	}

	CM_API Vector3 operator*(float scalar, const Vector3& vector) {
		return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
	}

	CM_API Vector3 operator*(const Vector3& vector, float scalar) {
		return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
	}

	CM_API Vector3 operator/(const Vector3& vector, float scalar) {
		return Vector3(vector.x / scalar, vector.y / scalar, vector.z / scalar);
	}

	CM_API Vector3 Negate(const Vector3& vec) {
		return Vector3(-vec.x, -vec.y, -vec.z);
	}

	CM_API float Dot(const Vector3& lhp, const Vector3& rhp) {
		return lhp.x * rhp.x + lhp.y * rhp.y + lhp.z * rhp.z;
	}

	CM_API Vector3 Cross(const Vector3& lhp, const Vector3& rhp) {
		return Vector3(lhp.y * rhp.z - lhp.z * rhp.y,
					   lhp.z * rhp.x - lhp.x * rhp.z,
					   lhp.x * rhp.y - lhp.y * rhp.x);
	}

	CM_API Vector3 Normalize(const Vector3& vector) {
		float length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		return vector / length;
	}

	CM_API float Length(const Vector3& vector) {
		return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	CM_API float Distance(const Vector3& lhp, const Vector3& rhp) {
		return Length(rhp - lhp);
	}

	CM_API bool LinearlyDependent(const Vector3& u, const Vector3& v) {
		return AlmostEqual(u.x * v.y - u.y * v.x, 0.0f) &&
			   AlmostEqual(u.x * v.z - u.z * v.x, 0.0f);
	}

	CM_API Vector3 ReflectNormalized(const Vector3& incident, const Vector3& normal) {
		return incident - 2.0f * Dot(normal, incident) * normal;
	}

	CM_API Vector3 RefractNormalized(const Vector3& incident, const Vector3& normal, 
									float Si, float St) // indices of refraction, i = incident, t = transmission
	{
		float Ci = Dot(normal, -incident);
		float nit = St / Si;
		return nit * incident + (nit * Ci - sqrtf(1 + nit * nit * (Ci * Ci - 1.0f))) * normal;
	}

} // namespace CM