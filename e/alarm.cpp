#include "alarm.h"

Alarm::Alarm():
	Alarm(-1)
{}

Alarm::Alarm(int t):
	time(t),
	resetTime(t)
{}

void Alarm::tick(){
	if (time > STATE::INACTIVE){
		time--;
	}
}

bool Alarm::ring(){
	return time==STATE::RING;
}

bool Alarm::active(){
	return time > STATE::INACTIVE;
}

void Alarm::reset(){
	time = resetTime;
}

void Alarm::set(int t){
	time = t;
	resetTime = t;
}
