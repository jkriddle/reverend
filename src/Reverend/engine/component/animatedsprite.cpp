#include "animatedsprite.h"

void AnimatedSprite::render(SDL_Renderer* renderer) {
	int cx = parent_->position.x; //Game::getInstance()->getCamera()->position().x;
	int cy = parent_->position.y;
	int x = (int)parent_->position.x - cx;
	int y = (int)parent_->position.y - cy;
	TextureManager::getInstance()->drawFrame(texture, x, y, 
		parent_->width, parent_->height, currentRow, currentFrame,
		renderer);
}

void AnimatedSprite::update() {
	currentFrame = int(((SDL_GetTicks() / 100) % maxFrames));
}


void AnimatedSprite::receiveMessage(Message* m) {
}
