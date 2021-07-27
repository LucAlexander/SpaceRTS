#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "utils.h"
#include "textureTable.h"

class Entity{
public:
	Entity();
	virtual ~Entity();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void drawGui();
	
	float getX()const;
	float getY()const;
	float getOriginX()const;
	float getOriginY()const;
	void setPosition(float xx, float yy);
	void setX(float yy);
	void setY(float yy);

	utils::Rect getGlobalHitbox()const;
	utils::Rect getHitbox()const;
	void setHitbox(float x, float y, float xx, float yy);

	int getDirection()const;
	void setDirection(int ang);
	
	sf::Sprite getSprite()const;
	void setTexture(const char* dir);
	
	int getDepth()const;
protected:
	sf::Sprite sprite;
	utils::Rect hitbox;
	float x, y;
	int depth;
	int direction;
};

#endif
