#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include "animator.h"

class Particle{
public:
	Particle();
	Particle(float xx, float yy);
	bool alive()const;
	void setTexture(const char* dir);
	virtual void update();
	virtual void draw();
protected:
	sf::Sprite sprite;
	Animator anim;
	float spd;
	int direction;
	int life;
};

#endif
