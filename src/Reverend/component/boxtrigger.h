#pragma once
#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H

#include "../object/sdlgameobject.h"
#include "../object/objectfactory.h"
#include "component.h"

class BoxTrigger : public Component {
public:
	void update(SDLGameObject &parent) {
		std::cout << "BoxTrigger updating.. NEED TO IMLPEMENT ACTUAL COLLISION DETECTION" << std::endl;
		if (checkCollision(parent)) {
			std::cout << "TRIGGER DETECTED" << std::endl;
		}
	}
protected:
	bool checkCollision(SDLGameObject &parent) {
		// iterator->first = key
		// iterator->second = value
		// Repeat if you also want to iterate through the second map.
		if (parent.getX() > 9500) {
			parent.sendMessage(new Message(3, MessageType::TriggerEnter, &parent));
			return true;
		}

		return false;
	}
};

#endif