/*
solution:	raytracing
project:	rtengine0
file:		raycaster.cpp
author:		cj
*/

#include "../common/common.h"
#include "../common/config.h"
#include "color.h"
#include "framebuffer.h"
#include "world.h"
#include "shader.h"
#include "renderer.h"
#include "raycaster.h"

namespace RT0 {

	//M::Matrix4 RigidInverse(const M::Matrix4& mat) {
	//	M::Matrix4 irot = M::Matrix4(mat.m00, mat.m10, mat.m20, 0.0f,
	//							mat.m01, mat.m11, mat.m21, 0.0f,
	//							mat.m02, mat.m12, mat.m22, 0.0f,
	//							0.0f, 0.0f, 0.0f, 1.0f);
	//	M::Matrix4 itrans = M::Mat4::Translate(-mat.m03, -mat.m13, -mat.m23);
	//	return irot; // * itrans;
	//}

	Pixel PixelFromColor(const Color& color) {
		return Pixel((COM::byte_t)(255 * color.r), 
			(COM::byte_t)(255 * color.g), 
			(COM::byte_t)(255 * color.b),
			(COM::byte_t)(255 * color.a));
	}

	RayCaster::RayCaster(Framebuffer& framebuffer,
		const World& world,
		GEN::Pointer<Shader> shader,
		const M::Matrix4& worldMatrix,
		COM::size_t x, COM::size_t y,
		COM::size_t w, COM::size_t h) 
		:	_framebuffer(framebuffer),
			_world(world), _shader(shader),
			_depth(1),
			_x(x), _y(y), _w(w), _h(h),
			_frameListener(NULL),
			_invWorld(RigidInverse(worldMatrix))
	{
		COM::Config& config = COM::Config::Instance();
		_depth = config.Get("depth", 10);
		_rayDir =  M::Transform(_invWorld, M::Vector3(0.0f, 0.0f, -1.0f));
	}

	void RayCaster::SetFrameListener(FrameListener* frameListener) {
		_frameListener = frameListener;
	}

	DWORD RayCaster::Run(void) {
		const float scalex = 2.0f / _framebuffer.GetWidth();
		const float scaley = 2.0f / _framebuffer.GetHeight();
		const float viewDistance = 10.0f;

		if(_frameListener) _frameListener->BeginRendering();

		for(COM::size_t x = _x; x < _x + _w; ++x) {
			for(COM::size_t y = _y; y < _y + _h; ++y) {
				float fx = -1.0f + x * scalex;
				float fy = -1.0f + y * scaley;

				M::Ray ray;
				ray.origin = M::Transform(_invWorld, M::Vector3(fx, fy, viewDistance));
				ray.direction = _rayDir;
			
				int depth = _depth;
				Color frag = Color::Black;
				World::IntersectionInfo info;
				if(_world.Intersects(ray, &info)) {
					info.primary = true;
					frag = _shader->Hit(depth, _world, info);
				} else {
					frag = _shader->Miss();
				}

				frag.r = M::Clamp(frag.r, 0.0f, 1.0f);
				frag.g = M::Clamp(frag.g, 0.0f, 1.0f);
				frag.b = M::Clamp(frag.b, 0.0f, 1.0f);
				frag.a = M::Clamp(frag.a, 0.0f, 1.0f);

				_framebuffer.SetPixel(x, y, PixelFromColor(frag));
			}
		}

		if(_frameListener) _frameListener->EndRendering();

		return 0;
	}

} // namespace RT0