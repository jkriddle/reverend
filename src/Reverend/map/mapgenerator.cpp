#include "mapgenerator.h"
#include "../engine/cleanup.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

MapGenerator::MapGenerator(int width, int height, int seed) {
	mapRenderer_ = NULL;
	mapRenderer_ = new MapRenderer();
	width_ = width;
	height_ = height;
	seed_ = seed;
}
MapGenerator::~MapGenerator() {
	delete mapRenderer_;
	mapRenderer_ = NULL;
	cleanup(altitudeMap_);
}

Uint32 MapGenerator::getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void MapGenerator::loadAltitudeMap(std::string fileName) {
	altitudeMap_ = SDL_LoadBMP(fileName.c_str());
}

// Generate map (default player view)
void MapGenerator::generate(int x, int y) {
	// find centers
	double r = width_ / (double)height_;
	int mx = (360 / (double)r) - 180;
	int my = (180 / (double)r) - 90;
	mx = x;
	my = y;
	int sx = 10;
	int sy = sx / r;
	std::cout << "Player map: " << x << "," << y << std::endl;
	std::cout << "Overworld translation: " << mx << "," << my << std::endl;
	generate(my - sy, my + sy, mx - sx, mx + sx);
}

void MapGenerator::generate(int southBound, int northBound, int westBound, int eastBound) {
	noise::module::Perlin module;
	module.SetSeed(seed_);
	//module.SetFrequency(.5);

	heightMapBuilder_.SetSourceModule (module);
	heightMapBuilder_.SetDestNoiseMap (heightMap_);

	// how big is the resulting image?
	heightMapBuilder_.SetDestSize(width_, height_);

	// where are we on the map?
	// south, north, west, east
	heightMapBuilder_.SetBounds (southBound, northBound, westBound, eastBound);
	std::cout << " Rendering map at S:" << southBound << ", N:" << northBound << ", W:" << westBound << ", E:" << eastBound << std::endl;

	heightMapBuilder_.Build ();
}

// Retrieve map height at location
double MapGenerator::getAltitude(int x, int y) {
	Uint32 pixel = getPixel(altitudeMap_, x, y);
	Uint8 red, green, blue;
	SDL_GetRGB(pixel, altitudeMap_->format, &red, &green, &blue);

	// since this is all grayscale we only need to return a single value
	return red;
}
	
void MapGenerator::renderToFile(std::string fileName) {
	mapRenderer_->renderToFile(heightMap_, fileName);
}