/*
solution:	raytracing
project:	app_test4
file:		window.h
author:		cj
*/

#pragma once

#include "../system/glwindow.h"
#include "../rtengine2/world.h"
#include "../rtengine2/renderer.h"
#include "camera.h"

class Window : public SYS::GLWindow {
private:

	// order matters here since the renderer must set
	// the cuda device before the world allocated memory
	// on it ...
	RT2::Renderer _renderer;
	RT2::World _world;
	Camera _camera;
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
		}
		if(SYS::MouseEvent::TYPE_BUTTON_UP == event.type) {
			if(SYS::MouseEvent::BUTTON_LEFT == event.reason) {
				_camera.StopDragging();
			}
		}
		if(SYS::MouseEvent::TYPE_MOVE == event.type) {
			if(_camera.Drag(event.x, event.y)) {
				_world.SetWorldMatrix(_camera.GetMatrix());
			}
		}
	}
public:
	typedef SYS::GLWindow base_t;

	Window(int width, int height, int rwidth, int rheight);

	void Render(void);
	void Move(float secsPassed) { }
};