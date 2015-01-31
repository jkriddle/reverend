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

void Player::handleKeyboardInput() {
	
	bool look = false;

	GameDirection direction = currentDirection_;

	// Digital Pad
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_A)) {
		// Left
		velocity_.setX(-1);
	}
		
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_D)) {
		// Right
		velocity_.setX(1);
	}
		
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_W)) {
		// Up
		velocity_.setY(-1);
	}
		
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_S)) {
		// Down
		velocity_.setY(1);
	}
		
	Vector2d* mousePos = InputHandler::getInstance()->getMousePosition();
	Vector2d* prevMousePos = InputHandler::getInstance()->getPrevMousePosition();

	// If mouse moves a single pixel don't register it as a changed look
	if (abs(mousePos->getX() - prevMousePos->getX()) > 1 && abs(mousePos->getY() - prevMousePos->getY()) > 1) {
		look = true;
	}

	if (!look) {
		look = false;
	} else {
		look = true;
			
		// Mouse is active
		Vector2d delta = *mousePos - position_;
		float radian = atan2(delta.getY(), delta.getX()) + M_PI;
		float degree = radian * 180 / M_PI;
			
		// 0/360 degrees is due West
		if (degree >= 30 && degree < 75) {
			direction = GameDirection::NORTH_WEST;
		} else if (degree >= 75 && degree < 120) {
			direction = GameDirection::NORTH;
		} else if (degree >= 120 && degree < 165) {
			direction = GameDirection::NORTH_EAST;
		} else if (degree >= 165 && degree < 210) {
			direction = GameDirection::EAST;
		} else if (degree >= 210 && degree < 255) {
			direction = GameDirection::SOUTH_EAST;
		} else if (degree >= 255 && degree < 300) {
			direction = GameDirection::SOUTH;
		} else if (degree >= 300 && degree < 345) {
			direction = GameDirection::SOUTH_WEST;
		} else if (degree >= 345 || degree < 30) {
			direction = GameDirection::WEST;
		}
	}

	if (!look) {
		direction = getWalkingDirection();
	}

	updateInputTexture(direction);

}

GameDirection Player::getWalkingDirection() {
	GameDirection direction = currentDirection_;

	if (velocity_.getX() == 0 && velocity_.getY() == 0) {
		// Idle
	} else if (velocity_.getX() == 0 && velocity_.getY() < 0) {
		// N
		direction = GameDirection::NORTH;
	} else if (velocity_.getX() > 0 && velocity_.getY() < 0) {
		// NE
		direction = GameDirection::NORTH_EAST;
	} else if (velocity_.getX() > 0 && velocity_.getY() == 0) {
		// E
		direction = GameDirection::EAST;
	} else if (velocity_.getX() > 0 && velocity_.getY() > 0) {
		// SE
		direction = GameDirection::SOUTH_EAST;
	} else if (velocity_.getX() == 0 && velocity_.getY() > 0) {
		// S
		direction = GameDirection::SOUTH;
	} else if (velocity_.getX() < 0 && velocity_.getY() > 0) {
		// SW
		direction = GameDirection::SOUTH_WEST;
	} else if (velocity_.getX() < 0 && velocity_.getY() == 0) {
		// W
		direction = GameDirection::WEST;
	} else if (velocity_.getX() < 0 && velocity_.getY() < 0) {
		// NW
		direction = GameDirection::NORTH_WEST;
	}
	return direction;
}

void Player::updateInputTexture(GameDirection direction) {
	switch(direction) {
		case GameDirection::NORTH:
			currentTextureRow_ = 1;
			break;
		case GameDirection::NORTH_EAST:
			currentTextureRow_ = 3;
			break;
		case GameDirection::EAST:
			currentTextureRow_ = 5;
		break;
		case GameDirection::SOUTH_EAST:
			currentTextureRow_ = 7;
			break;
		case GameDirection::SOUTH:
			currentTextureRow_ = 9;
			break;
		case GameDirection::SOUTH_WEST:
			currentTextureRow_ = 11;
			break;
		case GameDirection::WEST:
			currentTextureRow_ = 13;
			break;
		case GameDirection::NORTH_WEST:
			currentTextureRow_ = 14;
			break;
	}
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
		GameDirection direction = currentDirection_;
		bool look = true;

		// If nothing is pressed on right stick, use direction of left stick
		if (InputHandler::getInstance()->getAxisX(0, 2) == 0 && InputHandler::getInstance()->getAxisY(0, 2) == 0) {
			// No look - see below where we determine the direction of the player
			look = false;
		} else if (InputHandler::getInstance()->getAxisX(0, 2) > 0) {
			// RS - Right
			if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
				direction = GameDirection::NORTH_EAST;
			} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
				direction = GameDirection::SOUTH_EAST;
			} else {
				direction = GameDirection::EAST;
			}
		} else if (InputHandler::getInstance()->getAxisX(0, 2) < 0) {
			// RS - Left
			if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
				direction = GameDirection::SOUTH_WEST;
			} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
				direction = GameDirection::NORTH_WEST;
			} else {
				direction = GameDirection::WEST;
			}
		} else if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
			direction = GameDirection::SOUTH;
		} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
			direction = GameDirection::NORTH;
		}

		if (!look) {
			direction = getWalkingDirection();
		}

		updateInputTexture(direction);

		// Buttons
		if (InputHandler::getInstance()->getButtonState(0, 10) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_E)) {
			// Xbox (A) or E-key
		}
		
		if (InputHandler::getInstance()->getButtonState(0, 12) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_F)) {
			// Xbox (X) or F-key
		}
		
		if (InputHandler::getInstance()->getButtonState(0, 13) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_M)) {
			// Xbox (Y) or M-key
		}
		

		if (InputHandler::getInstance()->getButtonState(0, 11) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_C)) {
			// Xbox (B) or C-key
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

	handleKeyboardInput();
}
