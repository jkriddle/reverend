#pragma once
#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H

#include "../gameobject.h"
#include "component.h"
#include "../physics.h"

class BoxTrigger : public Component {
public:
	BoxTrigger(GameObject* parent) : position(parent->position.x, parent->position.y, parent->width, parent->height), Component(parent) {}
	
	virtual void update();
	virtual void receiveMessage(Message* m);
	GameRect getBounds() { return GameRect(position.x + offset.x, position.y + offset.y, offset.w, offset.h); }
	GameRect position;
	GameRect offset;

protected:
};

#endif