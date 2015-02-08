#pragma once
#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "layer.h"
#include "sdlgameobject.h"
#include <vector>

class ObjectLayer : public Layer
{
public:
	void add(SDLGameObject* object);
	virtual void update();
	virtual void draw();
	virtual void clean();
	std::vector<SDLGameObject*>* getGameObjects()
	{
		return &gameObjects_;
	}

private:
	std::vector<SDLGameObject*> gameObjects_;
};

#endif;