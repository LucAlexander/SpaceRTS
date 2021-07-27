#ifndef PLANET_H
#define PLANET_H

#include "../e/entity.h"
#include "faction.h"

class Planet : public Entity{
public:
	Planet();
	void init();
	void draw();
	float getRadius();
	void setRadius(float r);
	bool intersects(float xx, float yy, float rr);
	bool intersects(Planet*);
	void toggleSelect();
	void setFaction(Faction*);
	Faction* getFaction()const;
private:
	float rad;
	bool selected;
	sf::CircleShape circle;
	Faction* faction;
	int population;
};

#endif
