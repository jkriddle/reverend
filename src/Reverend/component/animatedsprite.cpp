#include "animatedsprite.h"

void AnimatedSprite::render(SDL_Renderer* renderer) {
	int cx = parent_->getX(); //Game::getInstance()->getCamera()->getPosition().getX();
	int cy = parent_->getY();
	int x = (int)parent_->getX() - cx;
	int y = (int)parent_->getY() - cy;
	TextureManager::getInstance()->drawFrame(texture, x, y, 
		parent_->getWidth(), parent_->getHeight(), currentRow, currentFrame,
		renderer);
}

void AnimatedSprite::update() {
	currentFrame = int(((SDL_GetTicks() / 100) % maxFrames));
}


void AnimatedSprite::receiveMessage(Message* m) {
}
