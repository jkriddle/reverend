#pragma once
#ifndef BASERENDERER_H
#define BASERENDERER_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <map>
#include "component.h"
#include "../gameobject.h"

class RenderingComponent : public Component {

public:
	RenderingComponent(GameObject& parent) : Component(parent) {}
	virtual void render(SDL_Renderer* renderer);
	virtual void update();
	virtual void receiveMessage(Message* message);
	
	std::string texture;
};

#endif