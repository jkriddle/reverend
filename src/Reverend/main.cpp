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
#include <time.h>
#include <noise\noise.h>
#include "noise\noiseutils.h"
#include "vector2d.h"
#include "map\mapgenerator.h"

SDL_Window* window_;
SDL_Renderer* renderer_;
SDL_Surface* terrain;
SDL_Texture* terrainTexture;
SDL_Surface* heightMap;
SDL_Texture* heightMapTexture;


const int windowX_ = 1280; // 720;
const int windowY_ = 720; // 360;
const int mapTileSize_ = 2; //(windowX_ / (double)windowY_);
MapGenerator* mapGen;
int mapX = 0;
int mapY = 0;
int seed;

bool initSystems() {
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	//Create window
	window_ = SDL_CreateWindow("Reverend", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowX_, windowY_, SDL_WINDOW_OPENGL); // SDL_WINDOW_FULLSCREEN
	if( window_ == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr){
		SDL_DestroyWindow(window_);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	return true;
}

void close() {
	window_ = NULL;
	renderer_ = NULL;

	SDL_Quit();
}

void render_player() {

	// Render screen view window
	/*double r = (double)windowX_ / (double)windowY_;  // 1280/720 = 1.7777
	double numTilesPerScreenX = windowX_ / screenTileSize_; // 1280 / 64 = 20
	double numTilesPerScreenY = windowY_ / screenTileSize_; // 720 / 64 = 11.25
*/
	// so we know that every screen is 20x11 tiles (of 64x64 size)
	// in this world map, each screen = 1 pixel. Thus we want a rectangle of 20x11

	// Render character
	SDL_Rect* rectToDraw = new SDL_Rect();
	
	int x = (windowX_ / 2) + (mapX * mapTileSize_) - (mapTileSize_ / (double)2); // get centerpoint of screen and add the map coordinates
	int y = (windowY_ / 2) + (-mapY * mapTileSize_) - (mapTileSize_ / (double)2); // get centerpoint of screen and add the map coordinates (mapY flipped since map coords are opposite for Y)

	rectToDraw->x = x;
	rectToDraw->y = y;
	rectToDraw->w = mapTileSize_;
	rectToDraw->h = mapTileSize_;
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 1.0);
	SDL_RenderDrawRect(renderer_, rectToDraw);
}

SDL_Texture* getSimpleHeightMapTexture(MapGenerator* mapGen, SDL_Surface* terrain) {
	for(int i = 0; i < windowX_; i+=mapTileSize_) {
		for(int j = 0; j < windowY_; j+=mapTileSize_) {
			int midX = i;
			int midY = j;
			double height = mapGen->getAltitude(midX, midY);
			utils::Color color = utils::Color (  10, 105, 201, 255); // deeps
			if (height > -0.050) color = utils::Color (12, 128, 247, 255); // shallows
			if (height > -0.100) color = utils::Color (221, 203, 117, 255); // sand
			if (height > 0.0725) color = utils::Color ( 61, 97, 10, 255); // grass
			if (height > 0.5050) color = utils::Color (104, 75, 46, 255); // dirt
			if (height > 0.7500) color = utils::Color (114, 112, 100, 255); // rock
			if (height > 0.9) color = utils::Color (255, 255, 255, 255); // snow

			SDL_Rect rectToDraw = { i, j, mapTileSize_, mapTileSize_};
			SDL_FillRect(terrain, &rectToDraw, SDL_MapRGBA(terrain->format, color.red, color.green, color.blue, 1.0));
		}
	}
	SDL_Texture* terrainTexture = SDL_CreateTextureFromSurface(renderer_, terrain);
	return terrainTexture;
}

