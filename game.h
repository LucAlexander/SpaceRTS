#ifndef GAME_H
#define GAME_H

#include <functional>
#include <SFML/Graphics.hpp>

class Game{
public:
	Game();
	Game(const char* title);
	void setInitCode(std::function<void()> code);
	void loop();
	void close();
private:
	void update();
	void draw();
	sf::Clock clock;
	sf::Int32 elapsedTime;
	int frameTime;
	std::function<void()> initCode;
};

#endif
