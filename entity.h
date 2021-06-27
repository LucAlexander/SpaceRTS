#ifndef ENTITY_H
#define ENTITY_H

class Entity{
public:
	Entity();
	virtual ~Entity();
	virtual void update();
	virtual void draw();
	virtual void drawGui();
protected:
};

#endif
