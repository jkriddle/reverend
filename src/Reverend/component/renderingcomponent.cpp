#include "renderingcomponent.h"

void RenderingComponent::render(SDL_Renderer* renderer) {
	int cx = parent_->getX(); //Game::getInstance()->getCamera()->getPosition().getX();
	int cy = parent_->getY();
	int x = (int)parent_->getX() - cx;
	int y = (int)parent_->getY() - cy;
	TextureManager::getInstance()->drawFrame(texture, x, y, 
		parent_->getWidth(), parent_->getHeight(), 0, 0, renderer);
}

void RenderingComponent::update() {
}


void RenderingComponent::receiveMessage(Message* m) {
}
