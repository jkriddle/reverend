#pragma once
#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H

#include "../object/gameobject.h"
#include "component.h"

class BoxTrigger : public Component {
public:
	virtual void update(GameObject &parent) {
		std::cout << "BoxCollider updating.. NEED TO IMLPEMENT ACTUAL COLLISION DETECTION" << std::endl;
		if (checkCollision(parent)) {
			std::cout << "TRIGGER DETECTED" << std::endl;
		}

		/*if (parent.x > 5) {
			std::cout << "TRIGGER DETECTED" << std::endl;
			parent.sendMessage(new Message(3, MessageType::CollisionEnter, &parent));
		}*/

	}
protected:
	bool checkCollision(GameObject &parent) {
	}
};

#endif