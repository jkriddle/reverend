#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "message.h"
#include <iostream>
class GameObject;

class Component {
public:
	virtual void update(GameObject& o) = 0;
	virtual void receiveMessage(Message* message) {
		std::cout << "BoxCollider received message " << message->getMessageType() << " from #" << message->getDestinationObjectId() << std::endl;
	}
};

#endif;