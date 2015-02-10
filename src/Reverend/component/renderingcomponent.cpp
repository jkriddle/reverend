#include "renderingcomponent.h"

void RenderingComponent::render(SDL_Renderer* renderer) {
	bool x = true;
	/*
	int cx = Game::getInstance()->getCamera()->getPosition().getX();
	int cy = Game::getInstance()->getCamera()->getPosition().getY();
	int x = (int)position_.getX() - cx;
	int y = (int)position_.getY() - cy;
	TextureManager::getInstance()->drawFrame(textureId_, x, y, width_, height_, 
		currentTextureRow_, currentTextureFrame_, Game::getInstance()->getRenderer());
		*/
}

void RenderingComponent::update() {
}


void RenderingComponent::receiveMessage(Message* m) {
}
