#include "gameobject.h"
#include "cleanup.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


GameObject::GameObject(SDL_Texture* texture, int x, int y) {
	texture_ = texture;
	x_ = x;
	y_ = y;
}

GameObject::~GameObject() {
	if (texture_ != nullptr) {
		cleanup(texture_);
		texture_ = NULL;
	}
}

void GameObject::setPos(int x, int y) {
	x_ = x;
	y_ = y;
}