#pragma once

#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include <SDL/SDL.h>
#include "gameobject.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:
	int x_;
	int y_;

	int width_;
	int height_;

	int currentTextureRow_;
	int currentTextureFrame_;

	std::string textureId_;
};

#endif