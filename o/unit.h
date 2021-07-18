#ifndef UNIT_H
#define UNIT_H

#include "../e/entity.h"
#include "../e/animator.h"

class Unit : public Entity{
public:
	Unit();
	void update();
private:
	float spd;
	int viewAngle;
	int divergeAngle;
	int convergeAngle;
	int alignAngle;
	int comfortRange;
	Animator animHandler;
};

#endif
