#include "unit.h"
#include "utils.h"
#include "entityHandler.h"

Unit::Unit():
	Entity(),
	spd(1.0),
	sprite()
{
	sprite.setTexture(*txtab::load("ship.png"));
	sprite.setPosition(64, 64);
	sprite.setRotation(0);
}

void Unit::update(){
	//turn(1);
	move();
}

void Unit::move(){
	float xvec = utils::lengthDirX(spd, getAngle());
	float yvec = utils::lengthDirY(spd, getAngle());
	sprite.move(xvec, yvec);
}

void Unit::setAngle(int ang){
	sprite.setRotation(ang);
}

void Unit::turn(int ang){
	sprite.rotate(ang);
}

float Unit::getX()const{
	return sprite.getPosition().x;
}

float Unit::getY()const{
	return sprite.getPosition().y;
}

int Unit::getAngle()const{
	return sprite.getRotation();
}

sf::Sprite Unit::getSprite()const{
	return sprite;
}
