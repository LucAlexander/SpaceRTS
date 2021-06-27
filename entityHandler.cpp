#include "entityHandler.h"

#include <typeinfo>

std::map<std::string, std::vector<Entity*>> enth::entityList;

void enth::close(){
	for (auto mit : entityList){
		for (auto vit : mit.second){
			delete vit;
		}
	}
}
