#include "enemy.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	x_ += 1;
	y_ += 1;
	currentTextureFrame_ = int(((SDL_GetTicks() / 100) % 12));
	currentTextureRow_ = 6;
}

void Enemy::clean()
{
	SDLGameObject::clean();
}