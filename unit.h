#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>

#include "textureTable.h"
#include "entity.h"

class Unit : public Entity{
public:
	Unit();
	void update();
	void move();
	void setAngle(int ang);
	void turn(int ang);
	float getX()const;
	float getY()const;
	int getAngle()const;
	sf::Sprite getSprite()const;
private:
	float spd;
	sf::Sprite sprite;
};

#endif
