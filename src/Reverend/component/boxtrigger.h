#pragma once
#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H

#include "../object/sdlgameobject.h"
#include "../object/objectfactory.h"
#include "component.h"
#include "../physicssystem.h"

class BoxTrigger : public Component {
public:
	void update(SDLGameObject &parent) {
		std::cout << "BoxTrigger updating.. NEED TO IMLPEMENT ACTUAL COLLISION DETECTION" << std::endl;
		for(SDLGameObject* o : ObjectFactory::getObjects()) {
			if (PhysicsSystem::checkCollision(parent, *o)) {
				parent.sendMessage(new Message(3, MessageType::TriggerEnter, &parent));
				std::cout << "TRIGGER DETECTED" << std::endl;
			}
		}
	}
	
	virtual void receiveMessage(Message* m) {
		//std::cout << "Box Collider received message" << std::endl;
	}

protected:

};

#endif