#include "terrain.h"
#include <iostream>
#include "../game.h"

Tile* Terrain::getCachedTile(int x, int y) {
	return tileCache_[x][y];
}

// Remove any distance tiles that no longer need to be stored in memory
void Terrain::flushCache(int x, int y) {
	// TODO:
	// The code below causes huge lag due to having to loop through the entire Y cache constantly.
	// Find a better way to do this. There has to be an easy way to create an index of item so we can quickly
	// just say "delete [x][i]"

	/*const int minX = tileCache_.rbegin()->first;

	std::map<int, std::map<int, Tile*>>::iterator xi = tileCache_.begin();
	std::map<int, Tile*>::iterator yi;
	std::map<int, std::map<int, Tile*>>::iterator toEraseX;
	std::map<int, Tile*>::iterator toEraseY;

	while (xi != tileCache_.end()) {
		if (xi->first < (x - TerrainLayer::CACHE_RANGE) || xi->first > (x + TerrainLayer::CACHE_RANGE)) {
		   toEraseX = xi;
		   ++xi;
		   tileCache_.erase(toEraseX);
		   std::cout << "Erasing cache outside of " << x << std::endl;
		} else {
			// X is valid, what about Y?
			yi = xi->second.begin();
			while (yi != xi->second.end()) {
				if (yi->first < (y - TerrainLayer::CACHE_RANGE) || yi->first > (y + TerrainLayer::CACHE_RANGE)) {
				   toEraseY = yi;
				   ++yi;
				   xi->second.erase(toEraseY);
		   std::cout << "Erasing cache outside of " << y << std::endl;
				} else {
					// X is valid, what about Y?
				   ++yi;
				}
			}
		   ++xi;
		}
	}*/
}

// This may seem pointless right now since we're still just using the altitude map,
// but eventually each tile is goingto be calculated by altitude, moisture, other tiles around
// it, randomeness, etc. Re-calculating this for every tile every frame would kill the CPU. 
// Thus we will only calculate tiles once ever, and store them in memory.
// Eventually we'll use a disk cache to offload the memory and re-load blocks as appropriate.
Tile* Terrain::getTile(int x, int y) {
	Tile* tile = nullptr;
	tile = getCachedTile(x, y);
	if (tile != nullptr) return tile;

	int mapAltX = x;
	int mapAltY =  y;
			
	if (mapAltX != 0) mapAltX = x / Game::getTileSize() / Game::getScale();
	if (mapAltY != 0) mapAltY = y / Game::getTileSize() / Game::getScale();
			
	double height = Game::getInstance()->getMap()->getAltitude(mapAltX, mapAltY);
	
	std::string texture = "water";
	// Height goes 0 to 255
	if (height > 120) texture = "shallows";
	if (height > 130) texture = "sand";
	if (height > 140) texture = "grass";
	if (height > 210) texture = "dirt";
	if (height > 230) texture = "rock";
	if (height > 250) texture = "snow";

	// TODO load from file
	tile = new Tile(new LoaderParams(x, y, 32, 32, texture));

	tileCache_[x][y] = tile;
	return tile;
}

void Terrain::update() {
}

/*
void Terrain::draw() {
	int tileSize = Game::getTileSize();
	int scale = Game::getScale();

	int cameraX = (int)Game::getInstance()->getCamera()->getPosition().getX();
	int cameraY = (int)Game::getInstance()->getCamera()->getPosition().getY();
	
	int startX = cameraX - tileSize;
	int startY =  cameraY - tileSize;
	
	// Always render one extra tile since movement is non-tile based. 
	// Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX +  (int)Game::getInstance()->getScreenWidth() + tileSize;
	int mY = startY +  (int)Game::getInstance()->getScreenHeight() + tileSize;

	int offsetX, offsetY, cX, cY;
	
	for(int i = startX; i <= mX; i+=tileSize) { // for 0 through 720, every 32 px
		for(int j = startY; j <= mY; j+=tileSize) { // for 0 through 360, every 32 px
			//srand(seed_ + i + j);

			Tile* tile = getTile(i, j);

			// we have this tile, but we need to shift the position based on the camera position
			offsetX = (startX % tileSize);
			offsetY = (startY % tileSize);
			cX = i - cameraX - offsetX;
			cY = j - cameraY - offsetY;

			// an equator bug exists where when you are within a few "tileSize" X or Y values of 0, the map gets pretty crazy
			// also a low Y value seems to cause the map generator to crash because it is trying to get a negative pixel value
			// (like it isn't being translated accordingly)

			TextureManager::getInstance()->draw(tile->getTextureId(), cX, cY, tileSize, tileSize, Game::getInstance()->getRenderer());
		}
	}

	flushCache(cameraX, cameraY);
}*/

void Terrain::clean() {
	tileCache_.clear();
}