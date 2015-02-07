#include "objectlayer.h"
#include <iostream>

void ObjectLayer::add(GameObject* o) {
	gameObjects_.push_back(o);
}

void ObjectLayer::update() {
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->update();
	}
}

void ObjectLayer::draw() {
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->draw();
	}
}

void ObjectLayer::clean() {
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->clean();
	}
	gameObjects_.clear();
}