#include "entity.h"
#include "win.h"

Entity::Entity():
	sprite(),
	hitbox(0, 0, 0, 0),
	depth(0),
	direction(0)
{}

Entity::~Entity(){}

void Entity::update(){}

void Entity::draw(){
	sprite.setRotation(-direction);
	win::window.draw(sprite);
}

void Entity::drawGui(){}

void Entity::setDirection(int ang){
	direction = ang;
}

void Entity::setTexture(const char* dir){
	sf::Texture* t = txtab::load(dir);
	sprite.setTexture(*t);
	sf::Vector2u s = t->getSize();
	setHitbox(0, 0, s.x, s.y);
}

float Entity::getOriginX()const{
	return sprite.getOrigin().x;
}

float Entity::getOriginY()const{
	return sprite.getOrigin().y;
}

utils::Rect Entity::getGlobalHitbox()const{
	float l, t, r, b;
	l = getX()-getOriginX()+hitbox.start.x;
	t = getY()-getOriginY()+hitbox.start.y;
	r = l+hitbox.end.x-hitbox.start.x;
	b = t+hitbox.end.y-hitbox.start.y;
	return utils::Rect(l,t,r,b);
}

utils::Rect Entity::getHitbox()const{
	return hitbox;
}

void Entity::setHitbox(float x1, float y1, float x2, float y2){
	hitbox.start.x = x1;
	hitbox.start.y = y1;
	hitbox.end.x = x2;
	hitbox.end.y = y2;
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

int Entity::getDirection()const{
	return direction;
}

sf::Sprite Entity::getSprite()const{
	return sprite;
}

int Entity::getDepth()const{
	return depth;
}
