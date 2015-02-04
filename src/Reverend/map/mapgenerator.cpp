#include "mapgenerator.h"

MapGenerator::MapGenerator(int width, int height, int seed) {
	mapRenderer_ = new MapRenderer();
	width_ = width;
	height_ = height;
	seed_ = seed;
}

// Generate map (default player view)
void MapGenerator::generate(int x, int y) {
	// find centers
	double r = width_ / (double)height_;
	int mx = (360 / (double)r) - 180;
	int my = (180 / (double)r) - 90;
	mx = x;
	my = y;
	std::cout << "Player map: " << x << "," << y << std::endl;
	std::cout << "Overworld translation: " << mx << "," << my << std::endl;
	generate(my, my + 1, mx, mx + 1);
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
	return heightMap_.GetValue(x, y);
}
	

void MapGenerator::renderToFile(std::string fileName) {
	mapRenderer_->renderToFile(heightMap_, fileName);
}
void MapGenerator::renderToMemory(std::ostringstream &mem) {
	mapRenderer_->renderToMemory(heightMap_, mem);
}