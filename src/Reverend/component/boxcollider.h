#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "../object/gameobject.h"
#include "boxtrigger.h"
#include "component.h"

class BoxCollider : public Component {
public:
	virtual void update(SDLGameObject &parent) {
		std::cout << "BoxCollider updating" << std::endl;
		for(SDLGameObject* o : ObjectFactory::getObjects()) {
			if (PhysicsSystem::checkCollision(parent, *o)) {
				// collision detected
				Vector2d newPos = parent.getPosition() - parent.getVelocity();
				parent.setPosition(newPos);
				parent.setVelocity(Vector2d::ZERO);
				parent.setAcceleration(Vector2d::ZERO);
				parent.sendMessage(new Message(3, MessageType::CollisionEnter, &parent));
			}
		}
	}

	virtual void receiveMessage(Message* m) {
		//std::cout << "Box Collider received message" << std::endl;
	}
};

#endif