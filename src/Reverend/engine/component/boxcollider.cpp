#include "boxcollider.h"

void BoxCollider::update() {
	boundingBox_.setPosition(parent_->position.x, parent_->position.y);
	for(GameObject* o : Object::getObjects()) {
		if (&parent_ == &o) continue;
		BoxCollider* pCollider = parent_->getComponent<BoxCollider>();
		BoxCollider* oCollider = o->getComponent<BoxCollider>();
		if (pCollider != nullptr && oCollider != nullptr) {
			if (Physics::checkCollision(pCollider->getBounds(), oCollider->getBounds())) {
				// collision detected
				Vector2d newPos = parent_->position - parent_->velocity;
				parent_->position = newPos;
				parent_->velocity = Vector2d::ZERO;
				parent_->acceleration = Vector2d::ZERO;
				parent_->sendMessage(new Message(3, MessageType::CollisionEnter, parent_));
			}
		}
	}
}
	
void BoxCollider::receiveMessage(Message* m) {
	//std::cout << "Box Collider received message" << std::endl;
}