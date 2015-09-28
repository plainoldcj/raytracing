/*
solution:	raytracing
project:	app_test4
file:		app_test4.cpp
author:		cj
*/

#pragma comment(lib, "cudart.lib")

#include <Windows.h>
#include "../common/config.h"
#include "../system/loop.h"
#include "window.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
	try {
		COM::Config& config = COM::Config::Instance();
		int width = config.Get("width", 800);
		int height = config.Get("height", 800);
		int rwidth = config.Get("rwidth", 1024);
		int rheight = config.Get("rheight", 1024);

		Window window(width, height, rwidth, rheight);
		SYS::EnterLoop(window);
	} catch(...) {
		MessageBox(NULL, TEXT("unhandled exception.\nview logfile for more information"),
			TEXT("Im really sorry..."), MB_OK);
		return -1;
	}
	return 0;
}