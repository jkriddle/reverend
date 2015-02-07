#pragma once
#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "objectlayer.h"
#include "gameobject.h"
#include "tile.h"
#include <map>

class TerrainLayer : public ObjectLayer
{
public:
	virtual void update();
	virtual void draw();
	virtual void clean();
	Tile* getTile(int x, int y);

private:
	Tile* getCachedTile(int x, int y);
	std::vector<GameObject*> gameObjects_;
	std::map<int, std::map<int, Tile*>> tileCache_;
	void flushCache(int x, int y);
	static const int CACHE_RANGE = 200;
};

#endif;