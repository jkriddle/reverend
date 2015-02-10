#include "boxtrigger.h"

BoxTrigger::BoxTrigger(SDLGameObject& parent, int x, int y, int w, int h) 
	: boundingBox_(x, y, w, h), Component(parent) {
	parent_ = &parent;
}

void BoxTrigger::update() {
	boundingBox_.setPosition(parent_->getX(), parent_->getY());
	for(SDLGameObject* o : ObjectFactory::getObjects()) {
		if (&parent_ == &o) continue;
		BoxTrigger* pTrigger = parent_->getComponent<BoxTrigger>();
		BoxTrigger* oTrigger = o->getComponent<BoxTrigger>();
		if (pTrigger != nullptr && oTrigger != nullptr) {
			if (PhysicsSystem::checkCollision(pTrigger->getBounds(), oTrigger->getBounds())) {
				// trigger entry detected
				parent_->sendMessage(new Message(3, MessageType::TriggerEnter, parent_));
			}
		}
	}
}
	
void BoxTrigger::receiveMessage(Message* m) {
	//std::cout << "Box Collider received message" << std::endl;
}