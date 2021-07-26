#ifndef PLAYER_H
#define PLAYER_H

#include "../e/entity.h"

class Player : public Entity{
public:
	Player();
	void update();
	std::string getFactionName();
private:
	std::string faction;
};

#endif
