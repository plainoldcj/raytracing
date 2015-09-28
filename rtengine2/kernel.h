/*
solution:	raytracing
project:	rtengine2
file:		kernel.h
author:		cj
*/

#pragma once

namespace RT2 {

	class RenderTarget;
	class World;

	void RunKernel(RenderTarget& renderTarget, World& world);

} // namespace RT2