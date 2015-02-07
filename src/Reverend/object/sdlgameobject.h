#pragma once

#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include "../vector2d.h"
#include "../inputhandler.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual int getX();
	virtual int getY();
	 std::string getTextureId() { return textureId_; }

protected:
	Vector2d position_;
	Vector2d velocity_;
	Vector2d acceleration_;
	Vector2d forward_;

	int width_;
	int height_;

	int currentTextureRow_;
	int currentTextureFrame_;

	std::string textureId_;
};

#endif