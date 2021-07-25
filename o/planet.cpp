#include "planet.h"
#include "../e/win.h"
#include "../e/input.h"
#include "../e/entityHandler.h"

Planet::Planet():
	Entity(),
	rad(25)
{
	setHitbox(0, 0, rad*2, rad*2);
}

void Planet::draw(){
	sf::CircleShape c(rad, 64);
	c.setPosition(x, y);
	win::window.draw(c);
}

float Planet::getRadius(){
	return rad;
}

void Planet::setRadius(float r){
	setHitbox(0, 0, r*2, r*2);
	rad = r;
}

bool Planet::intersects(float x2, float y2, float r2){
	float x1 = x + rad;
	float y1 = y + rad;
	x2 += r2;
	y2 += r2;
	float rsq = (rad+r2);
	float xsq = (x1-x2);
	float ysq = (y1-y2);
	rsq*=rsq;
	xsq*=xsq;
	ysq*=ysq;
	return (rsq >= (xsq+ysq));
}

bool Planet::intersects(Planet* other){
	float r1 = rad;
	float r2 = other->getRadius();
	float x1 = x + r1;
	float y1 = y + r1;
	float x2 = other->getX() + r2;
	float y2 = other->getY() + r2;
	float rsq = (r1+r2);
	float xsq = (x1-x2);
	float ysq = (y1-y2);
	rsq*=rsq;
	xsq*=xsq;
	ysq*=ysq;
	return (rsq >= (xsq+ysq));
}

