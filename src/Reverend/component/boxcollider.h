#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "../object/gameobject.h"
#include "boxtrigger.h"
#include "component.h"

class BoxCollider : public BoxTrigger {
public:
	void update(SDLGameObject &parent) {
		std::cout << "BoxCollider updating" << std::endl;
		if (checkCollision(parent)) {
			std::cout << "COLLISION DETECTED" << std::endl;
			// undo last movement
			parent.setPosition(parent.getPosition() - parent.getVelocity());
			parent.sendMessage(new Message(3, MessageType::CollisionEnter, &parent));
		}
	}
};

#endif