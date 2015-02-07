#pragma once
#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "layer.h"
#include "gameobject.h"
#include <vector>

class ObjectLayer : public Layer
{
public:
	void add(GameObject* object);
	virtual void clean();
	virtual void update();
	virtual void draw();
	std::vector<GameObject*>* getGameObjects()
	{
		return &gameObjects_;
	}

private:
	std::vector<GameObject*> gameObjects_;
};

#endif;