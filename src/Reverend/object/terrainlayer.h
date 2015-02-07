#pragma once
#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "objectlayer.h"

class TerrainLayer : public ObjectLayer {

public:
	virtual void update();
	virtual void draw();
	virtual void clean();

private:
	std::vector<GameObject*> gameObjects_;
};

#endif