/*
solution:	raytracing
project:	app_test1
file:		world.h
author:		cj
*/

#pragma once

#include <list>
#include "../rtengine0/world.h"
#include "../common/pointer.h"

class Entity;

typedef GEN::Pointer<Entity> entPtr_t;

class World {
private:
	typedef std::list<entPtr_t>::iterator entIt_t;
	typedef std::list<entPtr_t>::const_iterator centIt_t;

	std::list<entPtr_t> _entities;
public:
	void AddEntity(entPtr_t entity);

	void Render(void) const;
};