#include "playerinput.h"

void PlayerInput::start() {
	sprite_ = parent_->getComponent<AnimatedSprite>();
}

void PlayerInput::handleKeyboardInput() {
	bool look = false;
	
	parent_->acceleration = Vector2d::ZERO;
	parent_->velocity = Vector2d::ZERO;

	// Digital Pad
	if (Input::getInstance().isKeyDown(SDL_SCANCODE_A)) {
		// Left
		parent_->velocity.x = -1 * (float)speed_;
	}
		
	if (Input::getInstance().isKeyDown(SDL_SCANCODE_D)) {
		// Right
		parent_->velocity.x = (float)speed_;
	}
		
	if (Input::getInstance().isKeyDown(SDL_SCANCODE_W)) {
		// Up
		parent_->velocity.y = -1 * (float)speed_;
	}
		
	if (Input::getInstance().isKeyDown(SDL_SCANCODE_S)) {
		// Down
		parent_->velocity.y = (float)speed_;
	}

	if (Input::getInstance().isKeyPressed(SDL_SCANCODE_E)) {
		//action();
	}
		
	if (Input::getInstance().isKeyPressed(SDL_SCANCODE_0)) {
		//equip(0);
	}
		
	if (Input::getInstance().isKeyPressed(SDL_SCANCODE_1)) {
		//equip(1);
	}
		
	if (Input::getInstance().isKeyPressed(SDL_SCANCODE_2)) {
		//equip(2);
	}
		
	if (Input::getInstance().isKeyPressed(SDL_SCANCODE_3)) {
		//equip(3);
	}
	
	if (Input::getInstance().isKeyPressed(SDL_SCANCODE_LEFTBRACKET)) {
		//equipPrev();
	}
	
	if (Input::getInstance().isKeyPressed(SDL_SCANCODE_RIGHTBRACKET)) {
		//equipNext();
	}
		
	// if mouse button is being held down (shooting) then look in direction of mouse
	if (Input::getInstance().getMouseButtonState(0)) {
		look = true;
	}
	
	if (Input::getInstance().getMouseButtonPress(0)) {
		//attack();
	}

	if (Input::getInstance().getMouseButtonPress(2)) {
		//action();
	}

	if (look) {
		Vector2d mousePos = Input::getInstance().getMousePosition();

		// Mouse is active
		Vector2d delta = mousePos - parent_->position;
		double radian = atan2(delta.y, delta.x) + M_PI;
		double degree = radian * 180 / M_PI;
			
		// 0/360 degrees is due West
		if (degree >= 30 && degree < 75) {
			// NW
			parent_->forward = Vector2d::NORTH_WEST;
		} else if (degree >= 75 && degree < 120) {
			parent_->forward = Vector2d::NORTH;
		} else if (degree >= 120 && degree < 165) {
			parent_->forward = Vector2d::NORTH_EAST;
		} else if (degree >= 165 && degree < 210) {
			parent_->forward = Vector2d::EAST;
		} else if (degree >= 210 && degree < 255) {
			parent_->forward = Vector2d::SOUTH_EAST;
		} else if (degree >= 255 && degree < 300) {
			parent_->forward = Vector2d::SOUTH;
		} else if (degree >= 300 && degree < 345) {
			parent_->forward = Vector2d::SOUTH_WEST;
		} else if (degree >= 345 || degree < 30) {
			parent_->forward = Vector2d::WEST;
		}
	}

	if (!look) {
		getWalkingDirection();
	}

	updateForwardTexture();

	parent_->velocity += parent_->acceleration;
	parent_->position += parent_->velocity;
}


void PlayerInput::getWalkingDirection() {

	if (parent_->velocity.x == 0 && parent_->velocity.y == 0) {
		// Idle
		parent_->forward = Vector2d::ZERO;
	} else if (parent_->velocity.x == 0 && parent_->velocity.y < 0) {
		// N
		parent_->forward = Vector2d::NORTH;
	} else if (parent_->velocity.x > 0 && parent_->velocity.y < 0) {
		// NE
		parent_->forward = Vector2d::NORTH_EAST;
	} else if (parent_->velocity.x > 0 && parent_->velocity.y == 0) {
		// E
		parent_->forward = Vector2d::EAST;
	} else if (parent_->velocity.x > 0 && parent_->velocity.y > 0) {
		// SE
		parent_->forward = Vector2d::SOUTH_EAST;
	} else if (parent_->velocity.x == 0 && parent_->velocity.y > 0) {
		// S
		parent_->forward = Vector2d::SOUTH;
	} else if (parent_->velocity.x < 0 && parent_->velocity.y > 0) {
		// SW
		parent_->forward = Vector2d::SOUTH_WEST;
	} else if (parent_->velocity.x < 0 && parent_->velocity.y == 0) {
		// W
		parent_->forward = Vector2d::WEST;
	} else if (parent_->velocity.x < 0 && parent_->velocity.y < 0) {
		// NW
		parent_->forward = Vector2d::NORTH_WEST;
	}
}

