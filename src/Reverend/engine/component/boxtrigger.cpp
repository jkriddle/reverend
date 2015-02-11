#include "boxtrigger.h"
#include "../object.h"

void BoxTrigger::update() {
	Component::update();
	boundingBox_.setPosition(parent_->position.x, parent_->position.y);
	for(GameObject* o : Object::getObjects()) {
		if (&parent_ == &o) continue;
		BoxTrigger* pTrigger = parent_->getComponent<BoxTrigger>();
		BoxTrigger* oTrigger = o->getComponent<BoxTrigger>();
		if (pTrigger != nullptr && oTrigger != nullptr) {
			if (Physics::checkCollision(pTrigger->getBounds(), oTrigger->getBounds())) {
				// trigger entry detected
				parent_->sendMessage(new Message(3, MessageType::TriggerEnter, parent_));
			}
		}
	}
}
	
void BoxTrigger::receiveMessage(Message* m) {
	//std::cout << "Box Collider received message" << std::endl;
}