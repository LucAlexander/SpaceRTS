#include "planet.h"
#include "unit.h"
#include "../e/win.h"
#include "../e/input.h"
#include "../e/entityHandler.h"
#include "../e/rnd.h"
#include "../e/textureTable.h"

#include <algorithm>

Planet::Planet():
	Entity(),
	rad(25),
	selected(false),
	circle(rad, 64),
	faction(nullptr),
	population(rad),
	target(nullptr),
	thickness(2),
	selectThickness(4),
	selectedColor(),
	vibranceCoef(47)
{}

void Planet::init(){
	circle.setOutlineThickness(2);
	circle.setOutlineColor(sf::Color::White);
	circle.setTexture(txtab::load("planet.png"));
	selectedColor = sf::Color::White;
	setHitbox(0, 0, rad*2, rad*2);
}

void Planet::update(){
	if (target != nullptr){
		spawnUnits();
	}
	//TODO alarm to increment population
	//population caps at diameter
}

void Planet::draw(){
	circle.setPosition(x, y);
	win::window.draw(circle);
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
	int shipPartitionSize = 1;
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
			ship->setX(utils::lengthDirX(1, placeDir));
			ship->setY(utils::lengthDirY(1, placeDir));
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
	setHitbox(0, 0, r*2, r*2);
	rad = r;
	circle.setRadius(rad);
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
	selectedColor = faction->getColor();
	selectedColor.r += vibranceCoef;
	selectedColor.g += vibranceCoef;
	selectedColor.b += vibranceCoef;
}

Faction* Planet::getFaction()const{
	return faction;
}

void Planet::setTarget(Planet* t){
	target = t;
}
