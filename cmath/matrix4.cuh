/*
solution:	raytracing
project:	cmath
file:		matrix4.cuh
author:		cj
*/

#pragma once

#include "cmath_api.h"
#include "vector3.cuh"
#include "matrix3.cuh"

namespace CM {

	struct Matrix4 {
		union {
			struct {
				float m00, m10, m20, m30;
				float m01, m11, m21, m31;
				float m02, m12, m22, m32;
				float m03, m13, m23, m33;
			};
			float mat[16];
		};

		CM_API Matrix4(void) { }
		
		CM_API Matrix4(float m00, float m01, float m02, float m03, 
						float m10, float m11, float m12, float m13,
						float m20, float m21, float m22, float m23,
						float m30, float m31, float m32, float m33)
						:	m00(m00), m01(m01), m02(m02), m03(m03),
							m10(m10), m11(m11), m12(m12), m13(m13),
							m20(m20), m21(m21), m22(m22), m23(m23),
							m30(m30), m31(m31), m32(m32), m33(m33) { }
		
		CM_API Matrix4(const Matrix4& other)
			:	m00(other.m00), m01(other.m01), m02(other.m02), m03(other.m03), 
				m10(other.m10), m11(other.m11), m12(other.m12), m13(other.m13),
				m20(other.m20), m21(other.m21), m22(other.m22), m23(other.m23),
				m30(other.m30), m31(other.m31), m32(other.m32), m33(other.m33) { }

		CM_API Matrix4& operator=(const Matrix4& other) {
			if(&other == this) return *this;
			for(unsigned i = 0; i < 16; ++i)
				mat[i] = other.mat[i];
			return *this;
		}
	};

	CM_API Matrix4 operator*(const Matrix4& lhp, const Matrix4& rhp) {
		Matrix4 mat;
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) {
				float el = 0.0f;
				for(int k = 0; k < 4; ++k) {
					el += lhp.mat[i + 4 * k] * rhp.mat[k + 4 * j];
				}
				mat.mat[i + 4 * j] = el;
			}
		}
		return mat;
	}

	CM_API Vector3 Transform(const Matrix4& mat, const Vector3& vec) {
		Vector3 ret;
		for(int i = 0; i < 3; ++i) {
			float el = 0.0f;
			for(int j = 0; j < 3; ++j) {
				el += mat.mat[i + 4 * j] * vec.vec[j];
			}
			ret.vec[i] = el + mat.mat[i + 12];
		}
		return ret;
	}

	namespace Mat4 {

		CM_API Matrix4 Identity(void) {
			return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		CM_API Matrix4 FromRigidTransform(const Matrix3& rot, const Vector3& tran) {
			return Matrix4(rot.m00, rot.m01, rot.m02, tran.x,
							rot.m10, rot.m11, rot.m12, tran.y,
							rot.m20, rot.m21, rot.m22, tran.z,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		CM_API Matrix4 Translate(float x, float y, float z) {
			return Matrix4(1.0f, 0.0f, 0.0f, x,
						   0.0f, 1.0f, 0.0f, y,
						   0.0f, 0.0f, 1.0f, z,
						   0.0f, 0.0f, 0.0f, 1.0f);
		}

	} // namespace Mat4

	CM_API Matrix4 RigidInverse(const Matrix4& mat) {
		Matrix4 irot = Matrix4(mat.m00, mat.m10, mat.m20, 0.0f,
								mat.m01, mat.m11, mat.m21, 0.0f,
								mat.m02, mat.m12, mat.m22, 0.0f,
								0.0f, 0.0f, 0.0f, 1.0f);
		Matrix4 itrans = Mat4::Translate(-mat.m03, -mat.m13, -mat.m23);
		return irot * itrans;
	}

} // namespace CM