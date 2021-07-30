#include "player.h"
#include "planet.h"
#include "../e/entityHandler.h"
#include "../e/input.h"
#include "../e/debug.h"
#include "../e/win.h"

#include <iostream>

Player::Player():
	Entity(),
	faction(nullptr),
	selectRect(-1, -1, 0, 0)
{}

void Player::init(){
	faction = enth::create(0, 0, Faction());
	std::cout << faction->getName() << "\n";
	for (int i = 0;i<4;++i){
		enth::get(Planet(), i)->setFaction(faction);
		std::cout << enth::get(Planet(), i)->getX() << "\t";
		std::cout << enth::get(Planet(), i)->getY() << "\n";
	}
}

void Player::update(){
	clickLogic();
	dbug::showHitboxes(false);
	if(inp::keyHeld(sf::Keyboard::Key::Tab)){
		dbug::showHitboxes(true);
	}
}

void Player::draw(){
	if (selectRect.start.x!=-1){
		sf::RectangleShape drawBound;
		drawBound.setPosition(selectRect.start.x, selectRect.start.y);
		drawBound.setSize(sf::Vector2f(selectRect.end.x-selectRect.start.x, selectRect.end.y-selectRect.start.y));
		drawBound.setOutlineThickness(3);
		drawBound.setOutlineColor(faction->getColor());
		drawBound.setFillColor(sf::Color(0, 0, 0, 0));
		win::window.draw(drawBound);
	}
}

void Player::clickLogic(){
	if (inp::mousePressed(sf::Mouse::Button::Left)){
		Planet* instance = enth::pointCollides(inp::mouseX(), inp::mouseY(), Planet());
		if (instance != nullptr){
			planetClickLogic(instance);
			return;
		}
		deselectPlanets();
		selectRect.start.x=inp::mouseX();
		selectRect.start.y=inp::mouseY();
	}
	if (inp::mouseHeld(sf::Mouse::Button::Left)){
		if (selectRect.start.x != -1){
			selectRect.end.x=inp::mouseX();
			selectRect.end.y=inp::mouseY();
		}
		return;
	}
	if (inp::mouseReleased(sf::Mouse::Button::Left)){
		boundSelectPlanets();
		selectRect.start.x=-1;
		selectRect.start.y=-1;
		selectRect.end.x=0;
		selectRect.end.y=0;
		return;
	}
	if (inp::mousePressed(sf::Mouse::Button::Right)){
		Planet* instance = enth::pointCollides(inp::mouseX(), inp::mouseY(), Planet());
		if (instance != nullptr){
			setTarget(instance);
		}
		return;
	}
}

void Player::deselectPlanets(){
	int c = enth::number(Planet());
	for (int i = 0;i<c;++i){
		Planet* instance = enth::get(Planet(), i);
		if(instance->getFaction() == faction){
			if (instance->getSelected()){
				instance->toggleSelect();
			}
		}
	}
}

void Player::boundSelectPlanets(){
	int c = enth::number(Planet());
	for (int i = 0;i<c;++i){
		Planet* instance = enth::get(Planet(), i);
		int iRad = instance->getRadius();
		if (utils::pointInRect(utils::v2(instance->getX()+iRad, instance->getY()+iRad), selectRect) && instance->getFaction()==faction){
			if (!instance->getSelected()){
				instance->toggleSelect();
			}
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
	if (instance->getFaction() == faction){
		if (instance->getSelected()){
			instance->toggleSelect();
		}
	}
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
