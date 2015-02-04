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

const int windowX_ = 720; // 720;
const int windowY_ = 360; // 360;
const int mapTileSize_ = 2; //(windowX_ / (double)windowY_);
MapGenerator* overviewMapGen;
MapGenerator* tileMapGen;
int mapX = 0; //-90 to 90
int mapY = 3; //-180 to 180

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

SDL_Texture* getTileMapTexture(SDL_Surface* terrain) {
	int tileSize = 32;

	for(int i = 0; i < windowX_; i+=mapTileSize_) {
		for(int j = 0; j < windowY_; j+=mapTileSize_) {
			
			int x = i * (tileSize / mapTileSize_);
			int y = j * (tileSize / mapTileSize_);

			double height = tileMapGen->getAltitude(x, y);

			std::string texture = "water";
			if (height > -0.050) 
				texture = "shallows";
			if (height > -0.100) 
				texture = "sand";
			if (height > 0.0725) 
				texture = "grass";
			if (height > 0.5050) 
				texture = "dirt";
			if (height > 0.7500) 
				texture = "rock";
			if (height > 0.9) 
				texture = "snow";
			TextureManager::getInstance()->drawTile(texture.c_str(), 0, 0, x, y, 32, 32, 0, 0, tileRenderer_);
		}
	}

	return SDL_CreateTextureFromSurface(mapRenderer_, terrain);
}

void render_player() {

	// Render mapScreen view window
	/*double r = (double)windowX_ / (double)windowY_;  // 1280/720 = 1.7777
	double numTilesPerScreenX = windowX_ / screenTileSize_; // 1280 / 64 = 20
	double numTilesPerScreenY = windowY_ / screenTileSize_; // 720 / 64 = 11.25
*/
	// so we know that every mapScreen is 20x11 tiles (of 64x64 size)
	// in this world map, each mapScreen = 1 pixel. Thus we want a rectangle of 20x11

	// Render character
	SDL_Rect* rectToDraw = new SDL_Rect();
	
	int x = (windowX_ / 2) + (mapX * mapTileSize_) - (mapTileSize_ / (double)2); // get centerpoint of mapScreen and add the map coordinates
	int y = (windowY_ / 2) + (-mapY * mapTileSize_) - (mapTileSize_ / (double)2); // get centerpoint of mapScreen and add the map coordinates (mapY flipped since map coords are opposite for Y)

	rectToDraw->x = x;
	rectToDraw->y = y;
	rectToDraw->w = mapTileSize_;
	rectToDraw->h = mapTileSize_;
	SDL_SetRenderDrawColor(mapRenderer_, 255, 0, 0, 1.0);
	SDL_RenderDrawRect(mapRenderer_, rectToDraw);
}

SDL_Texture* getSimpleHeightMapTexture(MapGenerator* map, SDL_Renderer* renderer, SDL_Surface* terrain) {
	for(int i = 0; i < windowX_; i++) {
		for(int j = 0; j < windowY_; j++) {
			int midX = i;
			int midY = j;
			double height = map->getAltitude(midX, midY);

			// Height goes 0 to 255
			int max = 255;
			

			utils::Color color = utils::Color (  10, 105, 201, 255); // deeps
			if (height > 120) color = utils::Color (12, 128, 247, 255); // shallows
			if (height > 130) color = utils::Color (221, 203, 117, 255); // sand
			if (height > 140) color = utils::Color ( 61, 97, 10, 255); // grass
			if (height > 210) color = utils::Color (104, 75, 46, 255); // dirt
			if (height > 230) color = utils::Color (114, 112, 100, 255); // rock
			if (height > 250) color = utils::Color (255, 255, 255, 255); // snow*/

			SDL_Rect rectToDraw = { i, j, mapTileSize_, mapTileSize_};
			SDL_FillRect(terrain, &rectToDraw, SDL_MapRGBA(terrain->format, color.red, color.green, color.blue, 1.0));
		}
	}
	return SDL_CreateTextureFromSurface(renderer, terrain);
}

void generateMapScreen() {
	terrain = SDL_LoadBMP("terrain.bmp");
	terrainTexture = SDL_CreateTextureFromSurface(mapRenderer_, terrain);
}

