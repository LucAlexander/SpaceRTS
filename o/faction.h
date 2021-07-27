#ifndef FACTION_H
#define FACTION_H

#include "../e/entity.h"

class Faction : public Entity{
public:
	Faction();
	void init();
	void setName(std::string);
	std::string getName()const;
private:
	std::string name;
	bool isUniqueName(std::string n);
};

#endif
