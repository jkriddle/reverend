#include "enemy.h"
#include "../component/boxcollider.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	addComponent(new BoxCollider());
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	currentTextureFrame_ = int(((SDL_GetTicks() / 100) % 12));
	currentTextureRow_ = 6;
	velocity_.setX(1);
	velocity_.setY(1);

	SDLGameObject::update();
}

void Enemy::clean()
{
	SDLGameObject::clean();
}