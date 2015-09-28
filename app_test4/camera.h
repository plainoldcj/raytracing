/*
solution:	glib
			raytracing
project:	cubemapping
			app_test1
			app_test2
			app_test3
			app_test4
file:		camera.cpp
author:		cj
*/

#pragma once

#include "../cmath/vector3.cuh"
#include "../cmath/matrix3.cuh"
#include "../cmath/matrix4.cuh"

class Camera {
private:
	float _halfWidth;
	float _halfHeight;
	float _radius;

	bool _dragging;
	CM::Vector3 _v0;
	CM::Matrix3 _dragRot;
	CM::Matrix3 _rotation;

	CM::Vector3 VectorFromMousePos(int mouseX, int mouseY);
public:
	Camera(int width, int height);

	void SetScreenSize(int width, int height);

	void StartDragging(int mouseX, int mouseY);
	bool Drag(int mouseX, int mouseY);
	void StopDragging(void);

	CM::Matrix4 GetMatrix(void) const;
};