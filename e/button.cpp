#include "button.h"

#include "../e/win.h"
#include "../e/input.h"
#include "../e/entityHandler.h"

Button::Button():
	Entity(),
	actionCode([](){}),
	show(true),
	guiX(0),
	guiY(0)
{}

void Button::init(){
	guiX = x;
	guiY = y;
}

void Button::update(){
	if (inp::mousePressed(sf::Mouse::Button::Left)){
		if (enth::pointCollides(inp::mouseX(), inp::mouseY(), this)){
			activate();
		}
	}
}

void Button::draw(){}

void Button::drawGui(){
	if (show){
		sf::Vector2f frame = win::window.mapPixelToCoords(sf::Vector2i(guiX, guiY));
		x = frame.x;
		y = frame.y;
		sprite.setPosition(x, y);
		win::window.draw(sprite);
	}
}

void Button::activate(){
	actionCode();
}

void Button::setAction(std::function<void()> code){
	actionCode = code;
}

void Button::setShow(bool s){
	show = s;
}

void Button::setGuiPosition(float xx, float yy){
	guiX = xx;
	guiY = yy;
}
