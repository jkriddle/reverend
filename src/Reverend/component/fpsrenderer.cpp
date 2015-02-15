#include "fpsrenderer.h"

void FpsRenderer::render(SDL_Renderer* renderer) {
	char msg[30];
	SDL_Color color = { 255, 255, 255 };
	sprintf(msg, "FPS: %4.0f", fps_);
	TextureManager::getInstance().drawText("sans", msg, color, 
		10, 10, 100, 30, renderer);
}

void FpsRenderer::update() {
	RenderingComponent::update();
}


void FpsRenderer::receiveMessage(Message* m) {
}
