#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	currentTextureRow_ = 4;
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	velocity_.setX(0);
	velocity_.setY(0);

	handleInput();

	currentTextureFrame_ = int(((SDL_GetTicks() / 100) % 12));

	SDLGameObject::update();
}

void Player::clean()
{
	SDLGameObject::clean();
}

void Player::handleInput()
{
	if (InputHandler::getInstance()->joysticksInitialised()) {
		
		// Left stick
		if (InputHandler::getInstance()->getAxisX(0, 1) > 0 || InputHandler::getInstance()->getAxisX(0, 1) < 0) {
			velocity_.setX(1 * InputHandler::getInstance()->getAxisX(0, 1));
		}

		if (InputHandler::getInstance()->getAxisY(0, 1) > 0 || InputHandler::getInstance()->getAxisY(0, 1) < 0) {
			velocity_.setY(1 * InputHandler::getInstance()->getAxisY(0, 1));
		}
		
		// Right stick
		if (InputHandler::getInstance()->getAxisX(0, 2) > 0 || InputHandler::getInstance()->getAxisX(0, 2) < 0) {
			velocity_.setX(1 * InputHandler::getInstance()->getAxisX(0, 2));
		}

		if (InputHandler::getInstance()->getAxisY(0, 2) > 0 || InputHandler::getInstance()->getAxisY(0, 2) < 0) {
			velocity_.setY(1 * InputHandler::getInstance()->getAxisY(0, 2));
		}
	}
}
