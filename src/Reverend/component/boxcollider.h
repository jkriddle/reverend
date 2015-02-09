#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "../object/gameobject.h"
#include "boxtrigger.h"
#include "component.h"

class BoxCollider : public BoxTrigger {
public:
	
	BoxCollider(int x, int y, int w, int h) : BoxTrigger(x, y, w, h) {
	}

	virtual void update(SDLGameObject &parent) {
		boundingBox_.setPosition(parent.getX(), parent.getY());
		for(SDLGameObject* o : ObjectFactory::getObjects()) {
			if (&parent == o) continue;
			BoxCollider* pCollider = parent.getComponent<BoxCollider>();
			BoxCollider* oCollider = o->getComponent<BoxCollider>();
			if (pCollider != nullptr && oCollider != nullptr) {
				if (PhysicsSystem::checkCollision(pCollider->getBounds(), oCollider->getBounds())) {
					// collision detected
					Vector2d newPos = parent.getPosition() - parent.getVelocity();
					parent.setPosition(newPos);
					parent.setVelocity(Vector2d::ZERO);
					parent.setAcceleration(Vector2d::ZERO);
					parent.sendMessage(new Message(3, MessageType::CollisionEnter, &parent));
				}
			}
		}
	}
};

#endif