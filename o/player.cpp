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
	upgrade(nullptr),
	growthRate(nullptr),
	growthCap(nullptr),
	drainSpeed(nullptr),
	menu(sf::Vector2f(64, 192)),
	tab(sf::Vector2f(15, 33)),
	upgradeOutline(sf::Vector2f(34, 18)),
	chooseUpgrade(sf::Vector2f(160, 64)),
	factionName(),
	techLevel(),
	resourceLevel(),
	nextCost(),
	growthUpLabel(),
	growthCapUpLabel(),
	drainUpLabel(),
	font(),
	techString("TECH "),
	resourceString("RESOURCES: "),
	costString("COST: "),
	tabOpen(false),
	upgradeMenuQueue(0)
{}

void Player::init(){
	faction = enth::create(0, 0, Faction());
	for (int i = 0;i<16;++i){
		enth::get(Planet(), i)->setFaction(faction);
	}
	// GUI
	setupButtons();
	setupText();
	setupElements();
}

void Player::setupButtons(){
	menuTab = enth::create(0, 18, Button());
	menuTab->setAction([this](){
		this->toggleTab();
	});
	menuTab->setDepth(depth+1);
	menuTab->setTexture("menuTab.png");
	upgrade = enth::create(6, 62, Button());
	upgrade->setAction([this](){
		if (this->faction->getResource() > this->faction->getCost()){
			this->upgradeMenuQueue ++;
		}
		this->faction->tryUpgrade();
		this->updateMenuText();
	});
	upgrade->setTexture("upgrade.png");
	upgrade->setDepth(depth+1);
	upgrade->setShow(tabOpen);
	growthRate = enth::create(108, 96, Button());
	growthRate->setTexture("growthRate.png");
	growthRate->setAction([this](){
		this->upgradeMenuQueue--;
		this->faction->upgradeGrowthRate();
	});
	growthRate->setDepth(depth+1);
	growthRate->setShow(false);
	growthCap = enth::create(152, 96, Button());
	growthCap->setTexture("growthCap.png");
	growthCap->setAction([this](){
		this->upgradeMenuQueue--;
		this->faction->upgradeGrowthCap();
	});
	growthCap->setDepth(depth+1);
	growthCap->setShow(false);
	drainSpeed = enth::create(196, 96, Button());
	drainSpeed->setTexture("drainSpeed.png");
	drainSpeed->setAction([this](){
		this->upgradeMenuQueue--;
		this->faction->upgradeDrainRate();
	});
	drainSpeed->setDepth(depth+1);
	drainSpeed->setShow(false);
}

void Player::setupText(){
	font.loadFromFile("./f/FSEX300.ttf");
	factionName.setFont(font);
	factionName.setString(faction->getName());
	factionName.setPosition(2, -2);
	factionName.setFillColor(sf::Color(32, 32, 32));
	factionName.setOutlineThickness(2);
	factionName.setOutlineColor(faction->getColor());
	factionName.setScale(0.5, 0.5);
	techLevel.setFont(font);
	techLevel.setString(techString + std::to_string(faction->getTech()));
	techLevel.setPosition(6, 48);
	techLevel.setFillColor(sf::Color(16, 16, 16));
	techLevel.setOutlineThickness(2);
	techLevel.setOutlineColor(faction->getColor());
	techLevel.setScale(0.25, 0.25);
	resourceLevel.setFont(font);
	resourceLevel.setString(resourceString + std::to_string(faction->getResource()));
	resourceLevel.setPosition(6, 96);
	resourceLevel.setFillColor(sf::Color(16, 16, 16));
	resourceLevel.setOutlineThickness(2);
	resourceLevel.setOutlineColor(faction->getColor());
	resourceLevel.setScale(0.25, 0.25);
	nextCost.setFont(font);
	nextCost.setString(costString + std::to_string(faction->getCost()));
	nextCost.setPosition(6, 80);
	nextCost.setFillColor(sf::Color(16, 16, 16));
	nextCost.setOutlineThickness(2);
	nextCost.setOutlineColor(faction->getColor());
	nextCost.setScale(0.25, 0.25);
	growthUpLabel.setFont(font);
	growthUpLabel.setString("Increase\nGrowth\nRate");
	growthUpLabel.setPosition(100, 112);
	growthUpLabel.setFillColor(sf::Color(16, 16, 16));
	growthUpLabel.setOutlineThickness(2);
	growthUpLabel.setOutlineColor(faction->getColor());
	growthUpLabel.setScale(0.25, 0.25);
	growthCapUpLabel.setFont(font);
	growthCapUpLabel.setString("Increase\nGrowth\nCap");
	growthCapUpLabel.setPosition(144, 112);
	growthCapUpLabel.setFillColor(sf::Color(16, 16, 16));
	growthCapUpLabel.setOutlineThickness(2);
	growthCapUpLabel.setOutlineColor(faction->getColor());
	growthCapUpLabel.setScale(0.25, 0.25);
	drainUpLabel.setFont(font);
	drainUpLabel.setString("Increase\nResource\nDrain Rate");
	drainUpLabel.setPosition(188, 112);
	drainUpLabel.setFillColor(sf::Color(16, 16, 16));
	drainUpLabel.setOutlineThickness(2);
	drainUpLabel.setOutlineColor(faction->getColor());
	drainUpLabel.setScale(0.25, 0.25);
}

void Player::setupElements(){
	menu.setPosition(0, 18);
	menu.setFillColor(sf::Color(32, 32, 32));
	menu.setOutlineColor(faction->getColor());
	menu.setOutlineThickness(2);
	tab.setPosition(2, 18);
	tab.setOutlineThickness(2);
	tab.setOutlineColor(faction->getColor());
	tab.setFillColor(faction->getColor());
	upgradeOutline.setPosition(5, 61);
	upgradeOutline.setFillColor(faction->getColor());
	chooseUpgrade.setPosition(80, 80);
	chooseUpgrade.setFillColor(sf::Color(32, 32, 32));
	chooseUpgrade.setOutlineColor(faction->getColor());
	chooseUpgrade.setOutlineThickness(2);
}

void Player::update(){
	clickLogic();
	resourceLevel.setString(resourceString + std::to_string(faction->getResource()));
	growthRate->setShow(upgradeMenuQueue>0&&tabOpen);
	growthCap->setShow(upgradeMenuQueue>0&&tabOpen);
	drainSpeed->setShow(upgradeMenuQueue>0&&tabOpen);
	changeShipFraction();
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
		win::window.draw(techLevel);
		win::window.draw(resourceLevel);
		win::window.draw(nextCost);
		win::window.draw(upgradeOutline);
		if (upgradeMenuQueue){
			win::window.draw(chooseUpgrade);
			win::window.draw(growthUpLabel);
			win::window.draw(growthCapUpLabel);
			win::window.draw(drainUpLabel);
		}
	}
	win::window.draw(tab);
	win::window.draw(factionName);
}

void Player::changeShipFraction(){
	if (inp::keyPressed(sf::Keyboard::Key::Equal)){
		faction->addFraction();
		return;
	}
	if (inp::keyPressed(sf::Keyboard::Key::Hyphen)){
		faction->subFraction();
		return;
	}
}

void Player::toggleTab(){
	tabOpen = !tabOpen;
	upgrade->setShow(tabOpen);
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
	for (int i = 0;i<planetCount;++i){
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

void Player::updateMenuText(){
	techLevel.setString(techString + std::to_string(faction->getTech()));
	nextCost.setString(costString + std::to_string(faction->getCost()));
}
