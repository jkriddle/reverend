#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "game.h"
#include "sdlgameobject.h"

SDLGameObject::SDLGameObject(const LoaderParams* params) : GameObject(params), 
	position_(params->getX(), params->getY()), velocity_(0, 0), 
	acceleration_(0, 0), forward_(0, 0) {

	width_ = params->getWidth();
	height_ = params->getHeight();

	textureId_ = params->getTextureId();

	currentTextureRow_ = 1;
	currentTextureFrame_ = 1;
}


SDLGameObject::SDLGameObject() : GameObject(), 
	position_(0, 0), velocity_(0, 0), 
	acceleration_(0, 0), forward_(0, 0) {
}

int SDLGameObject::getX()
{
	return position_.getX();
}

int SDLGameObject::getY()
{
	return position_.getY();
}

void SDLGameObject::update()
{
	velocity_ += acceleration_;
	position_ += velocity_;
}

void SDLGameObject::clean()
{
}