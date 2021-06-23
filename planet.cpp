#include "planet.h"

Planet::Planet():
	Planet(0, 0, 1)
{}

Planet::Planet(int x, int y, int r):
	sprite(r, 64)
{
	sprite.setPosition(x, y);
	sprite.setFillColor(sf::Color(0, 0, 0, 0));
	sprite.setOutlineColor(sf::Color(0, 255, 0));
	sprite.setOutlineThickness(1.0f);
}

sf::CircleShape Planet::getSprite(){
	return sprite;
}

float Planet::getRadius(){
	return sprite.getRadius();
}

void Planet::setRadius(float r){
	sprite.setRadius(r);
}

bool Planet::intersects(float x2, float y2, float r2){
	float r1 = sprite.getRadius();
	sf::Vector2f pl = sprite.getPosition();
	float x1 = pl.x + r1;
	float y1 = pl.y + r1;
	x2 += r2;
	y2 += r2;
	float rsq = (r1+r2);
	float xsq = (x1-x2);
	float ysq = (y1-y2);
	rsq*=rsq;
	xsq*=xsq;
	ysq*=ysq;
	return (rsq >= (xsq+ysq));
}

bool Planet::intersects(Planet other){
	float r1 = sprite.getRadius();
	float r2 = other.getRadius();
	sf::Vector2f pl1 = sprite.getPosition();
	sf::Vector2f pl2 = other.getSprite().getPosition();
	float x1 = pl1.x + r1;
	float y1 = pl1.y + r1;
	float x2 = pl2.x + r2;
	float y2 = pl2.y + r2;
	float rsq = (r1+r2);
	float xsq = (x1-x2);
	float ysq = (y1-y2);
	rsq*=rsq;
	xsq*=xsq;
	ysq*=ysq;
	return (rsq >= (xsq+ysq));
}

