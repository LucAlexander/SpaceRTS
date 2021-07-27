#ifndef PLAYER_H
#define PLAYER_H

#include "../e/entity.h"
#include "faction.h"

class Player : public Entity{
public:
	Player();
	void init();
	void update();
	Faction* getFaction()const;
	void setFactionName(std::string name);
private:
	Faction* faction;
};

#endif
