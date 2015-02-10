#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "message.h"
#include <iostream>
class SDLGameObject;

class Component {
public:
	virtual void update() = 0;
	virtual void receiveMessage(Message* message) = 0;

protected:

	Component(SDLGameObject& parent) {
		parent_ = &parent;
	}

	SDLGameObject* parent_;

private:
};

#endif;