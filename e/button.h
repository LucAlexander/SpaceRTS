#ifndef BUTTON_H
#define BUTTON_H

#include "entity.h"
#include <functional>

class Button : public Entity{
public:
	Button();
	void update();
	void draw();
	void drawGui();
	void setAction(std::function<void()> code);
	void activate();
	void setShow(bool s);
private:
	std::function<void()> actionCode;
	bool show;
	int guiX;
	int guiY;
};

#endif
