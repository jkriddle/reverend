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
const int windowX_ = 1280;
const int windowY_ = 720;
const int screenTileSize_ = 64;
const int mapTileSize_ = 1;

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
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
	SDL_RenderDrawPoint(renderer_, x, y);
}
 
void fill_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:
 
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;
 
    while (x >= y)
    {
        set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);
 
        if (x != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }
 
        if (y != 0)
        {
            set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }
 
        if (x != 0 && y != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }
 
        error += y;
        ++y;
        error += y;
 
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void render_player(int x, int y, int tileSize) {

	// Render screen view window
	double r = (double)windowX_ / (double)windowY_;  // 1280/720 = 1.7777
	double numTilesPerScreenX = windowX_ / screenTileSize_; // 1280 / 64 = 20
	double numTilesPerScreenY = windowY_ / screenTileSize_; // 720 / 64 = 11.25

	// so we know that every screen is 20x11 tiles (of 64x64 size)
	// in this world map, each screen = 1 pixel. Thus we want a rectangle of 20x11

	// Render character
	SDL_Rect* rectToDraw = new SDL_Rect();
	rectToDraw->x = x;
	rectToDraw->y = y;
	rectToDraw->w = numTilesPerScreenX;
	rectToDraw->h = numTilesPerScreenY;
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 1.0);
	SDL_RenderDrawRect(renderer_, rectToDraw);

}

SDL_Texture* getSimpleHeightMapTexture(MapGenerator* mapGen, SDL_Surface* terrain) {
	for(int i = 0; i < windowX_; i+=mapTileSize_) {
		for(int j = 0; j < windowY_; j+=mapTileSize_) {
			int midX = i;
			int midY = j;
			double height = mapGen->getAltitude(midX, midY);
			utils::Color color = utils::Color (  0,   0, 128, 255); // deeps
			if (height > -0.100) color = utils::Color (240, 240,  64, 255); // sand
			if (height > 0.0725) color = utils::Color ( 32, 160,   0, 255); // grass
			if (height > 0.5050) color = utils::Color (139, 69, 19, 255); // dirt
			if (height > 0.7500) color = utils::Color (128, 128, 128, 255); // rock
			if (height > 0.9) color = utils::Color (255, 255, 255, 255); // snow

			SDL_Rect rectToDraw = { i, j, mapTileSize_, mapTileSize_};
			SDL_FillRect(terrain, &rectToDraw, SDL_MapRGBA(terrain->format, color.red, color.green, color.blue, 1.0));
		}
	}
	SDL_Texture* terrainTexture = SDL_CreateTextureFromSurface(renderer_, terrain);
	return terrainTexture;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char **argv) 
{	
	if (!initSystems()) {
		return 0;
	}

	SDL_Surface* screen = SDL_GetWindowSurface(window_);

	/* Initialize random seed. Need larger seed than rand_max */
	srand(static_cast<int>(time(0)));
	unsigned int a = (rand() % (int)(RAND_MAX + 1));
	unsigned int b = (rand() % (int)(RAND_MAX + 1));
	unsigned int seed = a*(RAND_MAX+1)+b;
	std::cout << a << " " << b << " " << seed << std::endl;

	seed = 0; // testing only	
	
	srand(seed);
    SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 1.0);
    SDL_RenderClear( renderer_ );

	////////////////////////////// HEIGHT MAP ///////////////////////////////////////////
	MapGenerator* mapGen = new MapGenerator();
	mapGen->generate(windowX_, windowY_, seed);
	std::ostringstream mem;
	mapGen->renderToFile("terrain.bmp");

	
	// Not working yet
	//mapGen->renderToMemory(mem);
	//SDL_RWops* rwop = SDL_RWFromMem(mem, sizeof(mem));
	//SDL_Surface* terrain = SDL_LoadBMP_RW( rwop, 0 );
	//SDL_Texture* terrainTexture = SDL_CreateTextureFromSurface(renderer_, terrain);

	SDL_Surface* terrain = SDL_LoadBMP("terrain.bmp");
	SDL_Texture* terrainTexture = SDL_CreateTextureFromSurface(renderer_, terrain);

	// Render Height Map
	SDL_Surface* heightMap = SDL_CreateRGBSurface(SDL_SWSURFACE, windowX_, windowY_, 16 ,0,0,0,0);;
	SDL_Texture* heightMapTexture = nullptr;
	heightMapTexture = getSimpleHeightMapTexture(mapGen, heightMap);
	
	bool quit = false;
	SDL_Event ev;
	int pX = 512, pY = 320;
	render_player(pX, pY, mapTileSize_);
	SDL_RenderPresent( renderer_ );

	double numTilesPerScreenX = windowX_ / screenTileSize_; // 1280 / 64 = 20
	double numTilesPerScreenY = windowY_ / screenTileSize_; // 720 / 64 = 11.25

	bool heightMapOn = false;

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
							pX-= numTilesPerScreenX;
							break;
						case SDLK_s:
							pY+=numTilesPerScreenY;
							break;
						case SDLK_d:
							pX+= numTilesPerScreenX;
							break;
						case SDLK_w:
							pY-= numTilesPerScreenY;
							break;
						case SDLK_h:
							heightMapOn = !heightMapOn;
							break;
					}
					break;
				
			}

			if (pX < 0) {
				// change map
			} else if (pX >= windowX_) {
				// change map
			}

			if (pY < 0) {
				// change map
			} else if (pY >= windowY_) {
				// change map
			}
			if (heightMapOn) {
				SDL_RenderCopyEx(renderer_, heightMapTexture, NULL, NULL, NULL, NULL, SDL_FLIP_VERTICAL);
			}

			render_player(pX, pY, mapTileSize_);
			
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