#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "gameobject.h"

class Camera  {

public:
	Camera(int width, int height) : width_(width), height_(height) {
	}

	void setTarget(GameObject* t) {
		target = t;
	}

	Vector2d translate(int x, int y) {
		if (target == nullptr) {
			return Vector2d::ZERO;
		}

		int tX = x - target->position.x + (int)(width_ / 2) - (int)(target->width / 2);
		int tY = y - target->position.y  + (int)(height_ / 2) -  (int)(target->height / 2);
		return Vector2d((float)tX, (float)tY);
	}
	
	int getWidth() { return width_; }
	int getHeight() { return height_; }

	GameObject* target;
private:
	int width_;
	int height_;
};


class CameraManager  {

public:
	static Camera* getMain() {
		return mainCamera;
	}
	static void cleanup(){
		delete mainCamera;
		mainCamera = NULL;
	}
	static Camera* mainCamera;
};

#endif