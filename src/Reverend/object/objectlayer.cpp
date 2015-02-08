#include "objectlayer.h"
#include <iostream>

void ObjectLayer::add(SDLGameObject* o) {
	gameObjects_.push_back(o);
}

void ObjectLayer::update() {
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->update();
		
	
		// check components
		// definitely going to need to find a more efficient way of this
		// if we get a lot of object. Maybe move out of play state and just do it once for
		// all object everywhere.
		for(Component* c : gameObjects_[i]->getComponents())
		{
			c->update(*gameObjects_[i]);
		}	
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