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
	void setDirectionForce(int f);
	void setAdditiveSpdForce(float f);
	void setMultiplicativeSpdForce(float f);
	virtual void update();
	virtual void draw();
protected:
	sf::Sprite sprite;
	Animator anim;
	float spd;
	int direction;
	int life;
	// modification variables
	int directionForce;
	float spdForceAdd;
	float spdForceMult;
};

#endif
