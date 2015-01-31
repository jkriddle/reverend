#include "button.h"

Button::Button(const LoaderParams* params, void (*callback)()) : SDLGameObject(params), callback_(callback) {
	currentTextureFrame_ = ButtonState::MOUSE_OUT;
}

void Button::draw() {
	SDLGameObject::draw();
}

void Button::update() {
	Vector2d* mousePos = InputHandler::getInstance()->getMousePosition();
	if(mousePos->getX() < (position_.getX() + width_) 
		&& mousePos->getX() > position_.getX()
		&& mousePos->getY() < (position_.getY() + height_)
		&& mousePos->getY() > position_.getY()) {
		if(InputHandler::getInstance()->getMouseButtonState(LEFT) && released_) {
			currentTextureFrame_ = CLICKED;
			callback_();
			released_ = false;
		} else if(!InputHandler::getInstance()->getMouseButtonState(LEFT)) {
			released_ = true;
			currentTextureFrame_ = MOUSE_OVER;
		}
	} else {
		currentTextureFrame_ = MOUSE_OUT;
	}
}

void Button::clean() {
	SDLGameObject::clean();
}