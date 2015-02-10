#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "../gameobject.h"
#include "component.h"

class CameraComponent : public Component {

public:
	CameraComponent(GameObject& parent, GameObject* target) : target_(target), Component(parent) {
	}

	virtual void update() {
		if (target_ == nullptr) return;
		position_->set((float)target_->getX(), (float)target_->getY());
	}

	virtual void receiveMessage(Message* message) {
	}

private:
	GameObject* target_;
	Vector2d* position_;
};

#endif