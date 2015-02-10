#include "enemy.h"
#include "../engine/component/boxcollider.h"
#include "../engine/component/renderingcomponent.h"

Enemy::Enemy() : GameObject() {
}

Enemy::Enemy(const LoaderParams* pParams) : GameObject(pParams)
{
	addComponent(new BoxCollider(*this));
	addComponent(new RenderingComponent(*this));
}/*

void Enemy::update()
{
	currentTextureFrame_ = int(((SDL_GetTicks() / 100) % 12));
	currentTextureRow_ = 6;
	velocity_.setX(1);
	velocity_.setY(1);

	GameObject::update();
}

void Enemy::clean()
{
	GameObject::clean();
}
*/