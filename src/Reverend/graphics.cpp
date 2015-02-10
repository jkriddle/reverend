#include "graphics.h"
#include "object.h"
#include "component\cameracomponent.h"

void Graphics::render(GameObject* o, SDL_Renderer* renderer) {
	/*CameraComponent* component = ObjectFactory::getObject<CameraComponent>();
	int cx = camera_->getPosition().getX();
	int cy = camera_->getPosition().getY();
	int x = (int)position_.getX() - cx;
	int y = (int)position_.getY() - cy;

	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = o->getWidth();
	srcRect.h = destRect.h = o->getHeight();
	destRect.x = o->getX();
	destRect.y = o->getY();
	std::string id = o->getTextureId();
	SDL_RenderCopyEx(renderer, textureMap_[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);*/
}