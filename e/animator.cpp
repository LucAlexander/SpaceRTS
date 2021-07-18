#include "animator.h"
#include <iostream>

Animation::Animation():
	Animation(0, true)
{}

Animation::Animation(int s, bool l):
	frames(s, sf::IntRect()),
	loop(l),
	index(0)
{
}

bool Animation::getLoop()const{
	return loop;
}

void Animation::addFrame(int x, int y, int width, int height){
	frames[index++] = sf::IntRect(x, y, width, height);
}

sf::IntRect Animation::getNextFrame(){
	if (index == frames.size()){
		index--;
		if (loop){
			restart();
		}
	}
	return frames[index++];
}

void Animation::restart(){
	index = 0;
}

Animator::Animator():
	Animator(nullptr)
{}

Animator::Animator(sf::Sprite* spr):
	sprite(spr),
	activeAnimation(""),
	play(true)
{}

void Animator::addAnimation(std::string name, int startx, int starty, int width, int height, int frameCount, bool loop){
	if (sprite != nullptr){
		const sf::Texture* t = sprite->getTexture();
		if (t != nullptr){
			int tWidth = (t->getSize().x/width)-1;
			int tHeight = (t->getSize().y/height)-1;
			Animation anim(frameCount, loop);
			int shift = 0;
			int pos = 0;
			for (int i = 0;i<frameCount&&shift<=tHeight;++i){
				anim.addFrame(startx+(width*pos), starty+(height*shift), width, height);
				if (pos==tWidth){
					pos = -1;
					shift++;
				}
				pos++;
			}
			anim.restart();
			animations[name] = anim;
		}
	}
}

void Animator::playAnimation(std::string name){
	if (animations.count(name)!=0){
		if (name != activeAnimation){
			animations[name].restart();
			activeAnimation = name;
		}
		if (play){
			sprite->setTextureRect(animations[activeAnimation].getNextFrame());
		}
	}
}

void Animator::pause(){
	play = true;
}

void Animator::resume(){
	play = false;
}
