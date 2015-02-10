#pragma once
#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "tile.h"
#include <map>
#include <vector>

class Terrain : public SDLGameObject
{
public:
	virtual void update();
	virtual void clean();
	Tile* getTile(int x, int y);

private:
	Tile* getCachedTile(int x, int y);
	std::vector<SDLGameObject*> gameObjects_;
	std::map<int, std::map<int, Tile*>> tileCache_;
	void flushCache(int x, int y);
	static const int CACHE_RANGE = 5000;
};

#endif;