/*
solution:	raytracing
project:	cmath
file:		matrix3.cuh
author:		cj
*/

#pragma once

#include "cmath_api.h"

namespace CM {

	struct Vector3;

	struct Matrix3 {
		union {
			struct {
				float m00, m10, m20;
				float m01, m11, m21;
				float m02, m12, m22;
			};
			struct {
				float a, d, g;
				float b, e, h;
				float c, f, i;
			};
			float mat[9];
		};

		CM_API Matrix3(void) { }
		
		CM_API Matrix3(float m00, float m01, float m02, 
						float m10, float m11, float m12,
						float m20, float m21, float m22)
						:	m00(m00), m01(m01), m02(m02),
							m10(m10), m11(m11), m12(m12),
							m20(m20), m21(m21), m22(m22) { }
	};

	CM_API Matrix3 operator*(const Matrix3& lhp, const Matrix3& rhp) {
		Matrix3 mat;
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) {
				float el = 0.0f;
				for(int k = 0; k < 3; ++k) {
					el += lhp.mat[i + 3 * k] * rhp.mat[k + 3 * j];
				}
				mat.mat[i + 3 * j] = el;
			}
		}
		return mat;
	}

	CM_API Matrix3 operator/(const Matrix3& mat, float scalar) {
		return Matrix3(mat.m00 / scalar, mat.m01 / scalar, mat.m02 / scalar, 
						mat.m10 / scalar, mat.m11 / scalar, mat.m12 / scalar,
						mat.m20 / scalar, mat.m21 / scalar, mat.m22 / scalar);
	}

	CM_API Vector3 Transform(const Matrix3& mat, const Vector3& vec) {
		Vector3 ret;
		for(int i = 0; i < 3; ++i) {
			float el = 0.0f;
			for(int j = 0; j < 3; ++j) {
				el += mat.mat[i + 3 * j] * vec.vec[j];
			}
			ret.vec[i] = el;
		}
		return ret;
	}

	CM_API float Det(const Matrix3& m) {
		return m.a * (m.e * m.i - m.f * m.h)
			- m.b * (m.d * m.i - m.f * m.g)
			+ m.c * (m.d * m.h - m.e * m.g);
	}

	CM_API Matrix3 Inverse(const Matrix3& m) {
		Matrix3 inv(m.e * m.i - m.f * m.h, m.c * m.h - m.b * m.i, m.b * m.f - m.c * m.e,
					m.f * m.g - m.d * m.i, m.a * m.i - m.c * m.g, m.c * m.d - m.a * m.f,
					m.d * m.h - m.e * m.g, m.b * m.g - m.a * m.h, m.a * m.e - m.b * m.d);
		return inv / Det(m);
	}

	CM_API Matrix3 RigidInverse(const Matrix3& m) {
		return Matrix3(m.m00, m.m10, m.m20,
					   m.m01, m.m11, m.m21,
					   m.m02, m.m12, m.m22);
	}

	CM_API void ToColumns(const Matrix3& mat, Vector3& A1, Vector3& A2, Vector3& A3) {
		A1.x = mat.m00;
		A1.y = mat.m10;
		A1.z = mat.m20;

		A2.x = mat.m01;
		A2.y = mat.m11;
		A2.z = mat.m21;

		A3.x = mat.m02;
		A3.y = mat.m12;
		A3.z = mat.m22;
	}

	namespace Mat3 {

		CM_API Matrix3 FromColumns(const Vector3& A1, const Vector3& A2, const Vector3& A3) {
			return Matrix3(A1.x, A2.x, A3.x,
						   A1.y, A2.y, A3.y,
						   A1.z, A2.z, A3.z);
		}

		CM_API Matrix3 Identity(void) {
			return Matrix3(1.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 1.0f);
		}

		CM_API Matrix3 RotateY(float angle) {
			const float rad = Deg2Rad(angle);
			const float sina = sinf(rad);
			const float cosa = cosf(rad);

			return Matrix3(cosa, 0.0f, -sina,
						   0.0f, 1.0f, 0.0f,
						   sina, 0.0f, cosa);
		}

		CM_API Matrix3 RotateAxis(const Vector3& axis, float angle) {
			const float rad = Deg2Rad(angle);
			const float sina = sinf(rad);
			const float cosa = cosf(rad);
			const float oneMinusCos = 1.0f - cosa;

			const float xyT = axis.x * axis.y * oneMinusCos;
			const float xzT = axis.x * axis.z * oneMinusCos;
			const float yzT = axis.y * axis.z * oneMinusCos;

			const float xT = axis.x * sina;
			const float yT = axis.y * sina;
			const float zT = axis.z * sina;

			return Matrix3(axis.x * axis.x * oneMinusCos + cosa, xyT - zT, xzT + yT,
						   xyT + zT, axis.y * axis.y * oneMinusCos + cosa, yzT - xT,
						   xzT - yT, yzT + xT, axis.z * axis.z * oneMinusCos + cosa);
		}

	} // namespace Mat3

} // namespace CM