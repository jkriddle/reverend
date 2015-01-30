#include "gameobject.h"

void GameObject::load(int x, int y, int width, int height, std::string textureId)
{
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
	textureId_ = textureId;
	currentTextureRow_ = 1;
	currentTextureFrame_ = 1;
}

void GameObject::draw(SDL_Renderer* renderer)
{
	TextureManager::Instance()->drawFrame(textureId_, x_, y_, width_, height_, currentTextureRow_, currentTextureFrame_, renderer);
}

void GameObject::update()
{
	x_ -= 1;
}

void GameObject::clean()
{
}