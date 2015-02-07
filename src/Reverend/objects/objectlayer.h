#pragma once
#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "layer.h"
#include "gameobject.h"
#include <vector>

class ObjectLayer : public Layer
{
public:
	virtual void update();
	virtual void render();
	std::vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}

private:
	std::vector<GameObject*> m_gameObjects;
};

#endif;