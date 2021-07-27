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
}

void Player::update(){
	if (inp::mousePressed(sf::Mouse::Button::Left)){
		Planet* instance = enth::pointCollides(inp::mouseX(), inp::mouseY(), Planet());
		if (instance != nullptr){
			instance->toggleSelect();
		}
	}
}

Faction* Player::getFaction()const{
	return faction;
}


void Player::setFactionName(std::string name){
	faction->setName(name);
}
