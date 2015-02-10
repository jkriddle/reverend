#pragma once
#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H

#include "../gameobject.h"
#include "component.h"
#include "../physicssystem.h"

class BoxTrigger : public Component {
public:
	BoxTrigger(GameObject& parent) : Component(parent) {}
	
	virtual void update();
	virtual void receiveMessage(Message* m);

	GameRect getBounds() { return boundingBox_; }

protected:
	GameRect boundingBox_;
};

#endif