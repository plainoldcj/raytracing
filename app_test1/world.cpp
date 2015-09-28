/*
solution:	raytracing
project:	app_test1
file:		world.cpp
author:		cj
*/

#include "entity.h"
#include "world.h"

void World::AddEntity(entPtr_t entity) {
	_entities.push_back(entity);
}

void World::Render(void) const {
	for(centIt_t entIt(_entities.cbegin()); entIt != _entities.cend(); ++entIt) {
		(*entIt)->RenderGL();
	}
}