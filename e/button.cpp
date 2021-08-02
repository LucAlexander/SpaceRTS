#include "button.h"

#include "../e/win.h"
#include "../e/input.h"
#include "../e/entityHandler.h"

Button::Button():
	Entity(),
	actionCode([](){}),
	show(true)
{}

void Button::update(){
	if (inp::mousePressed(sf::Mouse::Button::Left)){
		if (utils::pointInRect(utils::v2(inp::guiMouseX(), inp::guiMouseY()), getGlobalHitbox())){
			activate();
		}
	}
}

void Button::draw(){}

void Button::drawGui(){
	if (show){
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
