#ifndef FACTION_H
#define FACTION_H

#include "../e/entity.h"
#include <SFML/Graphics.hpp>

class Faction : public Entity{
public:
	Faction();
	void init();
	void setName(std::string);
	std::string getName()const;
	sf::Color getColor()const;
	int operator==(Faction a);
	void gainResource();
	void tryUpgrade();
	int getTech()const;
	int getResource()const;
	int getCost()const;
	int getGrowthRate()const;
	int getDrainRate()const;
	float getGrowthCap()const;	
	void upgradeGrowthRate();
	void upgradeGrowthCap();
	void upgradeDrainRate();
private:
	std::string name;
	sf::Color col;
	bool isUniqueName(std::string n);
	sf::Color generateColor();
	int resource;
	int tech;
	int techCostIncrement;
	int techCostIncrementChange;
	int techCost;
	int growthRate;
	int drainRate;
	float growthCap;
};

#endif
