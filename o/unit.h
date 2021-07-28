#ifndef UNIT_H
#define UNIT_H

#include "planet.h"

#include "../e/entity.h"
#include "../e/animator.h"

class Unit : public Entity{
public:
	Unit();
	void init();
	void update();
	void setTarget(Planet* t);
private:
	float spd;
	int viewAngle;
	int divergeAngle;
	int convergeAngle;
	int alignAngle;
	int comfortRange;
	Animator animHandler;
	Planet* target;
};

#endif
