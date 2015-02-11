#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "gameobject.h"

void GameObject::init(const LoaderParams& params) {
	position.x = params.x;
	position.y = params.y;
	width = params.width;
	height = params.height;
}

void GameObject::start() {
}

void GameObject::update() {
	if (!started_) {
		start();
		started_ = true;
	}
}