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

std::string Terrain::mapTexture(double height) {
	std::string texture = "water";
	// Height goes 0 to 255
	if (height > 120) texture = "shallows";
	if (height > 130) texture = "sand";
	if (height > 140) texture = "grass";
	if (height > 210) texture = "dirt";
	if (height > 230) texture = "rock";
	if (height > 250) texture = "snow";
	return texture;
}

std::string Terrain::getTile(int x, int y) {
	int mapAltX = x;
	int mapAltY =  y;
			
	if (mapAltX != 0) mapAltX = x / tileSize_ / scale_;
	if (mapAltY != 0) mapAltY = y / tileSize_ / scale_;
			
	double height = map_->getAltitude(mapAltX, mapAltY);
	std::string texture = mapTexture(height);
	
	height = map_->getAltitude(mapAltX, mapAltY - 1);
	std::string textureN = mapTexture(height);
	if (texture == "grass" && textureN == "dirt") {
		texture = "grass-n";
	}

	// if block above this is dirt


	// TODO load from file
	return texture;
}

void Terrain::update() {
	RenderingComponent::update();
}

void Terrain::render(SDL_Renderer* renderer) {
	int w = CameraManager::getMain()->getWidth();
	int h = CameraManager::getMain()->getHeight();
	int cameraX = CameraManager::getMain()->target->position.x;
	int cameraY = CameraManager::getMain()->target->position.y;
	
	int startX = cameraX - tileSize_;
	int startY =  cameraY - tileSize_;
	
	// Always render one extra tile since movement is non-tile based. 
	// Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX + w + tileSize_;
	int mY = startY + h + tileSize_;

	int offsetX, offsetY, cX, cY;
	
	for(int i = startX; i <= mX; i+=tileSize_) { // for 0 through 720, every 32 px
		for(int j = startY; j <= mY; j+=tileSize_) { // for 0 through 360, every 32 px
			//srand(seed_ + i + j);

			// we have this tile, but we need to shift the position based on the camera position
			offsetX = (startX % tileSize_);
			offsetY = (startY % tileSize_);
			cX = i - cameraX - offsetX;
			cY = j - cameraY - offsetY;

			// an equator bug exists where when you are within a few "tileSize_" X or Y values of 0, the map gets pretty crazy
			// also a low Y value seems to cause the map generator to crash because it is trying to get a negative pixel value
			// (like it isn't being translated accordingly)
			std::string tile = getTile(i, j);
			TextureManager::getInstance().draw(tile, cX, cY, tileSize_, tileSize_, renderer);
			
		}
	}
}
