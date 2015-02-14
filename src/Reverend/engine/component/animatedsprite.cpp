#include "animatedsprite.h"
#include "../camera.h"

void AnimatedSprite::render(SDL_Renderer* renderer) {
	Vector2d offset = CameraManager::getMain()->translate((int)parent_->position.x, (int)parent_->position.y);
	TextureManager::getInstance().drawFrame(texture.c_str(), offset.x, offset.y,
		parent_->width, parent_->height, currentRow, currentFrame, renderer);
}

void AnimatedSprite::update() {
	Component::update();
	currentFrame = int(((SDL_GetTicks() / 100) % maxFrames));
}


void AnimatedSprite::receiveMessage(Message* m) {
}
