#pragma once
#ifndef FPSRENDERER_H
#define FPSRENDERER_H

#include "../engine/component/component.h"
#include "../engine/component/renderingcomponent.h"
#include "../engine/gameobject.h"

class FpsRenderer : public RenderingComponent {

public:
	FpsRenderer(GameObject* parent) : fps_(0), RenderingComponent(parent) {
	}

	virtual void render(SDL_Renderer* renderer);
	virtual void update();
	virtual void receiveMessage(Message* message);
	
	std::string texture;
private:
	double fps_;
};

#endif