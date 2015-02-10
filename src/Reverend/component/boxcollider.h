#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "../gameobject.h"
#include "boxtrigger.h"
#include "component.h"

class BoxCollider : public BoxTrigger {
public:
	
	BoxCollider(SDLGameObject& parent, int x, int y, int w, int h);

	virtual void update();
	virtual void receiveMessage(Message* m);

};

#endif