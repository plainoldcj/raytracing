/*
solution:	raytracing
project:	app_test0
file:		app_test0.cpp
author:		cj
*/

#include <Windows.h>
#include "../common/config.h"
#include "../system/loop.h"

#include "../rtengine0/framebuffer.h"
#include "../rtengine0/imagewindow.h"
#include "../rtengine0/world.h"
#include "../rtengine0/renderer.h"

#include "../rtengine0/ent_sphere.h"
#include "../rtengine0/ill_pointlight.h"
#include "../rtengine0/sh_default.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
	try {
		COM::Config& config = COM::Config::Instance();
		int width = config.Get("width", 400);
		int height = config.Get("height", 400);
		float reflectivity = config.Get("reflectivity", 0.3f);

		RT0::entPtr_t sphere0(new RT0::ENT::Sphere(0.4f));
		sphere0->SetPosition(M::Vector3(-0.6f, 0.0f, -5.0f));
		//sphere0->GetSkin().SetDiffuseColor(RT0::Color::FromBytes(150, 205, 237));
		sphere0->GetSkin().SetDiffuseColor(RT0::Color(1.0f, 0.0f, 0.0f));
		sphere0->GetSkin().SetReflectivity(reflectivity);

		RT0::entPtr_t sphere1(new RT0::ENT::Sphere(0.4f));
		sphere1->SetPosition(M::Vector3(0.6f, 0.0f, -5.0f));
		//sphere1->GetSkin().SetDiffuseColor(RT0::Color::FromBytes(56, 126, 167));
		sphere1->GetSkin().SetDiffuseColor(RT0::Color(1.0f, 0.5f, 0.5f));
		sphere1->GetSkin().SetReflectivity(reflectivity);

		RT0::entPtr_t sphere2(new RT0::ENT::Sphere(0.4f));
		sphere2->SetPosition(M::Vector3(0.0f, 0.6f, -5.0f));
		//sphere2->GetSkin().SetDiffuseColor(RT0::Color::FromBytes(57, 183, 255));
		sphere2->GetSkin().SetDiffuseColor(RT0::Color(0.0f, 0.0f, 1.0f));
		sphere2->GetSkin().SetReflectivity(reflectivity);

		RT0::entPtr_t sphere3(new RT0::ENT::Sphere(0.4f));
		sphere3->SetPosition(M::Vector3(0.0f, -0.6f, -5.0f));
		sphere3->GetSkin().SetDiffuseColor(RT0::Color::FromBytes(57, 183, 255));
		sphere3->GetSkin().SetReflectivity(reflectivity);

		RT0::lightPtr_t light(new RT0::ILL::Pointlight());
		light->SetPosition(M::Vector3(-2.0f, 2.0f, -2.0f));

		RT0::World world;
		world.AddEntity(sphere0);
		world.AddEntity(sphere1);
		world.AddEntity(sphere2);
		world.AddEntity(sphere3);
		world.AddLight(light);

		RT0::Framebuffer framebuffer(width, height);
		RT0::ImageWindow imageWindow(framebuffer, 800, 800);

		RT0::Renderer& renderer = RT0::Renderer::Instance();
		renderer.Render(framebuffer, world, RT0::AllocShader<RT0::SH::Default>, &imageWindow);
		/*renderer.Join();
		imageWindow.UpdateSubFrame(0, 0, width, height);*/
		SYS::EnterLoop(imageWindow);
	} catch(...) {
		MessageBox(NULL, TEXT("unhandled exception.\nview logfile for more information"),
			TEXT("Im really sorry..."), MB_OK);
		return -1;
	}
	
	return 0;
}