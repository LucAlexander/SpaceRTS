#include "planet.h"
#include "unit.h"
#include "../e/win.h"
#include "../e/input.h"
#include "../e/entityHandler.h"
#include "../e/rnd.h"
#include "../e/textureTable.h"
#include "../e/settings.h"

#include <algorithm>
#include <string>

Planet::Planet():
	Entity(),
	rad(25),
	selected(false),
	circle(rad, 64),
	faction(nullptr),
	population(rad),
	resource(rad),
	target(nullptr),
	thickness(2),
	selectThickness(4),
	selectedColor(),
	vibranceCoef(47),
	grow(),
	drain(),
	popText(),
	resText(),
	popFont(),
	type(TYPE::POPULATION),
	textScale(0.5),
	popWeight(4)
{}

void Planet::init(){
	// SETUP AND TEXT DEFAULT
	popFont.loadFromFile("./f/FSEX300.ttf");
	popText.setFont(popFont);
	popText.setFillColor(sf::Color::White);
	popText.setOutlineThickness(2);
	popText.setScale(textScale, textScale);
	int tPosX = static_cast<int>(x+rad);
	int tPosY = static_cast<int>(y+rad);
	popText.setPosition(tPosX, tPosY+rad);
	sf::Color neutralColor;
	// TYPE SPECIFIC
	type = rnd::roll(popWeight) ? TYPE::RESOURCE : TYPE::POPULATION;
	switch(type){
		case TYPE::RESOURCE:{
			drain.set(settings::TPS*2);
			neutralColor = sf::Color(104, 104, 104);
			circle.setTexture(txtab::load("resourcePlanet.png"));
			resText.setFont(popFont);
			resText.setFillColor(sf::Color::White);
			resText.setOutlineThickness(2);
			resText.setOutlineColor(neutralColor);
			resText.setScale(textScale, textScale);
			tPosY = static_cast<int>(y+(rad*2));
			resText.setPosition(tPosX, tPosY);
			population = 0;
		}
		break;
		case TYPE::POPULATION:{
			neutralColor = sf::Color(104, 86, 12);
			circle.setTexture(txtab::load("planet.png"));
			grow.set(settings::TPS);
			resource = 0;
		}
		break;

	}
	// DEFAULT
	popText.setOutlineColor(neutralColor);
	circle.setOutlineThickness(2);
	circle.setOutlineColor(neutralColor);
	selectedColor = sf::Color::White;
	setHitbox(-8, -8, 8+(rad*2), 8+(rad*2));
}

void Planet::update(){
	if (faction != nullptr){
		// SPAWN UNITS
		if (target != nullptr){
			spawnUnits();
		}
		switch(type){
			case TYPE::POPULATION:{
				// GROW POPULATION
				if (population < (rad*2*faction->getGrowthCap())){
					if (grow.ring()){
						population++;
						grow.set(settings::TPS/faction->getGrowthRate());
						grow.reset();
					}
					grow.tick();
				}
			}
			break;
			case TYPE::RESOURCE:{
				// DRAIN RESOURCES
				if (resource > 0 && population >= resource){
					if (drain.ring()){
						resource--;
						faction->gainResource();
						drain.set(settings::TPS/faction->getDrainRate());
						drain.reset();
					}
					drain.tick();
				}
			}
			break;
		}
	}
	resText.setString(std::to_string(resource));
	popText.setString(std::to_string(population));
}
void Planet::draw(){
	circle.setPosition(x, y);
	win::window.draw(circle);
	win::window.draw(popText);
	if (type==TYPE::RESOURCE){
		win::window.draw(resText);
	}
}

void Planet::spawnUnits(){
	int targetDir = utils::pointDirection(x, y, target->getX(), target->getY());
	int offset = 8;
	int offsetInc = (offset/rad)*30;
	int offsetWiggle = 10;
	int maxRot = 120;
	int polarity = 1;
	int placeDist = rad;
	int placeOffset = 16;
	int shipLoad = population - (population / 2);
	int shipPartitionSize = 5;
	population /= 2;
	int tries = 0;
	while (shipLoad > 0){
		int popCount = std::min(shipPartitionSize, shipLoad);
		shipLoad -= popCount;
		int placeDir = (targetDir + (polarity * offset));
		int posx = x + rad + utils::lengthDirX(placeDist + placeOffset, placeDir);
		int posy = y + rad + utils::lengthDirY(placeDist + placeOffset, placeDir);
		Unit* ship = enth::create(posx, posy, Unit());
		while (enth::collides(ship, Unit())){
			ship->setX(posx + utils::lengthDirX(placeOffset, rnd::iRange(0, 11)*30));
			ship->setY(posy + utils::lengthDirY(placeOffset, rnd::iRange(0, 11)*30));
		}
		ship->setTarget(target);
		ship->setDepth(depth+1);
		ship->setFaction(faction);
		ship->setShipCount(popCount);
		offset += ((tries % 2 == 0) ? offsetInc : 0);
		polarity*=-1;
		if (offset >= maxRot){
			offset = offsetInc;
			offsetInc += offsetWiggle;
			placeDist += placeOffset;
		}
		tries ++;
	}
	target = nullptr;
}

void Planet::addPopulation(Faction* f, int pop){
	population += ((faction==f)?1:-1)*pop;
	if (population <= 0){
		population *= -1;
		setFaction(f);
	}
}

float Planet::getRadius(){
	return rad;
}

void Planet::setRadius(float r){
	setHitbox(-8, -8, 8+(r*2), 8+(r*2));
	rad = r;
	circle.setRadius(rad);
	resource = rad;
	if (type==TYPE::POPULATION){
		population = rad;
	}
	int tPosX = static_cast<int>(x+rad);
	int tPosY = static_cast<int>(y+rad);
	popText.setPosition(tPosX, tPosY);
	tPosY = static_cast<int>(y+(rad*2));
	resText.setPosition(tPosX, tPosY);
}

bool Planet::intersects(float x2, float y2, float r2){
	float x1 = x + rad;
	float y1 = y + rad;
	x2 += r2;
	y2 += r2;
	float rsq = (rad+r2);
	float xsq = (x1-x2);
	float ysq = (y1-y2);
	rsq*=rsq;
	xsq*=xsq;
	ysq*=ysq;
	return (rsq >= (xsq+ysq));
}

bool Planet::intersects(Planet* other){
	float r1 = rad;
	float r2 = other->getRadius();
	float x1 = x + r1;
	float y1 = y + r1;
	float x2 = other->getX() + r2;
	float y2 = other->getY() + r2;
	float rsq = (r1+r2);
	float xsq = (x1-x2);
	float ysq = (y1-y2);
	rsq*=rsq;
	xsq*=xsq;
	ysq*=ysq;
	return (rsq >= (xsq+ysq));
}

void Planet::toggleSelect(){
	selected = !selected;
	circle.setOutlineThickness(selected ? selectThickness : thickness);
	circle.setOutlineColor(selected ? selectedColor : faction->getColor());
}

bool Planet::getSelected()const{
	return selected;
}

void Planet::setFaction(Faction* f){
	faction = f;
	circle.setOutlineColor(faction->getColor());
	circle.setFillColor(faction->getColor());
	selectedColor = faction->getColor();
	selectedColor.r += vibranceCoef;
	selectedColor.g += vibranceCoef;
	selectedColor.b += vibranceCoef;
	popText.setOutlineColor(faction->getColor());
}

Faction* Planet::getFaction()const{
	return faction;
}

void Planet::setTarget(Planet* t){
	target = t;
}