void generateTileMapScreen() {
	tileMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);;
	tileMapTexture = getTileMapTexture(tileMap);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char **argv) 
{	
	if (!initSystems()) {
		return 0;
	}
		
	SDL_Surface* mapScreen = SDL_GetWindowSurface(mapWindow_);
	SDL_Surface* tileScreen = SDL_GetWindowSurface(tileWindow_);

	/* Initialize random seed. Need larger seed than rand_max */
	srand(static_cast<int>(time(0)));
	unsigned int a = (rand() % (int)(RAND_MAX + 1));
	unsigned int b = (rand() % (int)(RAND_MAX + 1));
	
	seed = a*(RAND_MAX+1)+b;
	std::cout << a << " " << b << " " << seed << std::endl;

	seed = 0; // testing only	
	
	srand(seed);

	
    SDL_SetRenderDrawColor( mapRenderer_, 0, 0, 0, 1.0);
    SDL_RenderClear( mapRenderer_ );

    SDL_SetRenderDrawColor( tileRenderer_, 0, 0, 0, 1.0);
    SDL_RenderClear( tileRenderer_ );

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
	//tileMapGen->generate(0, 30, 0, 30);
	//tileMapGen->renderToFile("player_map.bmp");

	// Now read the image
	/* load BMP file */
	tileMapGen->loadAltitudeMap("player_map.bmp");
	
	tileMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);
	tileMapTexture = getSimpleHeightMapTexture(tileMapGen, tileRenderer_, tileMap);
	
	
	SDL_RenderClear(mapRenderer_);
	SDL_RenderCopyEx(mapRenderer_, heightMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent( mapRenderer_ );

	SDL_RenderClear(tileRenderer_);
	SDL_RenderCopyEx(tileRenderer_, tileMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent( tileRenderer_ );

	SDL_Event evt;
	bool q=  false;
	while (!q) {
		while (SDL_PollEvent(&evt)) {
			switch(evt.key.type) {
				case SDL_QUIT:
					q = true;
					break;
				default:
					SDL_RenderClear(mapRenderer_);
					SDL_RenderCopyEx(mapRenderer_, heightMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
					SDL_RenderPresent( mapRenderer_ );

					SDL_RenderClear(tileRenderer_);
					SDL_RenderCopyEx(tileRenderer_, tileMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
					SDL_RenderPresent( tileRenderer_ );

					break;
			}
		}
	}

	SDL_Quit();
	return 0;
	
	//terrain = SDL_LoadBMP("terrain.bmp");
	//terrainTexture = SDL_CreateTextureFromSurface(mapRenderer_, terrain);

	//overviewMapGen->saveToDisk("mapdata.txt");

	//overviewMapGen->readFromDisk("mapdata.txt");
	
	//tileMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);
	//tileMapTexture = getTileMapTexture(tileMap);
	
	bool quit = false;
	SDL_Event ev;

	double numTilesPerScreenX = windowX_; // windowX_ / screenTileSize_; // 1280 / 64 = 20
	double numTilesPerScreenY = windowY_; // windowY_ / screenTileSize_; // 720 / 64 = 11.25
	
	//overviewMapGen->generate(mapX, mapY);
	
	// Render Height Map
	heightMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);
	heightMapTexture = getSimpleHeightMapTexture(overviewMapGen, mapRenderer_, heightMap);

	bool zoomedOut = true;
	SDL_Keycode keyPressed = NULL;
	generateMapScreen();
	
	//generateTileMapScreen();
	
	while (!quit) {
		while (SDL_PollEvent(&ev)) {
			switch(ev.key.type) {
				case SDL_QUIT:
					quit = true;
					break;
				default:
					SDL_RenderClear(tileRenderer_);
					SDL_RenderClear(mapRenderer_);
			
					SDL_RenderCopyEx(mapRenderer_, heightMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
					SDL_RenderCopyEx(tileRenderer_, tileMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);

					render_player();
			
					SDL_RenderPresent( tileRenderer_ );
					SDL_RenderPresent( mapRenderer_ );
					break;
			}
		}
	}
	
	SDL_Delay(3000);
	
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

    //Quit SDL subsystems
    SDL_Quit();

	return 0;
}