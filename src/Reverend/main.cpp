#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include <stdio.h>
#include <search.h>
#include <malloc.h>
#include "voronoi.h"
#include <iostream>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <random>
#include <time.h>
#include <noise\noise.h>
#include "noise\noiseutils.h"

SDL_Window* window_;
SDL_Renderer* renderer_;
const int windowX_ = 800;
const int windowY_ = 600;

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

	noise::module::Perlin myModule;
	myModule.SetSeed(seed);

	//double value = myModule.GetValue (2.50, 3,2.75);
	//std::cout << value << std::endl;
	
	
	/*
	noise::module::RidgedMulti mountainTerrain;

	// TODO: how do we generate less water??? SetBias?
	noise::module::Billow baseFlatTerrain;
	baseFlatTerrain.SetFrequency (2.0);

	noise::module::ScaleBias flatTerrain;
	flatTerrain.SetSourceModule (0, baseFlatTerrain);
	flatTerrain.SetScale (0.125);
	flatTerrain.SetBias (-0.75);

	noise::module::Perlin terrainType;
	terrainType.SetFrequency (0.5);
	terrainType.SetPersistence (0.25);

	noise::module::Select finalTerrain;
	finalTerrain.SetSourceModule (0, flatTerrain);
	finalTerrain.SetSourceModule (1, mountainTerrain);
	finalTerrain.SetControlModule (terrainType);
	finalTerrain.SetBounds (0.0, 1000.0);
	finalTerrain.SetEdgeFalloff (0.125);

	noise::utils::NoiseMap hm;
	noise::utils::NoiseMapBuilderPlane hmb;
	hmb.SetSourceModule (finalTerrain);
	hmb.SetDestNoiseMap (hm);*/
	noise::utils::NoiseMap hm;
	noise::utils::NoiseMapBuilderPlane hmb;
	hmb.SetSourceModule (myModule);
	hmb.SetDestNoiseMap (hm);

	// how big is the resulting image?
	hmb.SetDestSize (windowX_, windowY_);

	// where are we on the map?
	hmb.SetBounds(0, 4, 0, 4);
	hmb.Build ();

	noise::utils::RendererImage renderer;
	noise::utils::Image image;
	renderer.SetSourceNoiseMap (hm);
	renderer.SetDestImage (image);
	renderer.ClearGradient ();
  
	/*
	renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
	renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
	renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
	renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
	renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
	renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
	renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
	renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
	*/

	renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
	renderer.AddGradientPoint (-0.5500, utils::Color (240, 240,  64, 255)); // sand
	renderer.AddGradientPoint ( 0.0625, utils::Color ( 32, 160,   0, 255)); // grass
	renderer.AddGradientPoint ( 0.3750, utils::Color (139, 69, 19, 255)); // dirt
	renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
	renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow


	renderer.Render ();
	utils::WriterBMP writer;
	writer.SetSourceImage (image);
	writer.SetDestFilename ("terrain.bmp");
	writer.WriteDestFile ();

	SDL_Surface* terrain = SDL_LoadBMP("terrain.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, terrain);
	SDL_FreeSurface(terrain);
	
    SDL_RenderCopy(renderer_, texture, NULL, NULL);

    SDL_RenderPresent( renderer_ );

	
	//////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////// VORONOI ///////////////////////////////////////////

    
		
	const int count = 400;
	const int dotRadius = 3;

	float xValues[count];
	int min = dotRadius; // must be larger than fill_circle radius parameter
	int max = windowX_ - dotRadius; // must be larger than fill_circle radius parameter
	for(int i = 0; i < count; i++) {
			xValues[i] = rand() % (max - min + 1) + min;
	}

	max = windowY_ - dotRadius;
	float yValues[count];
	for(int i = 0; i < count; i++) {
		yValues[i] = rand() % (max - min + 1) + min;
	}
	
	// dots
	/*SDL_SetRenderDrawColor( renderer_, 255, 0, 0, 1.0);
	for(int i = 0; i < count; i++) {
		Uint32* pixel = new Uint32[windowX_ * windowY_];
		fill_circle(screen, xValues[i], yValues[i], dotRadius, *pixel);
	}*/

	SDL_SetRenderDrawColor( renderer_, 255, 255, 255, 1.0);
	VoronoiDiagramGenerator vdg;
	vdg.generateVoronoi(xValues,yValues,count, 0, windowX_, 0, windowY_, 1);

	vdg.resetIterator();

	float x1,y1,x2,y2;

	printf("\n-------------------------------\n");
	while(vdg.getNext(x1,y1,x2,y2))
	{
		//printf("GOT Line (%f,%f)->(%f,%f)\n",x1,y1,x2, y2);
		SDL_RenderDrawLine( renderer_, x1, y1, x2, y2);
	}

	
    //Update screen
    SDL_RenderPresent( renderer_ );


	// Wait
	int x = 0;
	std::cin >> x;

	
    SDL_FreeSurface( screen );
    screen = NULL;

    //Destroy window
    SDL_DestroyWindow( window_ );
    window_ = NULL;

    //Quit SDL subsystems
    SDL_Quit();

	return 0;
}