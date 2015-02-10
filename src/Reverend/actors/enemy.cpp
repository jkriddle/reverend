#include "enemy.h"
#include "../component/boxcollider.h"
#include "../component/renderingcomponent.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	addComponent(new BoxCollider(*this, 20, 10, 34, 44));
	addComponent(new RenderingComponent(*this));
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