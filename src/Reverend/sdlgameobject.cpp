#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "game.h"
#include "sdlgameobject.h"

SDLGameObject::SDLGameObject(const LoaderParams* params) : GameObject(params), position_(params->getX(), params->getY()), velocity_(0, 0), acceleration_(0, 0) {
	width_ = params->getWidth();
	height_ = params->getHeight();

	textureId_ = params->getTextureId();

	currentTextureRow_ = 1;
	currentTextureFrame_ = 1;
}

void SDLGameObject::draw()
{
	TextureManager::getInstance()->drawFrame(textureId_, (int)position_.getX(), (int)position_.getY(), width_, height_, 
		currentTextureRow_, currentTextureFrame_, Game::getInstance()->getRenderer());
}


void SDLGameObject::update()
{
	velocity_ += acceleration_;
	position_ += velocity_;
}


void SDLGameObject::clean()
{
}