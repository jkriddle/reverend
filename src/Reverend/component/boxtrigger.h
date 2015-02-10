#pragma once
#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H

#include "../sdlgameobject.h"
#include "../entities/objectfactory.h"
#include "component.h"
#include "../physicssystem.h"

class BoxTrigger : public Component {
public:
	BoxTrigger(SDLGameObject& parent, int x, int y, int w, int h);
	
	virtual void update();
	virtual void receiveMessage(Message* m);

	GameRect getBounds() { return boundingBox_; }

protected:
	GameRect boundingBox_;
};

#endif