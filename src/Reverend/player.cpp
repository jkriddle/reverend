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
		if (InputHandler::getInstance()->getAxisX(0, 1) > 0 
			|| InputHandler::getInstance()->getAxisX(0, 1) < 0) {
			velocity_.setX(1 * InputHandler::getInstance()->getAxisX(0, 1));
		}

		if (InputHandler::getInstance()->getAxisY(0, 1) > 0 || InputHandler::getInstance()->getAxisY(0, 1) < 0) {
			velocity_.setY(1 * InputHandler::getInstance()->getAxisY(0, 1));
		}
		
		// Right stick (Look)

		// If nothing is pressed on right stick, use direction of left stick
		if (InputHandler::getInstance()->getAxisX(0, 2) == 0 && InputHandler::getInstance()->getAxisY(0, 2) == 0) {
			if (velocity_.getX() == 0 && velocity_.getY() == 0) {
				// Idle
			} else if (velocity_.getX() == 0 && velocity_.getY() < 0) {
				// N
			currentTextureRow_ = 1;
			} else if (velocity_.getX() > 0 && velocity_.getY() < 0) {
				// NE
				currentTextureRow_ = 3;
			} else if (velocity_.getX() > 0 && velocity_.getY() == 0) {
				// E
				currentTextureRow_ = 5;
			} else if (velocity_.getX() > 0 && velocity_.getY() > 0) {
				// SE
				currentTextureRow_ = 7;
			} else if (velocity_.getX() == 0 && velocity_.getY() > 0) {
				// S
			currentTextureRow_ = 9;
			} else if (velocity_.getX() < 0 && velocity_.getY() > 0) {
				// SW
				currentTextureRow_ = 11;
			} else if (velocity_.getX() < 0 && velocity_.getY() == 0) {
				// W
				currentTextureRow_ = 13;
			} else if (velocity_.getX() < 0 && velocity_.getY() < 0) {
				// NW
				currentTextureRow_ = 14;
			}
		} else if (InputHandler::getInstance()->getAxisX(0, 2) > 0) {
			// RS - Right
			if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
				// Look NE
				currentTextureRow_ = 7;
			} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
				// Look SE
				currentTextureRow_ = 3;
			} else {
				// Look E
				currentTextureRow_ = 5;
			}
		} else if (InputHandler::getInstance()->getAxisX(0, 2) < 0) {
			// RS - Left
			if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
				// Look SW
				currentTextureRow_ = 11;
			} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
				// Look NW
				currentTextureRow_ = 14;
			} else {
				// Look W
				currentTextureRow_ = 13;
			}
		} else if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
			// Look S
			currentTextureRow_ = 9;
		} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
			// Look N
			currentTextureRow_ = 1;
		}

		// Digital Pad
		if (InputHandler::getInstance()->getButtonState(0, 2)) {
			// Left
			velocity_.setX(-1);
		}
		
		if (InputHandler::getInstance()->getButtonState(0, 3)) {
			// Right
			velocity_.setX(1);
		}
		
		if (InputHandler::getInstance()->getButtonState(0, 0)) {
			// Up
			velocity_.setY(-1);
		}
		
		if (InputHandler::getInstance()->getButtonState(0, 1)) {
			// Down
			velocity_.setY(1);
		}

		// Buttons
		if (InputHandler::getInstance()->getButtonState(0, 10)) {
			// A
		}
		
		if (InputHandler::getInstance()->getButtonState(0, 12)) {
			// X
		}
		
		if (InputHandler::getInstance()->getButtonState(0, 13)) {
			// Y
		}
		

		if (InputHandler::getInstance()->getButtonState(0, 11)) {
			// B
		}

		if (InputHandler::getInstance()->getTriggerState(0, 0)) {
			// L Trigger
			std::cout << "L TRIGGER" << std::endl;
		}

		if (InputHandler::getInstance()->getTriggerState(0, 1)) {
			// R Trigger
			std::cout << "R TRIGGER" << std::endl;
		}
		
		
		if (InputHandler::getInstance()->getButtonState(0, 5)) {
			// Select
		}

		if (InputHandler::getInstance()->getButtonState(0, 4)) {
			// Start
		}
		

	}
}
