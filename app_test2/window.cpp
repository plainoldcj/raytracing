/*
solution:	raytracing
project:	app_test2
file:		window.cpp
author:		cj
*/

#include "../rtengine1/renderer.h"
#include "window.h"

Window::Window(int width, int height, int rwidth, int rheight)
	:	base_t(NULL, TEXT("Image Window"), width, height),
		_renderer(rwidth, rheight),
		_camera(width, height)
{
	M::Sphere sphere0(M::Vector3(-0.6f,  0.0f,  0.0f), 0.4f);
	M::Sphere sphere1(M::Vector3( 0.6f,  0.0f,  0.0f), 0.4f);
	M::Sphere sphere2(M::Vector3( 0.0f,  0.6f,  0.0f), 0.4f);
	M::Sphere sphere3(M::Vector3( 0.0f, -0.6f,  0.0f), 0.4f);

	_world.AddSphere(sphere0, RT1::Color(1.0f, 0.0f, 0.0f));
	_world.AddSphere(sphere1, RT1::Color(1.0f, 0.5f, 0.5f));
	_world.AddSphere(sphere2, RT1::Color(0.0f, 0.0f, 1.0f));
	_world.AddSphere(sphere3, RT1::Color::FromBytes(57, 183, 255));

	_renderer.SetLightPosition(M::Vector3(-2.0f, 2.0f, 10.0f));

	_world.UpdateSpheres();
	_renderer.SetWorld(_world);
}

void Window::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_renderer.Render();
	_renderer.RenderOverlay();
}

void Window::Move(float secsPassed) {
}