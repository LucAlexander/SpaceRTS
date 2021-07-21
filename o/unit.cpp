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


	setTexture("ship.png");
	
	setHitbox(0, 0, 16, 16);
	
	sprite.setOrigin(8, 8);

	direction = rnd::iRange(0, 359);
	
	animHandler = Animator(&sprite);
	animHandler.addAnimation("fly", 0, 0, 16, 16, 2);
}

void Unit::update(){
	UnitTarget* target = enth::nearest(x, y, UnitTarget());
	if (target != nullptr){
		direction = utils::pointDirection(x, y, target->getX(), target->getY());
	}
	// CREATE MOVEMENT VECTORS
	float xvec = utils::lengthDirX(spd, direction);
	float yvec = utils::lengthDirY(spd, direction);
	// COLLISIONS AND MOVEMENT
	Unit* other = enth::collides(this, Unit(), xvec);
	if (other != nullptr){
		float nth = xvec/10;
		while(!enth::collides(this, other, nth)){
			x += nth;
		}
		xvec = 0;
	}
	x += xvec;
	other = enth::collides(this, Unit(), 0, yvec);
	if (other != nullptr){
		float nth = yvec/10;
		while(!enth::collides(this, other, 0, nth)){
			y += nth;
		}
		yvec = 0;
	}
	y += yvec;
	// WRAPPING MAP BORDERS
	if (x < 0 ){
		x = 1024;
	}
	else if(x > 1024){
		x = 0;
	}
	if (y < 0 ){
		y = 1024;
	}
	else if(y > 1024){
		y = 0;
	}
	// ANIMATE
	animHandler.playAnimation("fly");
}
