#ifndef PLANET_H
#define PLANET_H

#include "../e/entity.h"

class Planet : public Entity{
public:
	Planet();
	void draw();
	float getRadius();
	void setRadius(float r);
	bool intersects(float xx, float yy, float rr);
	bool intersects(Planet*);
private:
	float rad;
};

#endif
