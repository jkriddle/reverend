#include "game.h"
#include "sdlgameobject.h"

SDLGameObject::SDLGameObject(const LoaderParams* params) : GameObject(params)
{
	x_ = params->getX();
	y_ = params->getY();

	width_ = params->getWidth();
	height_ = params->getHeight();

	textureId_ = params->getTextureId();

	currentTextureRow_ = 1;
	currentTextureFrame_ = 1;
}

void SDLGameObject::draw()
{
	TextureManager::getInstance()->drawFrame(textureId_, x_, y_, width_, height_, 
		currentTextureRow_, currentTextureFrame_, Game::getInstance()->getRenderer());
}


void SDLGameObject::update()
{
}


void SDLGameObject::clean()
{
}