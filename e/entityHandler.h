#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H

#include "entity.h"
#include "utils.h"

#include <map>
#include <vector>

namespace enth{
	extern std::map<std::string, std::vector<Entity*>> entityList;
	extern int count;

	template<class T>
	T* create(float xx, float yy, T){
		T* instance = new T();
		instance->setPosition(xx, yy);
		entityList[typeid(instance).name()].push_back(instance);
		count++;
		return instance;
	}

	template<class T>
	void destroy(T* instance){
		std::string tid = typeid(instance).name();
		for (auto vid = entityList[tid].begin();vid < entityList[tid].end();++vid){
			if (*vid == instance){
				delete *vid;
				entityList[tid].erase(vid);
				count--;
			}
		}
	}

	template<class T>
	std::string getTypeId(T){
		return typeid(T*).name();
	}

	template<class T>
	std::string getTypeId(T*){
		return typeid(T*).name();
	}

	template<class T>
	bool exists(T){
		return (entityList[getTypeId(T())].size() > 0);
	}

	template<class T>
	bool exists(T*){
		return (entityList[getTypeId(T())].size() > 0);
	}

	template<class T>
	int number(T){
		return entityList[getTypeId(T())].size();
	}

	template<class T>
	int number(T*){
		return entityList.count[getTypeId(T())].size();
	}

	template<class T, class C>
	T* nearest(C* instance, T type, int n = 1){
		std::vector<Entity*> mit(entityList[getTypeId(type)]);
		Entity* other = nullptr;
		int shortest = -1;
		while (n>0){
			for (int i = 0;i<mit.size();++i){
				if (mit[i] != instance){
					int dist = utils::distancePoint(instance->getX(), instance->getY(), mit[i]->getX(), mit[i]->getY());
					if (shortest == -1 || dist < shortest){
						other = mit[i];
						shortest = i;
					}
				}
			}
			if (shortest != -1){
				mit.erase(mit.begin()+shortest);
			}
			n--;
		}
		if (instance == other){
			return nullptr;
		}
		return static_cast<T*>(other);
	}
	
	template<class T>
	T* nearest(float x, float y, T type, int n = 1){
		Entity* other = nullptr;
		int shortest = -1;
		std::vector<Entity*> mit(entityList[getTypeId(type)]);
		while(n > 0){
			for (int i = 0;i<mit.size();++i){
				int dist = utils::distancePoint(x, y, mit[i]->getX(), mit[i]->getY());
				if (shortest == -1 || dist < shortest){
					other = mit[i];
					shortest = i;
				}
			}
			if (shortest != -1){
				mit.erase(mit.begin()+shortest);
			}
			n--;
		}
		return static_cast<T*>(other);
	}
	
	template<class T, class C>
	T* furthest(C* instance, T type, int n = 1){
		std::vector<Entity*> mit(entityList[getTypeId(type)]);
		Entity* other = nullptr;
		int longest = -1;
		while (n>0){
			for (int i = 0;i<mit.size();++i){
				if (mit[i] != instance){
					int dist = utils::distancePoint(instance->getX(), instance->getY(), mit[i]->getX(), mit[i]->getY());
					if (longest == -1 || dist > longest){
						other = mit[i];
						longest = i;
					}
				}
			}
			if (longest != -1){
				mit.erase(mit.begin()+longest);
			}
			n--;
		}
		if (instance == other){
			return nullptr;
		}
		return static_cast<T*>(other);
	}
	
	template<class T>
	T* furthest(float x, float y, T type, int n = 1){
		Entity* other = nullptr;
		int longest = -1;
		std::vector<Entity*> mit(entityList[getTypeId(type)]);
		while(n > 0){
			for (int i = 0;i<mit.size();++i){
				int dist = utils::distancePoint(x, y, mit[i]->getX(), mit[i]->getY());
				if (longest == -1 || dist > longest){
					other = mit[i];
					longest = i;
				}
			}
			if (longest != -1){
				mit.erase(mit.begin()+longest);
			}
			n--;
		}
		return static_cast<T*>(other);
	}
	
	template<class T>
	bool pointCollides(float x, float y, T* instance){
		utils::Rect hb = instance->getGlobalHitbox();
		return utils::pointInRect(utils::v2(x, y), hb);
	}


	template<class T>
	T* pointCollides(float x, float y, T type){
		std::vector<Entity*> mit(entityList[getTypeId(type)]);
		for (int i = 0;i<mit.size();++i){
			if (pointCollides(x, y, mit[i])){
				return static_cast<T*>(mit[i]);
			}
		}
		return nullptr;
	}

	template<class T, class C>
	bool collides(C* instance, T* other, float xoff=0, float yoff=0){
		utils::Rect ihb = instance->getGlobalHitbox();
		ihb.start.x += xoff;
		ihb.end.x += xoff;
		ihb.start.y += yoff;
		ihb.end.y += yoff;
		utils::Rect ohb = other->getGlobalHitbox();
		utils::v2 bl(ihb.start.x, ihb.end.y);
		utils::v2 tr(ihb.end.x, ihb.start.y);
		return utils::pointInRect(ihb.start, ohb) || 
			utils::pointInRect(ihb.end, ohb) ||
			utils::pointInRect(bl, ohb) ||
			utils::pointInRect(tr, ohb);
	}
	
	template<class T, class C>
	T* collides(C* instance, T type, float xoff=0, float yoff=0){
		std::vector<Entity*> mit(entityList[getTypeId(type)]);
		for (int i = 0;i<mit.size();++i){
			T* other = static_cast<T*>(mit[i]);
			if (instance != other){
				if (collides(instance, other, xoff, yoff)){
					return other;
				}
			}
		}
		return nullptr;
	}

	int instanceCount();
	void close();
}

#endif
