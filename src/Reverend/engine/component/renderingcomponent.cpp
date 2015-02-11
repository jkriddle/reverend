#include "renderingcomponent.h"
#include "../camera.h"

void RenderingComponent::render(SDL_Renderer* renderer) {
	Vector2d offset = CameraManager::getMain()->translate((int)parent_->position.x, (int)parent_->position.y);
	TextureManager::getInstance().drawFrame(texture, offset.x, offset.y,
		parent_->width, parent_->height, 0, 0, renderer);
}

void RenderingComponent::update() {
	Component::update();
}


void RenderingComponent::receiveMessage(Message* m) {
}
