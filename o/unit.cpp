#include "unit.h"
#include "unitTarget.h"

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
	animHandler()
{

	setHitbox(0, 0, 16, 16);

	setTexture("ship.png");
	sprite.setOrigin(8, 8);

	direction = rnd::iRange(0, 359);
	
	animHandler = Animator(&sprite);
	animHandler.addAnimation("fly", 0, 0, 16, 16, 2);
}

void Unit::update(){
	float x = getX();
	float y = getY();
	UnitTarget* target = enth::nearest(x, y, UnitTarget());
	if (target != nullptr){
		direction = utils::pointDirection(x, y, target->getX(), target->getY());
	}
	float xvec = utils::lengthDirX(spd, direction);
	float yvec = utils::lengthDirY(spd, direction);
	sprite.move(xvec, yvec);
	if (enth::collides(this, Unit())!=nullptr){
		enth::destroy(this);
	}
	// wrap map borders
	if (x < 0 ){
		sprite.setPosition(1024, y);
	}
	else if(x > 1024){
		sprite.setPosition(0, y);
	}
	if (y < 0 ){
		sprite.setPosition(x, 1024);
	}
	else if(y > 1024){
		sprite.setPosition(x, 0);
	}
	animHandler.playAnimation("fly");
}
