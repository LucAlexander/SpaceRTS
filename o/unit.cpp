#include "unit.h"

#include "../e/utils.h"
#include "../e/rnd.h"
#include "../e/entityHandler.h"
#include "../e/input.h"

#include <iostream>

Unit::Unit():
	Entity(),
	spd(1),
	viewAngle(135),
	divergeAngle(5),
	convergeAngle(0),
	alignAngle(0),
	comfortRange(64),
	animHandler(),
	target(nullptr),
	firstStep(false),
	shipCount(0),
	faction(nullptr)
{}

void Unit::init(){
	setTexture("ship.png");
	
	setHitbox(6, 6, 10, 10);
	
	sprite.setOrigin(8, 8);
	
	sprite.setScale(0.5, 0.5);

	animHandler = Animator(&sprite);
	animHandler.addAnimation("fly", 0, 0, 16, 16, 2);
}

void Unit::update(){
	// SET DIRECTION
	if (target != nullptr){
		direction = utils::pointDirection(x, y, target->getX() + target->getRadius(), target->getY()+target->getRadius());
	}
	Unit* near = enth::nearest(this, Unit());
	int nearDist = enth::distance(this, near);
	if (nearDist < comfortRange && nearDist != -1){
		if (near->getTarget()==target && near->getFaction()==faction){
			int nearDir = utils::pointDirection(x, y, near->getX(), near->getY());
			int augDir = 180-utils::sign(direction-nearDir) < 180 ? 1 : -1;
			direction += augDir*(nearDist * 0.2);
		}
	}
	// CREATE MOVEMENT VECTORS
	float xvec = utils::lengthDirX(spd, direction);
	float yvec = utils::lengthDirY(spd, direction);
	// COLLISIONS AND MOVEMENT
	Unit* other = enth::collides(this, Unit(), xvec);
	if (other != nullptr){
		if (other->getTarget() == target){
			float nth = xvec/10;
			while(!enth::collides(this, other, nth)){
				x += nth;
			}
			xvec = 0;
		}
	}
	x += xvec;
	other = enth::collides(this, Unit(), 0, yvec);
	if (other != nullptr){
		if (other->getTarget() == target){
			float nth = yvec/10;
			while(!enth::collides(this, other, 0, nth)){
				y += nth;
			}
			yvec = 0;
		}
	}
	y += yvec;
	if (target != nullptr){
		if (enth::collides(this, target)){
			target->addPopulation(faction, shipCount);
			enth::destroy(this);
		}
	}
	// ANIMATE
	animHandler.playAnimation("fly");
}

void Unit::setShipCount(int c){
	shipCount = c;
}

int Unit::getShipCount()const{
	return shipCount;
}

void Unit::setFaction(Faction* f){
	faction = f;
}

Faction* Unit::getFaction(){
	return faction;
}

Planet* Unit::getTarget()const{
	return target;
}

void Unit::setTarget(Planet* t){
	target = t;
	direction = utils::pointDirection(x, y, target->getX() + target->getRadius(), target->getY()+target->getRadius());
}
