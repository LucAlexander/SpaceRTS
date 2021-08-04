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
	selectRect(-1, -1, 0, 0),
	zoomCoef(0.1),
	cameraOriginX(0),
	cameraOriginY(0),
	menuTab(nullptr),
	tabOpen(false),
	menu(sf::Vector2f(64, 192)),
	tab(sf::Vector2f(15, 33)),
	factionName(),
	font()
{}

void Player::init(){
	faction = enth::create(0, 0, Faction());
	for (int i = 0;i<4;++i){
		enth::get(Planet(), i)->setFaction(faction);
	}
	// GUI MENU
	menuTab = enth::create(0, 18, Button());
	menuTab->setAction([this](){
		this->toggleTab();
	});
	menuTab->setDepth(depth+1);
	menuTab->setTexture("menuTab.png");
	menu.setPosition(0, 18);
	menu.setFillColor(sf::Color(32, 32, 32));
	menu.setOutlineColor(faction->getColor());
	menu.setOutlineThickness(2);
	tab.setPosition(2, 18);
	tab.setOutlineThickness(2);
	tab.setOutlineColor(faction->getColor());
	tab.setFillColor(faction->getColor());
	font.loadFromFile("./f/FSEX300.ttf");
	factionName.setFont(font);
	factionName.setString(faction->getName());
	factionName.setPosition(2, -2);
	factionName.setFillColor(sf::Color(32, 32, 32));
	factionName.setOutlineThickness(2);
	factionName.setOutlineColor(faction->getColor());
	factionName.setScale(0.5, 0.5);
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

void Player::drawGui(){
	if(tabOpen){
		win::window.draw(menu);
	}
	win::window.draw(tab);
	win::window.draw(factionName);
}

void Player::toggleTab(){
	tabOpen = !tabOpen;
	if (tabOpen){
		menuTab->setX(64);
		tab.setPosition(66, 18);
		return;
	}
	menuTab->setX(0);
	tab.setPosition(2, 18);
}

void Player::cameraZoomUpdate(){
	sf::View gCam = win::window.getView();
	int dir = inp::mouseScroll()*-1;
	gCam.zoom(1+(dir*zoomCoef));
	win::window.setView(gCam);
}

void Player::cameraPositionUpdate(){
	sf::View gCam = win::window.getView();
	float mx, my;
	mx = inp::guiMouseX();
	my = inp::guiMouseY();
	gCam.move(cameraOriginX-mx, cameraOriginY-my);
	cameraOriginX = mx;
	cameraOriginY = my;
	win::window.setView(gCam);
}

void Player::clickLogic(){
	cameraZoomUpdate();
	bool clickL = inp::mousePressed(sf::Mouse::Button::Left);
	bool clickLH = inp::mouseHeld(sf::Mouse::Button::Left);
	bool clickLR = inp::mouseReleased(sf::Mouse::Button::Left);
	bool shift = inp::keyHeld(sf::Keyboard::Key::LShift);
	if (clickL){
		if (shift){
			cameraOriginX = inp::guiMouseX();
			cameraOriginY = inp::guiMouseY();
			return;
		}
		Planet* instance = enth::pointCollides(inp::mouseX(), inp::mouseY(), Planet());
		if (instance != nullptr){
			planetClickLogic(instance);
			return;
		}
		deselectPlanets();
		selectRect.start.x=inp::mouseX();
		selectRect.start.y=inp::mouseY();
	}
	if (clickLH){
		if (selectRect.start.x != -1){
			selectRect.end.x=inp::mouseX();
			selectRect.end.y=inp::mouseY();
			return;
		}
		if (shift){
			cameraPositionUpdate();
		}
		return;
	}
	if (clickLR){
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
