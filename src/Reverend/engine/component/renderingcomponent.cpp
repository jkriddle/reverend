#include "renderingcomponent.h"

void RenderingComponent::render(SDL_Renderer* renderer) {
	int cx = parent_->position.x; //Game::getInstance()->getCamera()->getPosition().x;
	int cy = parent_->position.y;
	int x = (int)parent_->position.x - cx;
	int y = (int)parent_->position.y - cy;
	TextureManager::getInstance()->drawFrame(texture, x, y, 
		parent_->width, parent_->height, 0, 0, renderer);
}

void RenderingComponent::update() {
}


void RenderingComponent::receiveMessage(Message* m) {
}
