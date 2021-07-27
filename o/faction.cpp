#include "faction.h"
#include "nationGenerator.h"
#include "../e/entityHandler.h"

Faction::Faction():
	Entity(),
	name("")
{}

void Faction::init(){
	if (enth::exists(NationGenerator())){
		do{
			name = enth::get(NationGenerator())->generate("chinese");
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

std::string Faction::getName()const{
	return name;
}

void Faction::setName(std::string n){
	name = n;
}

