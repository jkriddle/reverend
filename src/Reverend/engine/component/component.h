#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "message.h"
#include <iostream>
class GameObject;

class Component {
public:
	virtual void update() = 0;
	virtual void receiveMessage(Message* message) = 0;

protected:

	Component(GameObject& parent) {
		parent_ = &parent;
	}

	GameObject* parent_;

private:
};

#endif;