/*
solution:	raytracing
project:	rtengine0
file:		imagewindow.h
author:		cj
*/

#include "../common/common.h"
#include "../system/glx.h"
#include "../system/glwindow.h"
#include "raycaster.h"

namespace RT0 {

	class Framebuffer;

	class ImageWindow : public SYS::GLWindow, public FrameListener {
	private:
		const Framebuffer& _framebuffer;
		GLuint _texId;
	protected:
		void CloseEvent(void);
	public:
		typedef SYS::GLWindow base_t;

		ImageWindow(const Framebuffer& framebuffer, int width, int height);

		void UpdateSubFrame(int x, int y, int w, int h);

		void Render(void);
		void Move(float secsPassed) { }
	};

} // namespace RT0