#pragma once
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <map>
#include "renderingcomponent.h"
#include "../gameobject.h"

class AnimatedSprite : public RenderingComponent {

public:
	AnimatedSprite(GameObject& parent) : currentFrame(0), currentRow(0), maxFrames(1), RenderingComponent(parent) {
	}

	void render(SDL_Renderer* renderer);
	virtual void update();
	virtual void receiveMessage(Message* message);
	
	int currentFrame;
	int currentRow;
	int maxFrames;
};

#endif