/*
solution:	raytracing
project:	app_test1
file:		sphere.h
author:		cj
*/

#pragma once

#include "../system/glx.h"
#include "../rtengine0/ent_sphere.h"
#include "entity.h"

class Sphere : public Entity, public RT0::ENT::Sphere {
private:
	float _radius;
	int _numSlices;
	int _numStacks;

	GLUquadric* _quadric;
public:
	explicit Sphere(float radius);
	~Sphere(void);

	void RenderGL(void) const;
};