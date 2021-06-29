#include "entity.h"
#include "win.h"

Entity::Entity():
	sprite(),
	depth(0)
{}

Entity::~Entity(){}

void Entity::update(){}

void Entity::draw(){
	win::window.draw(sprite);
}

void Entity::drawGui(){}

void Entity::setAngle(float ang){
	sprite.setRotation(ang);
}

void Entity::setTexture(const char* dir){
	sprite.setTexture(*txtab::load(dir));
}

void Entity::setPosition(float xx, float yy){
	sprite.setPosition(xx, yy);
}

float Entity::getX()const{
	return sprite.getPosition().x;
}

float Entity::getY()const{
	return sprite.getPosition().y;
}

float Entity::getAngle()const{
	return sprite.getRotation();
}

sf::Sprite Entity::getSprite()const{
	return sprite;
}
