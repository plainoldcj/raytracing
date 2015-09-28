/*
solution:	raytracing
project:	app_test1
file:		window.h
author:		cj
*/

#pragma once

#include "../system/glwindow.h"
#include "../rtengine0/framebuffer.h"
#include "../rtengine0/world.h"
#include "../rtengine0/raycaster.h"
#include "world.h"
#include "camera.h"

namespace RT0 {
	class Framebuffer;
}

class Overlay {
private:
	GLuint _texId;
	RT0::Framebuffer _framebuffer;
public:
	Overlay(int width, int height);

	void Update(void);
	void Render(void);
	void Clear(void);

	RT0::Framebuffer& GetFramebuffer(void) {
		return _framebuffer;
	}
};

class Window : public SYS::GLWindow, public RT0::FrameListener {
private:
	Camera _camera;
	Overlay _lowRes;
	Overlay _highRes;
	bool _showLowRes;
	bool _showHighRes;
	RT0::World _rtWorld;
	World _glWorld;
protected:
	void ResizeEvent(unsigned width, unsigned height) {
		base_t::ResizeEvent(width, height);
		_camera.SetScreenSize(width, height);
	}

	void MouseEvent(const SYS::MouseEvent& event) {
		if(SYS::MouseEvent::TYPE_BUTTON_DOWN == event.type) {
			if(SYS::MouseEvent::BUTTON_LEFT == event.reason) {
				_camera.StartDragging(event.x, event.y);
			}

			if(_showLowRes) {
				_lowRes.Clear();
				_showLowRes = false;
			}
			if(_showHighRes) {
				_highRes.Clear();
				_showHighRes = false;
			}
		}
		if(SYS::MouseEvent::TYPE_BUTTON_UP == event.type) {
			if(SYS::MouseEvent::BUTTON_LEFT == event.reason) {
				_camera.StopDragging();
			}
		}
		if(SYS::MouseEvent::TYPE_MOVE == event.type) {
			_camera.Drag(event.x, event.y);
		}
	}
public:
	typedef SYS::GLWindow base_t;

	Window(int width, int height);

	void Render(void);
	void Move(float secsPassed);
};