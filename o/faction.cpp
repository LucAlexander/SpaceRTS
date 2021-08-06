#include "faction.h"
#include "nationGenerator.h"
#include "../e/entityHandler.h"
#include "../e/rnd.h"

Faction::Faction():
	Entity(),
	name(""),
	col(255, 255, 255),
	resource(0),
	tech(1),
	techCostIncrement(10),
	techCostIncrementChange(5),
	techCost(25)
{}

void Faction::init(){
	col = generateColor();
	if (enth::exists(NationGenerator())){
		do{
			name = enth::get(NationGenerator())->generate("portuguese");
		}
		while(!isUniqueName(name));
	}
}

bool Faction::isUniqueName(std::string n){
	int count = enth::number(Faction());
	for (int i =0;i<count;++i){
		Faction* instance = enth::get(Faction(), i);
		if (instance != this){
			if (instance->getName() == n){
				return false;
			}
		}
	}
	return true;
}
	
sf::Color Faction::generateColor(){
	int red, green, blue;
	int vibrant = rnd::iRange(0, 2);
	switch(vibrant){
		case 0:
			red = (rnd::iRange(10, 11) * 16) + rnd::iRange(0, 16);
			green = (rnd::iRange(0, 5) * 16) + rnd::iRange(0, 16);
			blue = (rnd::iRange(0, 5) * 16) + rnd::iRange(0, 16);
		break;
		case 1:
			green = (rnd::iRange(10, 11) * 16) + rnd::iRange(0, 16);
			red = (rnd::iRange(0, 5) * 16) + rnd::iRange(0, 16);
			blue = (rnd::iRange(0, 5) * 16) + rnd::iRange(0, 16);

		break;
		case 2:
			blue = (rnd::iRange(10, 11) * 16) + rnd::iRange(0, 16);
			green = (rnd::iRange(0, 5) * 16) + rnd::iRange(0, 16);
			red = (rnd::iRange(0, 5) * 16) + rnd::iRange(0, 16);

		break;
	}
	return sf::Color(red, green, blue);
}

int Faction::operator==(Faction a){
	return a.getName()==name;
}

sf::Color Faction::getColor()const{
	return col;
}

std::string Faction::getName()const{
	return name;
}

void Faction::setName(std::string n){
	name = n;
}

void Faction::gainResource(){
	resource++;
}

void Faction::tryUpgrade(){
	 if(resource >=techCost){
	 	resource -= techCost;
		techCost += techCostIncrement;
		techCostIncrement += techCostIncrementChange;
		tech++;
	 }
}

int Faction::getTech()const{
	return tech;
}

int Faction::getResource()const{
	return resource;
}

int Faction::getCost()const{
	return techCost;
}

