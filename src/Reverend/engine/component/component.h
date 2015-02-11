#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "message.h"
#include <iostream>
class GameObject;

class Component {
public:
	virtual void update() {
		if (!started_) {
			start();
			started_ = true;
		}
	}
	virtual void receiveMessage(Message* message) {}
	virtual void start() {}
protected:

	Component(GameObject& parent) {
		parent_ = &parent;
		started_ = false;
	}

	GameObject* parent_;
	bool started_;

private:
};

#endif;