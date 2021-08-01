#include "input.h"
#include "win.h"
#include "utils.h"

std::map<sf::Keyboard::Key,bool> inp::heldKeys;
std::map<sf::Keyboard::Key,bool> inp::pressedKeys;
std::map<sf::Keyboard::Key,bool> inp::releasedKeys;

std::map<sf::Mouse::Button,bool> inp::heldMB;
std::map<sf::Mouse::Button,bool> inp::pressedMB;
std::map<sf::Mouse::Button,bool> inp::releasedMB;

int inp::scrollDir = 0;

void inp::newFrame(){
	pressedKeys.clear();
	releasedKeys.clear();
	pressedMB.clear();
	releasedMB.clear();
	scrollDir = 0;
}

float inp::mouseX(){
	return win::window.mapPixelToCoords(sf::Vector2i(guiMouseX(), guiMouseY())).x;
}

float inp::mouseY(){
	return win::window.mapPixelToCoords(sf::Vector2i(guiMouseX(), guiMouseY())).y;
}

float inp::guiMouseX(){
	return sf::Mouse::getPosition(win::window).x;
}

float inp::guiMouseY(){
	return sf::Mouse::getPosition(win::window).y;
}

void inp::keyDownEvent(sf::Keyboard::Key k){
	if (!heldKeys[k]){
		pressedKeys[k] = true;
	}
	heldKeys[k] = true;
}

void inp::keyUpEvent(sf::Keyboard::Key k){
	releasedKeys[k] = true;
	heldKeys[k] = false;
}

void inp::mouseDownEvent(sf::Mouse::Button b){
	if (!heldMB[b]){
		pressedMB[b] = true;
	}
	heldMB[b] = true;
}

void inp::mouseUpEvent(sf::Mouse::Button b){
	releasedMB[b] = true;
	heldMB[b] = false;
}

void inp::mouseScrollEvent(int delta){
	scrollDir = delta;
}

bool inp::keyPressed(sf::Keyboard::Key k){
	return pressedKeys[k];
}

bool inp::keyReleased(sf::Keyboard::Key k){
	return releasedKeys[k];
}

bool inp::keyHeld(sf::Keyboard::Key k){
	return heldKeys[k];
}

bool inp::mousePressed(sf::Mouse::Button b){
	return pressedMB[b];
}

bool inp::mouseReleased(sf::Mouse::Button b){
	return releasedMB[b];
}

bool inp::mouseHeld(sf::Mouse::Button b){
	return heldMB[b];
}

bool inp::mouseScroll(int d){
	return utils::sign(d)==utils::sign(scrollDir);
}

int inp::mouseScroll(){
	return utils::sign(scrollDir);
}
