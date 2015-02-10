#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "../object.h"
#include "boxtrigger.h"
#include "component.h"

class BoxCollider : public BoxTrigger {
public:
	
	BoxCollider(GameObject& parent) : BoxTrigger(parent) {}

	virtual void update();
	virtual void receiveMessage(Message* m);

};

#endif