#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SFML/Graphics.hpp>

namespace inp{
	extern std::map<sf::Keyboard::Key,bool> heldKeys;
	extern std::map<sf::Keyboard::Key,bool> pressedKeys;
	extern std::map<sf::Keyboard::Key,bool> releasedKeys;
	
	extern std::map<sf::Mouse::Button,bool> heldMB;
	extern std::map<sf::Mouse::Button,bool> pressedMB;
	extern std::map<sf::Mouse::Button,bool> releasedMB;

	extern int scrollDir;

	void newFrame();

	float mouseX();
	float mouseY();
	float guiMouseX();
	float guiMouseY();

	void keyDownEvent(sf::Keyboard::Key);
	void keyUpEvent(sf::Keyboard::Key);

	void mouseDownEvent(sf::Mouse::Button);
	void mouseUpEvent(sf::Mouse::Button);
	void mouseScrollEvent(int delta);

	bool keyPressed(sf::Keyboard::Key);
	bool keyReleased(sf::Keyboard::Key);
	bool keyHeld(sf::Keyboard::Key);

	bool mousePressed(sf::Mouse::Button);
	bool mouseReleased(sf::Mouse::Button);
	bool mouseHeld(sf::Mouse::Button);
	bool mouseScroll(int delta);
	int mouseScroll();
}

#endif
