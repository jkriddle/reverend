#include "terrainlayer.h"
#include "../game.h"

void TerrainLayer::update() {
	ObjectLayer::update();
}

// Draw all tiles in range
void TerrainLayer::draw() {
	int tileSize = 32;
	int scale = 4;

	int cameraX = Game::getInstance()->getCamera()->getPosition().getX();
	int cameraY = Game::getInstance()->getCamera()->getPosition().getY();
	
	int startX = cameraX - tileSize;
	int startY =  cameraY - tileSize;
	
	// Always render one extra tile since movement is non-tile based. 
	// Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX +  Game::getInstance()->getScreenWidth() + tileSize;
	int mY = startY +  Game::getInstance()->getScreenHeight() + tileSize;

	int mapAltX, mapAltY, offsetX, offsetY, cX, cY;
	double height;
			
	std::string texture = "water";
	
	for(int i = startX; i <= mX; i+=tileSize) { // for 0 through 720, every 32 px
		for(int j = startY; j <= mY; j+=tileSize) { // for 0 through 360, every 32 px
			//srand(seed_ + i + j);
			mapAltX = i;
			mapAltY =  j;
			
			if (mapAltX != 0) mapAltX = i / tileSize / scale;
			if (mapAltY != 0) mapAltY = j / tileSize / scale;
			
			height = Game::getInstance()->getMap()->getAltitude(mapAltX, mapAltY);

			// we have this tile, but we need to shift the position based on the camera position
			offsetX = (startX % tileSize);
			offsetY = (startY % tileSize);
			cX = i - cameraX - offsetX;
			cY = j - cameraY - offsetY;

			// an equator bug exists where when you are within a few "tileSize" X or Y values of 0, the map gets pretty crazy
			// also a low Y value seems to cause the map generator to crash because it is trying to get a negative pixel value
			// (like it isn't being translated accordingly)

			// Height goes 0 to 255
			if (height > 120) texture = "shallows";
			if (height > 130) texture = "sand";
			if (height > 140) texture = "grass";
			if (height > 210) texture = "dirt";
			if (height > 230) texture = "rock";
			if (height > 250) texture = "snow";
			
			TextureManager::getInstance()->draw(texture, cX, cY, tileSize, tileSize, Game::getInstance()->getRenderer());
		}
	}
}

void TerrainLayer::clean() {
	ObjectLayer::clean();
}
