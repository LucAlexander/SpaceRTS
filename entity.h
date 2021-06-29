#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "textureTable.h"

class Entity{
public:
	Entity();
	virtual ~Entity();
	virtual void update();
	virtual void draw();
	virtual void drawGui();
	float getX()const;
	float getY()const;
	void setPosition(float xx, float yy);
	float getAngle()const;
	void setAngle(float ang);
	sf::Sprite getSprite()const;
	void setTexture(const char* dir);
protected:
	sf::Sprite sprite;
	int depth;
};

#endif
