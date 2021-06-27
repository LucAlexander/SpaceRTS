#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H

#include "entity.h"
#include "utils.h"

#include <map>
#include <vector>

namespace enth{
	extern std::map<std::string, std::vector<Entity*>> entityList;
	
	template<class T>
	T* instanceCreate(T){
		T* instance = new T();
		entityList[typeid(instance).name()].push_back(instance);
		return instance;
	}
	void close();

}

#endif
