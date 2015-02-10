#include "graphics.h"
#include "object.h"
#include "component\cameracomponent.h"

void Graphics::render(GameObject* o, SDL_Renderer* renderer) {
	/*CameraComponent* component = ObjectFactory::getObject<CameraComponent>();
	int cx = camera_->position().x;
	int cy = camera_->position().y;
	int x = (int)position_.x - cx;
	int y = (int)position_.y - cy;

	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = o->width;
	srcRect.h = destRect.h = o->height;
	destRect.x = o->x;
	destRect.y = o->y;
	std::string id = o->texture;
	SDL_RenderCopyEx(renderer, textureMap_[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);*/
}