void generateMapScreen() {
	mapGen->renderToFile("terrain.bmp");
	terrain = SDL_LoadBMP("terrain.bmp");
	terrainTexture = SDL_CreateTextureFromSurface(renderer_, terrain);
	heightMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);;
	heightMapTexture = getSimpleHeightMapTexture(mapGen, heightMap);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char **argv) 
{	
	if (!initSystems()) {
		return 0;
	}
	
	mapX = 0; //-90 to 90
	mapY = 0; //-180 to 180

	SDL_Surface* screen = SDL_GetWindowSurface(window_);

	/* Initialize random seed. Need larger seed than rand_max */
	srand(static_cast<int>(time(0)));
	unsigned int a = (rand() % (int)(RAND_MAX + 1));
	unsigned int b = (rand() % (int)(RAND_MAX + 1));
	
	seed = a*(RAND_MAX+1)+b;
	std::cout << a << " " << b << " " << seed << std::endl;

	seed = 0; // testing only	
	
	srand(seed);
    SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 1.0);
    SDL_RenderClear( renderer_ );

	////////////////////////////// HEIGHT MAP ///////////////////////////////////////////
	mapGen = new MapGenerator(windowX_, windowY_, seed);
	mapGen->generate(-90, 90, -180, 180);
	mapGen->renderToFile("terrain.bmp");
	
	// Not working yet
	//mapGen->renderToMemory(mem);
	//SDL_RWops* rwop = SDL_RWFromMem(mem, sizeof(mem));
	//terrain = SDL_LoadBMP_RW( rwop, 0 );
	//terrainTexture = SDL_CreateTextureFromSurface(renderer_, terrain);

	terrain = SDL_LoadBMP("terrain.bmp");
	terrainTexture = SDL_CreateTextureFromSurface(renderer_, terrain);

	// Render Height Map
	heightMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);
	heightMapTexture = getSimpleHeightMapTexture(mapGen, heightMap);
	
	bool quit = false;
	SDL_Event ev;

	double numTilesPerScreenX = windowX_; // windowX_ / screenTileSize_; // 1280 / 64 = 20
	double numTilesPerScreenY = windowY_; // windowY_ / screenTileSize_; // 720 / 64 = 11.25

	bool heightMapOn = true;
	bool zoomedOut = true;
	
	generateMapScreen();

	while (!quit) {
		while (SDL_PollEvent(&ev)) {
			SDL_RenderClear(renderer_);
			SDL_RenderCopy(renderer_, terrainTexture, NULL, NULL);

			switch(ev.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					SDL_Keycode keyPressed = ev.key.keysym.sym;
					switch (keyPressed)
					{
						case SDLK_a:
							mapX--;
							break;
						case SDLK_s:
							mapY--;
							break;
						case SDLK_d:
							mapX++;
							break;
						case SDLK_w:
							mapY++;
							break;
						case SDLK_h:
							heightMapOn = !heightMapOn;
							break;
						case SDLK_z:
							// zoom out to world
							if (!zoomedOut) {
								std::cout << "Zooming out..." << std::endl;
								zoomedOut = true;
								mapGen->generate(-90, 90, -180, 180);
								generateMapScreen();
							} else {
								std::cout << "Zooming in..." << std::endl;
								zoomedOut = false;
							}
							break;
					}
					break;
			}
			
			if (mapX < -180) mapX = 180;
			else if (mapX > 180) mapX = -180;
			
			if (mapY < -90) mapY = 90;
			else if (mapY > 90) mapY = -90;
			
			std::cout << "Map position: " << mapX << "," << mapY << std::endl;

			if (heightMapOn) {
				SDL_RenderCopyEx(renderer_, heightMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_VERTICAL);
			}

			if (zoomedOut) {
				render_player();
			} else {
				mapGen->generate(mapX, mapY);
				generateMapScreen();
			}
			
			SDL_RenderPresent( renderer_ );
		}
	}
	
    SDL_FreeSurface( screen );
    SDL_FreeSurface( terrain );
    screen = NULL;

    //Destroy window
    SDL_DestroyWindow( window_ );
    window_ = NULL;

    //Quit SDL subsystems
    SDL_Quit();

	return 0;
}