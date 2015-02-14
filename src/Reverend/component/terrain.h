#pragma once
#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "../engine/gameobject.h"
#include "../engine/component/renderingcomponent.h"
#include "../map/mapgenerator.h"
#include <map>
#include <string>

class Terrain : public RenderingComponent
{
public:
	Terrain(GameObject& parent) : scale_(1), tileSize_(32), map_(nullptr), RenderingComponent(parent){}
	~Terrain() {
		delete map_;
		map_ = NULL;
	}
	virtual void start();
	virtual void update();
	virtual void render(SDL_Renderer* renderer);

private:
	std::string Terrain::mapTexture(double height);
	std::string Terrain::getTile(int x, int y);
	GameObject* getCachedTile(int x, int y);
	MapGenerator* map_;
	const int scale_;
	const int tileSize_;
};

#endif;