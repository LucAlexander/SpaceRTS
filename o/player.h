#ifndef PLAYER_H
#define PLAYER_H

#include "../e/entity.h"
#include "../e/utils.h"
#include "../e/button.h"
#include "faction.h"
#include "planet.h"

class Player : public Entity{
public:
	Player();
	void init();
	void update();
	void draw();
	void drawGui();
	Faction* getFaction()const;
	void setFactionName(std::string name);
	void toggleTab();
private:
	Faction* faction;
	utils::Rect selectRect;
	float zoomCoef;
	float cameraOriginX;
	float cameraOriginY;
	Button* menuTab;
	Button* upgrade;
	sf::RectangleShape menu;
	sf::RectangleShape tab;
	sf::Text factionName;
	sf::Text techLevel;
	sf::Text resourceLevel;
	sf::Text nextCost;
	sf::Font font;
	bool tabOpen;
	void clickLogic();
	void boundSelectPlanets();
	void planetClickLogic(Planet* instance);
	void setTarget(Planet* instance);
	void deselectPlanets();
	void cameraPositionUpdate();
	void cameraZoomUpdate();
	void updateMenuText();
};

#endif
