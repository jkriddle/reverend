#include "player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	x_ += 1;
	currentTextureFrame_ = int(((SDL_GetTicks() / 100) % 12));
	currentTextureRow_ = 4;
}

void Player::clean()
{
	SDLGameObject::clean();
}
