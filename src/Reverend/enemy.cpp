#include "enemy.h"

void Enemy::load(int x, int y, int width, int height, std::string textureId)
{
	GameObject::load(x, y, width, height, textureId);
}

void Enemy::draw(SDL_Renderer* renderer)
{
	GameObject::draw(renderer);
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
	GameObject::clean();
}
