/*
solution:	raytracing
project:	app_test1
file:		window.cpp
author:		cj
*/

#include "../common/config.h"
#include "../system/glx.h"
#include "../rtengine0/renderer.h"
#include "../rtengine0/sh_default.h"
#include "../rtengine0/ill_pointlight.h"
#include "sphere.h"
#include "window.h"

void SetWireframe(bool on) {
	if(on) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Overlay::Overlay(int width, int height) : _framebuffer(width, height) {
	glGenTextures(1, &_texId);
	glBindTexture(GL_TEXTURE_2D, _texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _framebuffer.GetWidth(), _framebuffer.GetHeight(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, _framebuffer.GetPixels());

	// you have to set these filters for texturing to work ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Overlay::Update(void) {
	glBindTexture(GL_TEXTURE_2D, _texId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _framebuffer.GetWidth(), _framebuffer.GetHeight(),
		GL_RGBA, GL_UNSIGNED_BYTE, _framebuffer.GetPixels());
}

void Overlay::Render(void) {
	glBindTexture(GL_TEXTURE_2D, _texId);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	SetWireframe(false);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
	glEnd();
	glPopAttrib();
	glPopMatrix();
}

void Overlay::Clear(void) {
	_framebuffer.Clear();
	Update();
}

// !!! hardcoded screen size
Window::Window(int width, int height) 
	:	base_t(NULL, TEXT("Image Window"), 800, 800, SYS::WS_NONRESIZABLE),
		_lowRes(100, 100),
		_highRes(width, height),
		_camera(800, 800),
		_showLowRes(false),
		_showHighRes(false)
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -100.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	COM::Config& config = COM::Config::Instance();
	float reflectivity = config.Get("reflectivity", 0.3f);

	// shaping the world with bare hands...
	GEN::Pointer<Sphere> sphere0(new Sphere(0.4f));
	sphere0->SetPosition(M::Vector3(-0.6f, 0.0f, 0.0f));
	sphere0->GetSkin().SetDiffuseColor(RT0::Color(1.0f, 0.0f, 0.0f));
	sphere0->GetSkin().SetReflectivity(reflectivity);
	_rtWorld.AddEntity(sphere0);
	_glWorld.AddEntity(sphere0);

	GEN::Pointer<Sphere> sphere1(new Sphere(0.4f));
	sphere1->SetPosition(M::Vector3(0.6f, 0.0f, 0.0f));
	sphere1->GetSkin().SetDiffuseColor(RT0::Color(1.0f, 0.5f, 0.5f));
	sphere1->GetSkin().SetReflectivity(reflectivity);
	_rtWorld.AddEntity(sphere1);
	_glWorld.AddEntity(sphere1);

	GEN::Pointer<Sphere> sphere2(new Sphere(0.4f));
	sphere2->SetPosition(M::Vector3(0.0f, 0.6f, 0.0f));
	sphere2->GetSkin().SetDiffuseColor(RT0::Color(0.0f, 0.0f, 1.0f));
	sphere2->GetSkin().SetReflectivity(reflectivity);
	_rtWorld.AddEntity(sphere2);
	_glWorld.AddEntity(sphere2);

	GEN::Pointer<Sphere> sphere3(new Sphere(0.4f));
	sphere3->SetPosition(M::Vector3(0.0f, -0.6f, 0.0f));
	sphere3->GetSkin().SetDiffuseColor(RT0::Color::FromBytes(57, 183, 255));
	sphere3->GetSkin().SetReflectivity(reflectivity);
	_rtWorld.AddEntity(sphere3);
	_glWorld.AddEntity(sphere3);

	RT0::lightPtr_t light(new RT0::ILL::Pointlight());
	light->SetPosition(M::Vector3(-2.0f, 2.0f, 10.0f));
	_rtWorld.AddLight(light);
}

void Window::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	M::Matrix4 world = _camera.GetMatrix();
	glLoadMatrixf(world.mat);

	glBindTexture(GL_TEXTURE_2D, 0);
	SetWireframe(true);
	_glWorld.Render();

	if(_showLowRes) _lowRes.Render();
	if(_showHighRes) _highRes.Render();

	if(IsRendering()) {
		if(_showLowRes) _lowRes.Update();
		if(_showHighRes) _highRes.Update();
	}
}

void Window::Move(float secsPassed) {
	const unsigned rKey = 0x52;
	const unsigned tKey = 0x54;

	if(HIWORD(GetAsyncKeyState(rKey)) && !_showLowRes) {
		M::Matrix4 world = _camera.GetMatrix();
		RT0::Renderer::Instance().Render(_lowRes.GetFramebuffer(), _rtWorld,
			RT0::AllocShader<RT0::SH::Default>, world, this);
		_showLowRes = true;
		_showHighRes = false;
	}

	if(HIWORD(GetAsyncKeyState(tKey)) && !_showHighRes) {
		M::Matrix4 world = _camera.GetMatrix();
		RT0::Renderer::Instance().Render(_highRes.GetFramebuffer(), _rtWorld,
			RT0::AllocShader<RT0::SH::Default>, world, this);
		_showLowRes = false;
		_showHighRes = true;
	}
}