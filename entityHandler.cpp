#include "entityHandler.h"

#include <typeinfo>

std::map<std::string, std::vector<Entity*>> enth::entityList;
int enth::count = 0;

int enth::instanceCount(){
	return count;
}

void enth::close(){
	for (auto mit : entityList){
		for (auto vit = mit.second.begin();vit < mit.second.end();++vit){
			delete *vit;
			mit.second.erase(vit);
		}
	}
}
