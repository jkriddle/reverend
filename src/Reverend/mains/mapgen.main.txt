#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include <stdio.h>
#include <search.h>
#include <malloc.h>
#include "voronoi.h"
#include <iostream>
#include <sstream>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <random>
#include <tuple>
#include <time.h>
#include <noise\noise.h>
#include "noise\noiseutils.h"
#include "vector2d.h"
#include "map\mapgenerator.h"
#include "texturemanager.h"
#include "camera.h"

SDL_Window* mapWindow_;
SDL_Window* tileWindow_;
SDL_Renderer* mapRenderer_;
SDL_Renderer* tileRenderer_;
SDL_Surface* terrain;
SDL_Texture* terrainTexture;
SDL_Surface* tileMap;
SDL_Texture* tileMapTexture;
SDL_Surface* heightMap;
SDL_Texture* heightMapTexture;
Camera* camera;

const int windowX_ = 640; // 720;
const int windowY_ = 320; // 360;
const int mapTileSize_ = 2; //(windowX_ / (double)windowY_);
MapGenerator* overviewMapGen;
MapGenerator* tileMapGen;
int pX = 0;
int pY = 0;

int seed;

bool initSystems() {
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	//Create window
	tileWindow_ = SDL_CreateWindow("Tile Map", 0, 20, windowX_, windowY_, SDL_WINDOW_OPENGL); // SDL_mapWindow_FULLSCREEN
	if( tileWindow_ == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	mapWindow_ = SDL_CreateWindow("Height Map", windowX_/2, 20, windowX_, windowY_, SDL_WINDOW_OPENGL); // SDL_mapWindow_FULLSCREEN
	if( mapWindow_ == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	tileRenderer_ = SDL_CreateRenderer(tileWindow_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (tileRenderer_ == nullptr){
		SDL_DestroyWindow(tileWindow_);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	mapRenderer_ = SDL_CreateRenderer(mapWindow_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mapRenderer_ == nullptr){
		SDL_DestroyWindow(mapWindow_);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	return true;
}

void close() {
	mapWindow_ = NULL;
	mapRenderer_ = NULL;
	tileWindow_ = NULL;
	tileRenderer_ = NULL;
	SDL_Quit();
}
int rm = 0;
int lm = 0;
void renderTileMap(MapGenerator* map, SDL_Renderer* renderer, SDL_Surface* terrain, int scale = 1) {
	int tileSize = 32;
	/*
	int startX = (-1 * tileSize) + camera->getPosition().getX();
	int startY = (-1 * tileSize) + camera->getPosition().getY();

	// always render one extra tile since movement is non-tile based. Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX + windowX_ + (2 * tileSize);
	int mY = startY + windowY_ + (2 * tileSize);
	*/
	
	int startX = (-1*tileSize) + camera->getPosition().getX(); // (-1 * tileSize) + camera->getPosition().getX();
	int startY = (-1*tileSize) + camera->getPosition().getY(); //(-1 * tileSize) + camera->getPosition().getY();

	// always render one extra tile since movement is non-tile based. Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX + windowX_ + (1 * tileSize);
	int mY = startY + windowY_ + (1 * tileSize);

	// if we are showing tiles
	// 100, 100, 120, 120
	// we want to actualy load 80, 80, 140, 140
	
	for(int i = startX; i <= mX; i+=tileSize) { // for 0 through 720, every 32 px
		for(int j = startY; j <= mY; j+=tileSize) { // for 0 through 360, every 32 px

			int mapAltX = i;
			int mapAltY =  j;
			
			if (mapAltX != 0) mapAltX = i / tileSize / scale;
			if (mapAltY != 0) mapAltY = j / tileSize / scale;
			double height = map->getAltitude(mapAltX, mapAltY);

			// we have this tile, but we need to shift the position based on the camera position
			int offsetX = (startX % tileSize);
			int offsetY = (startY % tileSize);
			int cX = i - camera->getPosition().getX() - offsetX;
			int cY = j - camera->getPosition().getY() - offsetY;
			
			// an equator bug exists where when you are within a few "tileSize" Y values of 0, the lower tiles are drawn a tilesize too high.

			if (lm != pX || rm != pY) {
				std::cout << "x, y: " << camera->getPosition().getX() << "," << camera->getPosition().getY() << std::endl;
				std::cout << "startX, startY: " << startX << "," << startY << std::endl;
				std::cout << "mX, mY: " << mX << "," << mY << std::endl;
				//std::cout << "mapAltX, mapAltX: " << mapAltX << "," << mapAltY << std::endl;
				std::cout << "offsetX: " << offsetX << std::endl;
				std::cout << "offsetY: " << offsetY << std::endl;
				std::cout << "cX, cY: " << cX << "," << cY << std::endl << std::endl;
				lm = pX;
				rm = pY;
			}

			// Height goes 0 to 255
			int max = 255;
			
			std::string texture = "water";
			if (height > 120) texture = "shallows";
			if (height > 130) texture = "sand";
			if (height > 140) texture = "grass";
			if (height > 210) texture = "dirt";
			if (height > 230) texture = "rock";
			if (height > 250) texture = "snow";
			
			TextureManager::getInstance()->draw(texture.c_str(), cX, cY, tileSize, tileSize, renderer);
		}
	}
}

void render_player() {
	// For now this will always be 0,0 (i.e. camera is pointed directly at player)
	int centerX = windowX_ / (double)2;
	int centerY = windowY_ / (double)2;
	int cX = camera->getPosition().getX();
	int cY = camera->getPosition().getY();
	int tX = pX - cX;
	int tY = pY - cY;
	TextureManager::getInstance()->draw("player", tX + centerX, tY + centerY, 32, 32, tileRenderer_);
}

SDL_Texture* getSimpleHeightMapTexture(MapGenerator* map, SDL_Renderer* renderer, SDL_Surface* terrain, int x = 0, int y = 0, int scale = 1) {
	for(int i = 0; i < windowX_; i+=scale) { // for 0 through 72, every 10 px
		for(int j = 0; j < windowY_; j+=scale) { // for 0 through 36, every 10 px
			int midX = i;
			int midY = j;
			
			// we want a single pixel on the height map
			if (midX > 0) midX = i / scale;
			if (midY > 0) midY = j / scale;
			double height = map->getAltitude(midX + x, midY + y);

			// Height goes 0 to 255
			int max = 255;
			

			utils::Color color = utils::Color (  10, 105, 201, 255); // deeps
			if (height > 120) color = utils::Color (12, 128, 247, 255); // shallows
			if (height > 130) color = utils::Color (221, 203, 117, 255); // sand
			if (height > 140) color = utils::Color ( 61, 97, 10, 255); // grass
			if (height > 210) color = utils::Color (104, 75, 46, 255); // dirt
			if (height > 230) color = utils::Color (114, 112, 100, 255); // rock
			if (height > 250) color = utils::Color (255, 255, 255, 255); // snow*/

			CameraRect bounds = camera->getTileBounds(32);
			int cX = camera->getTileOffset(32).getX();
			int cY = camera->getTileOffset(32).getX();

			SDL_Rect rectToDraw = { i, j, scale, scale}; // draw a box = scale setting
			SDL_FillRect(terrain, &rectToDraw, SDL_MapRGBA(terrain->format, color.red, color.green, color.blue, 1.0));
		}
	}
	return SDL_CreateTextureFromSurface(renderer, terrain);
}

void generateMapScreen() {
	terrain = SDL_LoadBMP("terrain.bmp");
	terrainTexture = SDL_CreateTextureFromSurface(mapRenderer_, terrain);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char **argv) 
{	
	if (!initSystems()) {
		return 0;
	}
		
	int x = 0;
	int y = 0;
	int scale = 5;
		
	SDL_Surface* mapScreen = SDL_GetWindowSurface(mapWindow_);
	SDL_Surface* tileScreen = SDL_GetWindowSurface(tileWindow_);

	camera = new Camera(windowX_, windowY_, 1.0f);
	camera->goTo(pX, pY);

	/* Initialize random seed. Need larger seed than rand_max */
	srand(static_cast<int>(time(0)));
	unsigned int a = (rand() % (int)(RAND_MAX + 1));
	unsigned int b = (rand() % (int)(RAND_MAX + 1));
	
	seed = a*(RAND_MAX+1)+b;

	seed = 0; // testing only	
	srand(seed);
	
    SDL_SetRenderDrawColor( mapRenderer_, 0, 0, 0, 1.0);
    SDL_RenderClear( mapRenderer_ );

    SDL_SetRenderDrawColor( tileRenderer_, 0, 0, 0, 1.0);
    SDL_RenderClear( tileRenderer_ );
	
	TextureManager::getInstance()->load("assets/textures/player_sm.png", "player", tileRenderer_);
	TextureManager::getInstance()->load("assets/textures/water.png", "water", tileRenderer_);
	TextureManager::getInstance()->load("assets/textures/shallows.png", "shallows", tileRenderer_);
	TextureManager::getInstance()->load("assets/textures/sand.png", "sand", tileRenderer_);
	TextureManager::getInstance()->load("assets/textures/grass.png", "grass", tileRenderer_);
	TextureManager::getInstance()->load("assets/textures/dirt.png", "dirt", tileRenderer_);
	TextureManager::getInstance()->load("assets/textures/rock.png", "rock", tileRenderer_);
	TextureManager::getInstance()->load("assets/textures/snow.png", "snow", tileRenderer_);
	
	////////////////////////////// HEIGHT MAP ///////////////////////////////////////////
	// Let's make a large world map of 720*2 by 360*2 (scale of 2..i.e. each pixel is 2 screens)
	overviewMapGen = new MapGenerator(windowX_, windowY_, seed);
	//overviewMapGen->generate(-90, 90, -180, 180);
	//overviewMapGen->renderToFile("overworld.bmp");

	// Now read the image
	/* load BMP file */
	overviewMapGen->loadAltitudeMap("overworld.bmp");
	
	heightMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);
	heightMapTexture = getSimpleHeightMapTexture(overviewMapGen, mapRenderer_, heightMap);

	//-------------------------------------------------------
	tileMapGen = new MapGenerator(windowX_, windowY_, seed);

	// Now read the image
	tileMapGen->loadAltitudeMap("overworld.bmp");
	tileMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);
	
	camera->goTo(pX, pY);
	camera->update();

	SDL_Event evt;
	bool q =  false;
	while (!q) {
		while (SDL_PollEvent(&evt)) {
			switch(evt.key.type) {
				case SDL_QUIT:
					q = true;
					break;
				case SDL_KEYDOWN:
					switch(evt.key.keysym.scancode) {
					case SDL_SCANCODE_D:
						pX+=1;
						camera->goTo(pX, pY);
						camera->update();
						break;
					case SDL_SCANCODE_A:
						pX-=1;
						camera->goTo(pX, pY);
						camera->update();
						break;
					case SDL_SCANCODE_W:
						pY-=1;
						camera->goTo(pX, pY);
						camera->update();
						break;
					case SDL_SCANCODE_S:
						pY+=1;
						camera->goTo(pX, pY);
						camera->update();
						break;
					}
					break;
			}
		}
		
						
		SDL_RenderClear(mapRenderer_);
		SDL_RenderClear(tileRenderer_);
		SDL_RenderCopyEx(mapRenderer_, heightMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
		renderTileMap(tileMapGen, tileRenderer_, tileMap, scale);
		render_player();
		SDL_RenderPresent( tileRenderer_ );
		SDL_RenderPresent( mapRenderer_ );
	}

	SDL_Quit();

	SDL_FreeSurface( mapScreen );
    SDL_FreeSurface( tileScreen );
    SDL_FreeSurface( terrain );

    mapScreen = NULL;
    tileScreen = NULL;

    //Destroy windows
    SDL_DestroyWindow( mapWindow_ );
    mapWindow_ = NULL;
    SDL_DestroyWindow( tileWindow_ );
    tileWindow_ = NULL;

	return 0;

}