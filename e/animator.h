#ifndef ANIMATOR_H
#define ANIMATOR_H

#include<SFML/Graphics.hpp>

#include<unordered_map>
#include<vector>

class Animation{
public:
	Animation();
	Animation(int s, bool l = true);
	bool getLoop()const;
	void addFrame(int x, int y, int width, int height);
	sf::IntRect getNextFrame();
	void restart();
private:
	std::vector<sf::IntRect> frames;
	bool loop;
	int index;
};

class Animator{
public:
	Animator();
	Animator(sf::Sprite* spr);
	void addAnimation(std::string name, int startx, int starty, int width, int height, int frames, bool loop = true);
	void playAnimation(std::string);
	void pause();
	void resume();
private:
	std::map<std::string, Animation> animations;
	sf::Sprite* sprite;
	std::string activeAnimation;
	bool play;
};

#endif
