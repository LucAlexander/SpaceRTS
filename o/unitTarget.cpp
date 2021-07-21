#include "unitTarget.h"
#include "../e/utils.h"
#include "../e/entityHandler.h"
#include "../e/rnd.h"
#include "../e/input.h"

#include <SFML/Graphics.hpp>

UnitTarget::UnitTarget():
	Entity()
{}

void UnitTarget::update(){
	if (inp::keyPressed(sf::Keyboard::N)){
		x = rnd::iRange(0, 32)*32;
		y = rnd::iRange(0, 32)*32;
	}
}
