#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "game.h"
#include "player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	currentTextureRow_ = 4;
	numBeltSlots_ = 3;
	equippedItem_ = 0;
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

	// TODO - if we want idle animation remove the if condition here. I'm just using a static frame
	// for now despite the sprite sheet having it (MORE LOGIC)
	if (forward_ != Vector2d::ZERO) currentTextureFrame_ = int(((SDL_GetTicks() / 100) % 12));
	else currentTextureFrame_ = 1;

	SDLGameObject::update();
	
	Game::getInstance()->getCamera()->goToCenter(position_.getX(), position_.getY());
}

void Player::clean()
{
	SDLGameObject::clean();
}

void Player::handleKeyboardInput() {
	
	bool look = false;

	// Digital Pad
	if (InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_A)) {
		// Left
		std::cout << " left" << std::endl;
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

	if (InputHandler::getInstance()->isKeyPressed(SDL_SCANCODE_E)) {
		action();
	}
		
	if (InputHandler::getInstance()->isKeyPressed(SDL_SCANCODE_0)) {
		equip(0);
	}
		
	if (InputHandler::getInstance()->isKeyPressed(SDL_SCANCODE_1)) {
		equip(1);
	}
		
	if (InputHandler::getInstance()->isKeyPressed(SDL_SCANCODE_2)) {
		equip(2);
	}
		
	if (InputHandler::getInstance()->isKeyPressed(SDL_SCANCODE_3)) {
		equip(3);
	}
	
	if (InputHandler::getInstance()->isKeyPressed(SDL_SCANCODE_LEFTBRACKET)) {
		equipPrev();
	}
	
	if (InputHandler::getInstance()->isKeyPressed(SDL_SCANCODE_RIGHTBRACKET)) {
		equipNext();
	}
		
	// if mouse button is being held down (shooting) then look in direction of mouse
	if (InputHandler::getInstance()->getMouseButtonState(0)) {
		look = true;
	}
	
	if (InputHandler::getInstance()->getMouseButtonPress(0)) {
		attack();
	}

	if (InputHandler::getInstance()->getMouseButtonPress(2)) {
		action();
	}

	if (look) {
		Vector2d* mousePos = InputHandler::getInstance()->getMousePosition();

		// Mouse is active
		Vector2d delta = *mousePos - position_;
		float radian = atan2(delta.getY(), delta.getX()) + M_PI;
		float degree = radian * 180 / M_PI;
			
		// 0/360 degrees is due West
		if (degree >= 30 && degree < 75) {
			// NW
			forward_ = Vector2d::NORTH_WEST;
		} else if (degree >= 75 && degree < 120) {
			forward_ = Vector2d::NORTH;
		} else if (degree >= 120 && degree < 165) {
			forward_ = Vector2d::NORTH_EAST;
		} else if (degree >= 165 && degree < 210) {
			forward_ = Vector2d::EAST;
		} else if (degree >= 210 && degree < 255) {
			forward_ = Vector2d::SOUTH_EAST;
		} else if (degree >= 255 && degree < 300) {
			forward_ = Vector2d::SOUTH;
		} else if (degree >= 300 && degree < 345) {
			forward_ = Vector2d::SOUTH_WEST;
		} else if (degree >= 345 || degree < 30) {
			forward_ = Vector2d::WEST;
		}
	}

	if (!look) {
		getWalkingDirection();
	}

	updateForwardTexture();
}

void Player::getWalkingDirection() {

	if (velocity_.getX() == 0 && velocity_.getY() == 0) {
		// Idle
		forward_ = Vector2d::ZERO;
	} else if (velocity_.getX() == 0 && velocity_.getY() < 0) {
		// N
		forward_ = Vector2d::NORTH;
	} else if (velocity_.getX() > 0 && velocity_.getY() < 0) {
		// NE
		forward_ = Vector2d::NORTH_EAST;
	} else if (velocity_.getX() > 0 && velocity_.getY() == 0) {
		// E
		forward_ = Vector2d::EAST;
	} else if (velocity_.getX() > 0 && velocity_.getY() > 0) {
		// SE
		forward_ = Vector2d::SOUTH_EAST;
	} else if (velocity_.getX() == 0 && velocity_.getY() > 0) {
		// S
		forward_ = Vector2d::SOUTH;
	} else if (velocity_.getX() < 0 && velocity_.getY() > 0) {
		// SW
		forward_ = Vector2d::SOUTH_WEST;
	} else if (velocity_.getX() < 0 && velocity_.getY() == 0) {
		// W
		forward_ = Vector2d::WEST;
	} else if (velocity_.getX() < 0 && velocity_.getY() < 0) {
		// NW
		forward_ = Vector2d::NORTH_WEST;
	}
}

