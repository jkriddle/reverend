#include <iostream>
#include <sstream>
#include <noise\noise.h>
#include "..\noise\noiseutils.h"
#include "maprenderer.h"

class MapGenerator {

public:
	MapGenerator(int width, int height, int seed);

	// Generate a new map based on provided seed
	void generate(int x, int y);

	// Generate a new map based on boundaries/seed
	void generate(int southBound, int northBound, int westBound, int eastBound);
	
	// Retrieve map height at location
	double getAltitude(int x, int y);
	
	// Retrieve map moisture at location
	double getMoisture(int x, int y);

	// Zoom factor defaults to 1
	void setZoom(int zoomFactor);
	
	// Render the map to specified file
	void renderToFile(std::string fileName);
	
	// Render the map to memory stream
	void renderToMemory(std::ostringstream &mem);

private:
	noise::utils::NoiseMap heightMap_;
	noise::utils::NoiseMapBuilderSphere heightMapBuilder_;
	MapRenderer* mapRenderer_;
	int width_;
	int height_;
	int seed_;
};