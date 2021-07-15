#include "unitTarget.h"
#include "../e/utils.h"
#include "../e/entityHandler.h"
#include "../e/rnd.h"

#include <SFML/Graphics.hpp>

UnitTarget::UnitTarget():
	Entity()
{}

void UnitTarget::update(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
		sprite.setPosition(rnd::iRange(0, 32)*32, rnd::iRange(0, 32)*32);
	}
}