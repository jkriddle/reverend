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
		position_ = target_->position;
	}

	virtual void receiveMessage(Message* message) {
	}

private:
	GameObject* target_;
	Vector2d position_;
};

#endif