void PlayerInput::updateForwardTexture() {
	if (parent_->forward == Vector2d::ZERO) {
		sprite_->currentRow = 41; // Idle frame
	}
	if (parent_->forward == Vector2d::NORTH) sprite_->currentRow = 0;
	if (parent_->forward == Vector2d::NORTH_EAST) sprite_->currentRow = 2;
	if (parent_->forward == Vector2d::EAST) sprite_->currentRow = 4;
	if (parent_->forward == Vector2d::SOUTH_EAST) sprite_->currentRow = 6;
	if (parent_->forward == Vector2d::SOUTH) sprite_->currentRow = 8;
	if (parent_->forward == Vector2d::SOUTH_WEST) sprite_->currentRow = 10;
	if (parent_->forward == Vector2d::WEST) sprite_->currentRow = 12;
	if (parent_->forward == Vector2d::NORTH_WEST) sprite_->currentRow = 14;
}

void PlayerInput::update()
{
	Component::update();
	/*
	// Joystick input
	if (Input::getInstance().joysticksInitialised()) {
		
		// Left stick
		if (Input::getInstance().getAxisX(0, 1) > 0 
			|| Input::getInstance().getAxisX(0, 1) < 0) {
			velocity_.x = 1 * Input::getInstance(->getAxisX(0, 1));
		}

		if (Input::getInstance().getAxisY(0, 1) > 0 || Input::getInstance().getAxisY(0, 1) < 0) {
			velocity_.y = 1 * Input::getInstance(->getAxisY(0, 1));
		}
		
		// Right stick (Look)
		bool look = true;

		// If nothing is pressed on right stick, use direction of left stick
		if (Input::getInstance().getAxisX(0, 2) == 0 && Input::getInstance().getAxisY(0, 2) == 0) {
			// No look - see below where we determine the direction of the player
			look = false;
		} else if (Input::getInstance().getAxisX(0, 2) > 0) {
			// RS - Right
			if (Input::getInstance().getAxisY(0, 2) > 0) {
				parent_->forward = Vector2d::NORTH_EAST;
			} else if (Input::getInstance().getAxisY(0, 2) < 0) {
				parent_->forward = Vector2d::SOUTH_EAST;
			} else {
				parent_->forward = Vector2d::EAST;
			}
		} else if (Input::getInstance().getAxisX(0, 2) < 0) {
			// RS - Left
			if (Input::getInstance().getAxisY(0, 2) > 0) {
				parent_->forward = Vector2d::SOUTH_WEST;
			} else if (Input::getInstance().getAxisY(0, 2) < 0) {
				parent_->forward = Vector2d::NORTH_WEST;
			} else {
				parent_->forward = Vector2d::WEST;
			}
		} else if (Input::getInstance().getAxisY(0, 2) > 0) {
			parent_->forward = Vector2d::SOUTH;
		} else if (Input::getInstance().getAxisY(0, 2) < 0) {
			parent_->forward = Vector2d::NORTH;
		}

		// If we're not looking at something, look in the direction we're walking
		if (!look) {
			getWalkingDirection();
		}

		updateForwardTexture();

		// Buttons
		if (Input::getInstance().getButtonState(0, 10)) {
			// Xbox (A) or E-key
			action();
		}
		
		if (Input::getInstance().getTriggerState(0, 1)) {
			// R Trigger
			attack();
		}

		if (Input::getInstance().getTriggerState(0, 8)) {
			// R Bumper
			equipPrev();
		}

		if (Input::getInstance().getTriggerState(0, 9)) {
			// R Bumper
			equipNext();
		}

	}
	*/
	handleKeyboardInput();
}