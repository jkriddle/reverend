#include "Terrain.h"
#include <iostream>
#include "../engine/camera.h"
#include <time.h>

void Terrain::start() {
	srand(static_cast<int>(time(0)));
	unsigned int a = (rand() % (int)(RAND_MAX + 1));
	unsigned int b = (rand() % (int)(RAND_MAX + 1));
	int seed_ = a*(RAND_MAX+1)+b;
	
	seed_ = 0; // testing only	
	srand(seed_);

	map_ = new MapGenerator(CameraManager::getMain()->getWidth(), CameraManager::getMain()->getHeight(), seed_);
	map_->loadAltitudeMap("overworld.bmp");
}

std::string Terrain::getTile(int x, int y) {
	int scale = 4;
	int tileSize = 32;

	int mapAltX = x;
	int mapAltY =  y;
			
	if (mapAltX != 0) mapAltX = x / tileSize / scale;
	if (mapAltY != 0) mapAltY = y / tileSize / scale;
			
	double height = map_->getAltitude(mapAltX, mapAltY);
	
	std::string texture = "water";
	// Height goes 0 to 255
	if (height > 120) texture = "shallows";
	if (height > 130) texture = "sand";
	if (height > 140) texture = "grass";
	if (height > 210) texture = "dirt";
	if (height > 230) texture = "rock";
	if (height > 250) texture = "snow";

	// TODO load from file
	return texture;
}

void Terrain::update() {
	RenderingComponent::update();
}

void Terrain::render(SDL_Renderer* renderer) {
	int tileSize = 32;
	int scale = 4;
	
	int w = CameraManager::getMain()->getWidth();
	int h = CameraManager::getMain()->getHeight();
	int cameraX = CameraManager::getMain()->target->position.x;
	int cameraY = CameraManager::getMain()->target->position.y;
	
	int startX = cameraX - tileSize;
	int startY =  cameraY - tileSize;
	
	// Always render one extra tile since movement is non-tile based. 
	// Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX + w + tileSize;
	int mY = startY + h + tileSize;

	int offsetX, offsetY, cX, cY;
	
	for(int i = startX; i <= mX; i+=tileSize) { // for 0 through 720, every 32 px
		for(int j = startY; j <= mY; j+=tileSize) { // for 0 through 360, every 32 px
			//srand(seed_ + i + j);

			// we have this tile, but we need to shift the position based on the camera position
			offsetX = (startX % tileSize);
			offsetY = (startY % tileSize);
			cX = i - cameraX - offsetX;
			cY = j - cameraY - offsetY;

			// an equator bug exists where when you are within a few "tileSize" X or Y values of 0, the map gets pretty crazy
			// also a low Y value seems to cause the map generator to crash because it is trying to get a negative pixel value
			// (like it isn't being translated accordingly)
			std::string tile = getTile(i, j);
			TextureManager::getInstance().draw(tile, cX, cY, tileSize, tileSize, renderer);
			
		}
	}
}
