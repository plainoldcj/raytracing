/*
solution:	raytracing
project:	anim_test
file:		window.h
author:		cj
*/

#include "../system/glwindow.h"

class Window : public SYS::GLWindow {
public:
	typedef SYS::GLWindow base_t;

	Window(int width, int height);
	~Window(void) { }

	void Render(void);
	void Move(float secsPassed);
};