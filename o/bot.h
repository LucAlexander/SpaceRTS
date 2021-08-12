#ifndef BOT_H
#define BOT_H

#include "../e/entity.h"
#include "../e/alarm.h"
#include "faction.h"

class Bot : public Entity{
public:
	Bot();
	void init();
	void update();
	void setDifficulty(int d);
	void setFaction(Faction* f);
	Faction* getFaction()const;
private:
	Faction* faction;
	int actionTime;
	Alarm actionTimer;
	enum ACTION{
		IDLE,
		FORTIFY,
		SPREAD,
		UPGRADE,
		ATTACK
	};
	ACTION actionType;
	int difficulty;
	void behaviorEasy();
	void performAction();
};

#endif
