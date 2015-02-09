#pragma once
#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H

#include "../object/sdlgameobject.h"
#include "../object/objectfactory.h"
#include "component.h"
#include "../physicssystem.h"

class BoxTrigger : public Component {
public:
	BoxTrigger(int x, int y, int w, int h) : boundingBox_(x, y, w, h) {
	}

	GameRect getBounds() { return boundingBox_; }

	void update(SDLGameObject &parent) {
		boundingBox_.setPosition(parent.getX(), parent.getY());
		for(SDLGameObject* o : ObjectFactory::getObjects()) {
			if (&parent == o) continue;
			BoxTrigger* pTrigger = parent.getComponent<BoxTrigger>();
			BoxTrigger* oTrigger = o->getComponent<BoxTrigger>();
			if (pTrigger != nullptr && oTrigger != nullptr) {
				if (PhysicsSystem::checkCollision(pTrigger->getBounds(), oTrigger->getBounds())) {
					// trigger entry detected
					parent.sendMessage(new Message(3, MessageType::TriggerEnter, &parent));
				}
			}
		}
	}
	
	virtual void receiveMessage(Message* m) {
		//std::cout << "Box Collider received message" << std::endl;
	}

protected:
	GameRect boundingBox_;
};

#endif