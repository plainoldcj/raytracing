/*
solution:	raytracing
project:	app_test2
			app_test3
file:		window.cpp
author:		cj
*/

#include "../common/config.h"
#include "../system/print.h"
#include "../rtengine1/renderer.h"
#include "window.h"

Window::Window(int width, int height, int rwidth, int rheight)
	:	base_t(NULL, TEXT("Image Window"), width, height),
		_renderer(rwidth, rheight),
		_camera(width, height)
{
	COM::Config& config = COM::Config::Instance();
	int numSpheres = config.Get("numspheres", 10);
	int depth = config.Get("depth", 10);

	const float alpha = M::TWO_PI / numSpheres;
	const float dist = 0.8f;
	for(int i = 0; i < numSpheres; ++i) {
		M::Vector3 vec = dist * M::Vector3(cosf(alpha * i), sinf(alpha * i), -0.2f);
		_world.AddSphere(M::Sphere(vec, 0.2f), RT1::Color::Red);
	}

	for(int i = 0; i < numSpheres; ++i) {
		M::Vector3 vec = 1.2f * M::Vector3(cosf(alpha * i), sinf(alpha * i), -0.3f);
		_world.AddSphere(M::Sphere(vec, 0.1f), RT1::Color::Green);
	}

	_world.AddSphere(M::Sphere(M::Vector3(0.0f, 0.0f, 0.0f), 0.4f), RT1::Color::Blue);

	_renderer.SetLightPosition(M::Vector3(-2.0f, 2.0f, 5.0f));
	_renderer.SetLightAttenuation(1.0f, 0.05f, 0.001f);

	_world.UpdateSpheres();
	_renderer.SetWorld(_world);

	_renderer.SetDepth(depth);
}

void Window::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_renderer.Render();
	_renderer.RenderOverlay();

	glBindTexture(GL_TEXTURE_2D, 0);
	SYS::Relocate(10, Height() - 20);
	SYS::Print("Fps: %d", Fps());
}

void Window::Move(float secsPassed) {
	const int numSpheres = 10;
	const float alpha = M::TWO_PI / numSpheres;

	for(int i = 0; i < numSpheres; ++i) {
		float sin = M::Abs(sinf(Time() + i * alpha));
		_world.GetSphereGeometry(i).center.z = -0.2f + sin * 0.2f;
		_world.GetSphereGeometry(numSpheres + i).center.z = -0.3f + sin;
	}
	_world.UpdateSpheres();
}