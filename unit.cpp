#include "unit.h"
#include "utils.h"
#include "unitTarget.h"
#include "entityHandler.h"

Unit::Unit():
	Entity(),
	spd(2),
	viewAngle(135),
	divergeAngle(5),
	convergeAngle(0),
	alignAngle(0),
	comfortRange(64)
{
	setTexture("ship.png");
	sprite.setOrigin(8, 8);
}

void Unit::update(){
	float x = getX();
	float y = getY();
	UnitTarget* target = enth::nearest(x, y, UnitTarget());
	if (target != nullptr){
		direction = utils::pointDirection(x, y, target->getX(), target->getY());
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
	float xvec = utils::lengthDirX(spd, direction);
	float yvec = utils::lengthDirY(spd, direction);
	sprite.move(xvec, yvec);
}

