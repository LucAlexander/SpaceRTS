#include "player.h"
#include "planet.h"
#include "../e/entityHandler.h"
#include "../e/input.h"

#include <iostream>

Player::Player():
	Entity(),
	faction(nullptr)
{}

void Player::init(){
	faction = enth::create(0, 0, Faction());
	std::cout << faction->getName() << "\n";
	enth::get(Planet())->setFaction(faction);
	std::cout << enth::get(Planet())->getX() << "\t";
	std::cout << enth::get(Planet())->getY() << "\n";
}

void Player::update(){
	if (inp::mousePressed(sf::Mouse::Button::Left)){
		Planet* instance = enth::pointCollides(inp::mouseX(), inp::mouseY(), Planet());
		if (instance != nullptr){
			planetClickLogic(instance);
		}
	}
	else if (inp::mousePressed(sf::Mouse::Button::Right)){
		Planet* instance = enth::pointCollides(inp::mouseX(), inp::mouseY(), Planet());
		if (instance != nullptr){
			setTarget(instance);
		}
	}
}

void Player::planetClickLogic(Planet* instance){
	if (instance->getFaction() == faction){
		instance->toggleSelect();
		return;
	}
	setTarget(instance);
}

void Player::setTarget(Planet* instance){
	int planetCount = enth::number(Planet());
	for (int i =0;i<planetCount;++i){
		Planet* pl = enth::get(Planet(), i);
		if (pl != instance){
			if (pl->getFaction() == faction && pl->getSelected()){
				pl->setTarget(instance);
				pl->toggleSelect();
			}
		}
	}
}

Faction* Player::getFaction()const{
	return faction;
}


void Player::setFactionName(std::string name){
	faction->setName(name);
}
