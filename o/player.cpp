#include "player.h"
#include "planet.h"
#include "../e/entityHandler.h"
#include "../e/input.h"

Player::Player():
	Entity(),
	faction("Earth")
{}

void Player::update(){
	if (inp::mousePressed(sf::Mouse::Button::Left)){
		Planet* instance = enth::pointCollides(inp::mouseX(), inp::mouseY(), Planet());
		if (instance != nullptr){
			instance->toggleSelect();
		}
	}
}

std::string Player::getFactionName(){
	return faction;
}
