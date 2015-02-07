#pragma once
#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "objectlayer.h"

class TerrainLayer : ObjectLayer {
	virtual void clean();
	virtual void update();
	virtual void draw();
};

#endif