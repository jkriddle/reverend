#include "player.h"

void Player::load(int x, int y, int width, int height, std::string textureId)
{
	GameObject::load(x, y, width, height, textureId);
}

void Player::draw(SDL_Renderer* renderer)
{
	GameObject::draw(renderer);
}

void Player::update()
{
	x_ += 1;
	currentTextureFrame_ = int(((SDL_GetTicks() / 100) % 12));
	currentTextureRow_ = 4;
}

void Player::clean()
{
	GameObject::clean();
}
