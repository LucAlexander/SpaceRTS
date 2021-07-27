#ifndef PLANET_H
#define PLANET_H

#include "../e/entity.h"
#include "faction.h"

class Planet : public Entity{
public:
	Planet();
	void init();
	void update();
	void draw();
	float getRadius();
	void setRadius(float r);
	bool intersects(float xx, float yy, float rr);
	bool intersects(Planet*);
	void toggleSelect();
	bool getSelected()const;
	void setFaction(Faction*);
	void setTarget(Planet* t);
	Faction* getFaction()const;
private:
	float rad;
	bool selected;
	sf::CircleShape circle;
	Faction* faction;
	int population;
	Planet* target;
};

#endif
