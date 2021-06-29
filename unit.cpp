#include "unit.h"
#include "utils.h"
#include "entityHandler.h"

Unit::Unit():
	Entity(),
	spd(3)
{
	setTexture("ship.png");
}

void Unit::update(){
	move();
}

void Unit::move(){
	float xvec = utils::lengthDirX(spd, getAngle());
	float yvec = utils::lengthDirY(spd, getAngle());
	sprite.move(xvec, yvec);
}

void Unit::turn(int ang){
	sprite.rotate(ang);
}


