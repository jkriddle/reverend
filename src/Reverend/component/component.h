#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "message.h"
#include <iostream>
class SDLGameObject;

class Component {
public:
	virtual void update(SDLGameObject& o) = 0;
	virtual void receiveMessage(Message* message) {
		std::cout << "BoxCollider received message " << message->getMessageType() << " from #" << message->getDestinationObjectId() << std::endl;
	}
};

#endif;