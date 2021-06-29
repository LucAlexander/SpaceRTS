#ifndef UNIT_H
#define UNIT_H

#include "entity.h"

class Unit : public Entity{
public:
	Unit();
	void update();
	void move();
	void turn(int ang);
private:
	float spd;
};

#endif
