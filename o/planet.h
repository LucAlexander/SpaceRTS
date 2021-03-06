#ifndef PLANET_H
#define PLANET_H

#include "../e/entity.h"
#include "../e/alarm.h"
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
	void addPopulation(Faction* f, int pop);
private:
	void spawnUnits();
	float rad;
	bool selected;
	sf::CircleShape circle;
	Faction* faction;
	int population;
	int resource;
	Planet* target;
	int thickness;
	int selectThickness;
	sf::Color selectedColor;
	int vibranceCoef;
	Alarm grow;
	Alarm drain;
	sf::Text popText;
	sf::Text resText;
	sf::Font popFont;
	
	enum TYPE{
		POPULATION,
		RESOURCE
	};

	TYPE type;
	float textScale;
	int popWeight;
};

#endif
