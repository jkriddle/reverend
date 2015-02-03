#include "mapgenerator.h"

MapGenerator::MapGenerator() {
	mapRenderer_ = new MapRenderer();
}

void MapGenerator::generate(int x, int y, int width, int height, int seed) {
	noise::module::Perlin module;
	module.SetSeed(seed);

	heightMapBuilder_.SetSourceModule(module);
	heightMapBuilder_.SetDestNoiseMap(heightMap_);

	// how big is the resulting image?
	heightMapBuilder_.SetDestSize(width, height);

	// where are we on the map?
	heightMapBuilder_.SetBounds(x, x+1, y, y+1);
	std::cout << " Rendering map at " << x << "," << y << " to " << x+1 << "," << y+1 << std::endl;

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