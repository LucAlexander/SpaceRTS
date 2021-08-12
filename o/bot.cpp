#include "bot.h"
#include "../e/settings.h"
#include "../e/entityHandler.h"
#include "../e/rnd.h"

#include <iostream>

Bot::Bot():
	Entity(),
	faction(nullptr),
	actionTime(settings::TPS*3),
	actionTimer(),
	actionType(ACTION::IDLE),
	difficulty(0)
{}

void Bot::init(){
	faction = enth::create(0,0,Faction());
	actionTimer.set(actionTime);
}

void Bot::update(){
	if (actionTimer.ring()){
		switch(difficulty){
			case 0:
			default:
				behaviorEasy();
			break;
		}
		performAction();
		actionTimer.reset();
	}
	actionTimer.tick();
}

void Bot::behaviorEasy(){
	int t = rnd::iRange(0, 4);
	switch(t){
		case 0:actionType=ACTION::IDLE;return;
		case 1:actionType=ACTION::FORTIFY;return;
		case 2:actionType=ACTION::SPREAD;return;
		case 3:actionType=ACTION::UPGRADE;return;
		case 4:actionType=ACTION::ATTACK;return;
	}
}

void Bot::performAction(){
	switch(actionType){
		case ACTION::IDLE:
			std::cout << "IDLE\n";
		return;
		case ACTION::FORTIFY:
			std::cout << "FORTIFY\n";
		return;
		case ACTION::SPREAD:
			std::cout << "SPREAD\n";
		return;
		case ACTION::UPGRADE:
			std::cout << "UPGRADE\n";
		return;
		case ACTION::ATTACK:
			std::cout << "ATTACK\n";
		return;
	}
}

void Bot::setFaction(Faction* f){
	faction = f;
}

Faction* Bot::getFaction()const{
	return faction;
}

void Bot::setDifficulty(int d){
	difficulty = d;
}

