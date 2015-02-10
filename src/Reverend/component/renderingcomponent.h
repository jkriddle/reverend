#pragma once
#ifndef BASERENDERER_H
#define BASERENDERER_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <map>
#include "component.h"

class RenderingComponent : public Component {

public:
	RenderingComponent(SDLGameObject& parent) : Component(parent) {}
	void render(SDL_Renderer* renderer);
	virtual void update();
	virtual void receiveMessage(Message* message);
};

#endif