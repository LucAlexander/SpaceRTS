#include "planet.h"
#include "../e/win.h"
#include "../e/input.h"
#include "../e/entityHandler.h"
#include "../e/rnd.h"

Planet::Planet():
	Entity(),
	rad(25),
	selected(false),
	circle(rad, 64),
	faction(nullptr),
	population(rnd::iRange(0, 50))
{}

void Planet::init(){
	setHitbox(0, 0, rad*2, rad*2);
}

void Planet::draw(){
	if (selected){
		circle.setFillColor(sf::Color::Blue);
	}
	else{
		circle.setFillColor(sf::Color::White);
	}
	circle.setPosition(x, y);
	win::window.draw(circle);
}

float Planet::getRadius(){
	return rad;
}

void Planet::setRadius(float r){
	setHitbox(0, 0, r*2, r*2);
	rad = r;
	circle.setRadius(rad);
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


void Planet::toggleSelect(){
	selected = !selected;
}

void Planet::setFaction(Faction* f){
	faction = f;
}

Faction* Planet::getFaction()const{
	return faction;
}
