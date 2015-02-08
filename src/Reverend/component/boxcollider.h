#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "../object/gameobject.h"
#include "boxtrigger.h"
#include "component.h"

class BoxCollisder : public BoxTrigger {
public:
	virtual void update(GameObject &parent) {
		std::cout << "BoxCollider updating" << std::endl;
		if (checkCollision(parent)) {
			std::cout << "COLLISION DETECTED" << std::endl;
			parent.sendMessage(new Message(3, MessageType::CollisionEnter, &parent));
		}
	}
};

#endif