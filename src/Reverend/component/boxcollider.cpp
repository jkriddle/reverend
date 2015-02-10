#include "boxcollider.h"

BoxCollider::BoxCollider(SDLGameObject& parent, int x, int y, int w, int h) 
	: BoxTrigger(parent, x, y, w, h) {
}

void BoxCollider::update() {
	boundingBox_.setPosition(parent_->getX(), parent_->getY());
	for(SDLGameObject* o : ObjectFactory::getObjects()) {
		if (&parent_ == &o) continue;
		BoxCollider* pCollider = parent_->getComponent<BoxCollider>();
		BoxCollider* oCollider = o->getComponent<BoxCollider>();
		if (pCollider != nullptr && oCollider != nullptr) {
			if (PhysicsSystem::checkCollision(pCollider->getBounds(), oCollider->getBounds())) {
				// collision detected
				Vector2d newPos = parent_->getPosition() - parent_->getVelocity();
				parent_->setPosition(newPos);
				parent_->setVelocity(Vector2d::ZERO);
				parent_->setAcceleration(Vector2d::ZERO);
				parent_->sendMessage(new Message(3, MessageType::CollisionEnter, parent_));
			}
		}
	}
}
	
void BoxCollider::receiveMessage(Message* m) {
	//std::cout << "Box Collider received message" << std::endl;
}