void Player::updateForwardTexture() {
	if (forward_ == Vector2d::ZERO) {
		currentTextureRow_ = 42; // Idle frame
	}
	if (forward_ == Vector2d::NORTH) currentTextureRow_ = 1;
	if (forward_ == Vector2d::NORTH_EAST) currentTextureRow_ = 3;
	if (forward_ == Vector2d::EAST) currentTextureRow_ = 5;
	if (forward_ == Vector2d::SOUTH_EAST) currentTextureRow_ = 7;
	if (forward_ == Vector2d::SOUTH) currentTextureRow_ = 9;
	if (forward_ == Vector2d::SOUTH_WEST) currentTextureRow_ = 11;
	if (forward_ == Vector2d::WEST) currentTextureRow_ = 13;
	if (forward_ == Vector2d::NORTH_WEST) currentTextureRow_ = 15;
}

void Player::handleInput()
{
	// Joystick input
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
		bool look = true;

		// If nothing is pressed on right stick, use direction of left stick
		if (InputHandler::getInstance()->getAxisX(0, 2) == 0 && InputHandler::getInstance()->getAxisY(0, 2) == 0) {
			// No look - see below where we determine the direction of the player
			look = false;
		} else if (InputHandler::getInstance()->getAxisX(0, 2) > 0) {
			// RS - Right
			if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
				forward_ = Vector2d::NORTH_EAST;
			} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
				forward_ = Vector2d::SOUTH_EAST;
			} else {
				forward_ = Vector2d::EAST;
			}
		} else if (InputHandler::getInstance()->getAxisX(0, 2) < 0) {
			// RS - Left
			if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
				forward_ = Vector2d::SOUTH_WEST;
			} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
				forward_ = Vector2d::NORTH_WEST;
			} else {
				forward_ = Vector2d::WEST;
			}
		} else if (InputHandler::getInstance()->getAxisY(0, 2) > 0) {
			forward_ = Vector2d::SOUTH;
		} else if (InputHandler::getInstance()->getAxisY(0, 2) < 0) {
			forward_ = Vector2d::NORTH;
		}

		// If we're not looking at something, look in the direction we're walking
		if (!look) {
			getWalkingDirection();
		}

		updateForwardTexture();

		// Buttons
		if (InputHandler::getInstance()->getButtonState(0, 10)) {
			// Xbox (A) or E-key
			action();
		}
		
		if (InputHandler::getInstance()->getTriggerState(0, 1)) {
			// R Trigger
			attack();
		}

		if (InputHandler::getInstance()->getTriggerState(0, 8)) {
			// R Bumper
			equipPrev();
		}

		if (InputHandler::getInstance()->getTriggerState(0, 9)) {
			// R Bumper
			equipNext();
		}

	}

	handleKeyboardInput();
}


void Player::move(Vector2d* direction) {
}

void Player::action() {
	std::cout << "action" << std::endl;
}

void Player::attack() {
	std::cout << "attack" << std::endl;
	SoundManager::getInstance()->playSound("short_swipe", 0);
}

void Player::equip(int slot) {
	std::cout << "equipping slot " << slot << std::endl;
	equippedItem_ = slot;
}

void Player::equipPrev() {
	equippedItem_--;
	if (equippedItem_ < 0) equippedItem_ = numBeltSlots_;
	equip(equippedItem_);
}

void Player::equipNext() {
	equippedItem_++;
	if (equippedItem_ > numBeltSlots_) equippedItem_ = 0;
	equip(equippedItem_);
}
