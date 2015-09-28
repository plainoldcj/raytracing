/*
solution:	raytracing
project:	app_test4
file:		window.h
author:		cj
*/

#include "../system/print.h"
#include "window.h"

Window::Window(int width, int height, int rwidth, int rheight)
	:	base_t(NULL, TEXT("Image Window"), width, height),
		_renderer(rwidth, rheight),
		_world(),
		_camera(width, height)
{
	RT2::Sphere sphere;

	sphere.refIndex = 0.52;

	sphere.reflectivity = 0.3f;
	sphere.refractivity = 0.0f;
	sphere.transparency = 0.0f;

	sphere.color = CM_COLOR(1.0f, 0.0f, 0.0f);
	sphere.geometry = CM::Sphere(CM::Vector3(-1.0f, 1.0f, 0.0f), 0.5f);
	_world.AddSphere(sphere);

	sphere.color = CM_COLOR(0.1f, 0.0f, 1.0f);
	sphere.geometry = CM::Sphere(CM::Vector3(0.0f, 0.0f, 0.0f), 0.5f);
	_world.AddSphere(sphere);

	sphere.reflectivity = 0.2f;
	sphere.refractivity = 0.8f;
	sphere.transparency = 0.4f;

	sphere.color = CM::Color(0.1f, 0.1f, 0.1f);
	sphere.geometry = CM::Sphere(CM::Vector3(1.0f, -1.0f, 0.0f), 0.5f);
	_world.AddSphere(sphere);

	_world.SetLightPosition(CM::Vector3(10.0f, 0.0f, 10.0f));
	_world.SetWorldMatrix(CM::Mat4::Identity());
}

void Window::Render(void) {
	_renderer.Render(_world);

	glBindTexture(GL_TEXTURE_2D, 0);
	SYS::Relocate(10, Height() - 20);
	SYS::Print("Fps: %d", Fps());
}