#ifndef UNIT_H
#define UNIT_H

#include "planet.h"
#include "faction.h"

#include "../e/entity.h"
#include "../e/animator.h"

class Unit : public Entity{
public:
	Unit();
	void init();
	void update();
	void setTarget(Planet* t);
	void setFaction(Faction* f);
	Faction* getFaction();
	void setShipCount(int c);
	int getShipCount()const;
	Planet* getTarget()const;
private:
	float spd;
	int viewAngle;
	int divergeAngle;
	int convergeAngle;
	int alignAngle;
	int comfortRange;
	Animator animHandler;
	Planet* target;
	bool firstStep;
	int shipCount;
	Faction* faction;
};

#endif
