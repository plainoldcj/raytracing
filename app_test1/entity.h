/*
solution:	raytracing
project:	app_test1
file:		entity.h
author:		cj
*/

#pragma once

class Entity {
public:
	virtual ~Entity(void) { }

	virtual void RenderGL(void) const = 0;
};