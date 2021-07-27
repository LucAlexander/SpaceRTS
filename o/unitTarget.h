#ifndef UNITT_H
#define UNITT_H

#include "../e/entity.h"
#include "../e/particleSystem.h"
#include "../e/rnd.h"

class UnitTarget : public Entity{
public:
	UnitTarget();
	void init();
	void update();

	
};

class TestPart : public Particle{
public:
	TestPart(float x, float y):
		Particle(x, y)
	{
		setTexture("targetParticle.png");

		spd = rnd::iRange(1, 3);
		direction = (rnd::iRange(0, 15)*24) + rnd::iRange(0, 15);
		life = rnd::iRange(1, 3) * (utils::TPS/2);

		directionForce = 1;
	}
};
#endif
