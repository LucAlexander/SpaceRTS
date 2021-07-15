#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>

class Planet{
public:
	Planet();
	Planet(int x, int y, int r);
	sf::CircleShape getSprite();
	float getRadius();
	void setRadius(float r);
	bool intersects(float xx, float yy, float rr);
	bool intersects(Planet);
private:
	sf::CircleShape sprite;
};

#endif
