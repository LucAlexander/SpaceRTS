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
	faction(nullptr),
	spdMod(1),
	dirAugCoef(90),
	spdAugCoef(0.05f)
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
		int tempDir = utils::pointDirection(x, y, target->getX() + target->getRadius(), target->getY()+target->getRadius());
		direction = utils::pointDirection(x, y, target->getX() + target->getRadius()+utils::lengthDirX(target->getRadius(), tempDir), target->getY()+target->getRadius() + utils::lengthDirY(target->getRadius(), tempDir));
	}
	Unit* near = enth::nearest(this, Unit());
	int nearDist = enth::distance(this, near);
	if (nearDist < comfortRange && nearDist != -1){
		if (near->getFaction()==faction){
			int nearDir = utils::pointDirection(x, y, near->getX(), near->getY());
			int augDir = 180-utils::sign(direction-nearDir) < 180 ? 1 : -1;
			direction += augDir*(dirAugCoef/nearDist);
			spdMod += spdAugCoef/nearDist;
		}
	}
	// CREATE MOVEMENT VECTORS
	float xvec = utils::lengthDirX(spd*spdMod, direction);
	float yvec = utils::lengthDirY(spd*spdMod, direction);
	spdMod = 1;
	// COLLISIONS AND MOVEMENT
	Unit* other = enth::collides(this, Unit(), xvec);
	if (other != nullptr){
		if (other->getTarget() == target){
			xvec = 0;
		}
	}
	x += xvec;
	other = enth::collides(this, Unit(), 0, yvec);
	if (other != nullptr){
		if (other->getTarget() == target){
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
