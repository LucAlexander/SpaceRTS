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

	/*template<class T>
	T* pointCollides(float x, float y, T type){
		std::vector<Entity*> mit(entityList[getTypeId(type)]);
		for (int i = 0;i<mit.size();++i){
			//TODO check hitbox collisions	
		}
		return nullptr;
	}

	template<class T>
	bool pointCollides(float x, float y, T* instance){
		// TODO point collides with passed instance
		return false;
	}*/

	int instanceCount();
	void close();
}

#endif
