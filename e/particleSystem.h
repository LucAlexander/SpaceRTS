#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "entity.h"
#include "particle.h"
#include "particleSystem.h"
#include "entityHandler.h"

template<class T>
class PartSys : public Entity{
public:
	PartSys();
	PartSys(bool r, int l, int ppe, int mp, int ed);
	void update();
	void draw();
	void setBurst(int ppe);
	void setStream(int life, int ppe, int mp, int ed);
private:
	void handleParticleEvent(int index, T* particle);
	void destroyCheck();
	void emitTry();
	bool burst;
	int life;
	int partsPerEmit;
	int maxParts;
	int emitDelay;
	int emitTimer;
	std::vector<T*> parts;
};

template<class T>
PartSys<T>::PartSys(bool r, int l, int ppe, int mp, int ed):
	Entity(),
	burst(r),
	life(l),
	partsPerEmit(ppe),
	maxParts(mp),
	emitDelay(ed),
	emitTimer(0),
	parts(mp, nullptr)
{
	setHitbox(0, 0, 2, 2);

	if (partsPerEmit > maxParts){
		partsPerEmit = maxParts;
	}
}

template<class T>
PartSys<T>::PartSys():
	PartSys(true, -1, 5, 256, -1)
{}

template<class T>
void PartSys<T>::setBurst(int ppe){
	life = -1;
	emitDelay = -1;
	maxParts = ppe;
	partsPerEmit = ppe;
	burst = true;
}

template<class T>
void PartSys<T>::setStream(int lf, int ppe, int mp, int ed){
	life = lf;
	partsPerEmit = ppe;
	maxParts = mp;
	emitDelay = ed;
	burst = false;
	if(partsPerEmit > maxParts){
		partsPerEmit = maxParts;
	}
}

template<class T>
void PartSys<T>::handleParticleEvent(int index, T* particle){
	if (!particle->alive()){
		delete particle;
		parts[index] = nullptr;
		return;
	}
	particle->update();
}

template<class T>
void PartSys<T>::destroyCheck(){
	for (int i = 0;i<maxParts;++i){
		if (parts[i] != nullptr){
			return;
		}
	}
	enth::destroy(this);
}

template<class T>
void PartSys<T>::emitTry(){
	if (emitTimer == 0){
		int partQ = partsPerEmit;
		for (int i = 0;i<maxParts && partQ > 0;++i){
			if (parts[i] == nullptr){
				parts[i] = new T(x, y);
				partQ --;
			}
		}
		emitTimer = emitDelay;
	}
	emitTimer--;
	life--;
	if (burst){
		life = 0;
	}
}

template<class T>
void PartSys<T>::update(){
	// UPDATE EXISTING PARTICLES
	for (int i = 0;i<maxParts;++i){
		T* particle = parts[i];
		if(particle != nullptr){
			handleParticleEvent(i, particle);
		}
	}
	// DESTROY SEQUENCE
	if (life == 0){
		destroyCheck();
		return;
	}
	// EMIT NEW PARTICLES
	if (life > 0 || burst){
		emitTry();
	}
}

template<class T>
void PartSys<T>::draw(){
	for (int i = 0;i<maxParts;++i){
		if (parts[i] != nullptr){
			parts[i]->draw();
		}
	}
}

#endif
