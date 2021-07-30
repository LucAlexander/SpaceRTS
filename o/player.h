#ifndef PLAYER_H
#define PLAYER_H

#include "../e/entity.h"
#include "../e/utils.h"
#include "faction.h"
#include "planet.h"

class Player : public Entity{
public:
	Player();
	void init();
	void update();
	void draw();
	Faction* getFaction()const;
	void setFactionName(std::string name);
private:
	Faction* faction;
	utils::Rect selectRect;
	void clickLogic();
	void boundSelectPlanets();
	void planetClickLogic(Planet* instance);
	void setTarget(Planet* instance);
	void deselectPlanets();
};

#endif
