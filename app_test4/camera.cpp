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

#include "../math/math.h"
#include "camera.h"

CM::Vector3 Camera::VectorFromMousePos(int mouseX, int mouseY) {
	float x = mouseX - _halfWidth;
	float y = -mouseY + _halfHeight;
	const float r2 = _radius * _radius;
	const float len2 = x * x + y * y;
	CM::Vector3 ret;
	if(len2 > r2) {
		ret = CM::Normalize(CM::Vector3(x, y, 0.0f));
	} else {
		const float z = sqrt(r2 - len2);
		ret = CM::Normalize(CM::Vector3(x, y, z));
	}
	return ret;
}

Camera::Camera(int width, int height)
	: _dragging(false),
	  _rotation(CM::Mat3::Identity()),
	  _dragRot(CM::Mat3::Identity())
{
	SetScreenSize(width, height);
}

void Camera::SetScreenSize(int width, int height) {
	_halfWidth = width / 2.0f;
	_halfHeight = height / 2.0f;
	_radius = M::Min(_halfWidth, _halfHeight);
}

void Camera::StartDragging(int mouseX, int mouseY) {
	if(!_dragging) {
		_v0 = VectorFromMousePos(mouseX, mouseY);
		_dragging = true;
	}
}

bool Camera::Drag(int mouseX, int mouseY) {
	if(_dragging) {
		const CM::Vector3 v1 = VectorFromMousePos(mouseX, mouseY);
		if(CM::LinearlyDependent(_v0, v1)) return _dragging;
		const CM::Vector3 axis = CM::Normalize(CM::Cross(_v0, v1));
		float angle = acosf(CM::Dot(_v0, v1));
		_dragRot = _dragRot * CM::Mat3::RotateAxis(axis, M::Rad2Deg(angle));
		_v0 = v1;
	}
	return _dragging;
}

void Camera::StopDragging(void) {
	_dragging = false;
	_rotation = _dragRot * _rotation;
	_dragRot = CM::Mat3::Identity();
}

CM::Matrix4 Camera::GetMatrix(void) const {
	if(_dragging) {
		return CM::Mat4::FromRigidTransform(_dragRot * _rotation, CM::Vector3(0.0f, 0.0f, 0.0f));
	} else {
		return CM::Mat4::FromRigidTransform(_rotation, CM::Vector3(0.0f, 0.0f, 0.0f));
	}
}