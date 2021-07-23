#include "particle.h"
#include "utils.h"
#include "win.h"
#include "textureTable.h"

Particle::Particle():
	Particle(0, 0)
{}

Particle::Particle(float x, float y):
	sprite(),
	anim(),
	spd(0.0),
	direction(0),
	life(0)
{
	sprite.setPosition(x, y);
}

bool Particle::alive()const{
	return life > 0;
}

void Particle::update(){
	float xvec = utils::lengthDirX(spd, direction);
	float yvec = utils::lengthDirY(spd, direction);
	sprite.move(xvec, yvec);
	life--;
}

void Particle::draw(){
	win::window.draw(sprite);
}

void Particle::setTexture(const char* dir){
	sf::Texture* t = txtab::load(dir);
	sprite.setTexture(*t);
}


