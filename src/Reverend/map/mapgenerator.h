#include <iostream>
#include <sstream>
#include <noise\noise.h>
#include "..\noise\noiseutils.h"
#include "maprenderer.h"
#include <map>

class MapPoint {

public:
	int x;
	int y;
	int getAltitude() { return altitude_; }

private:
	int altitude_;

};

class MapGenerator {

public:
	MapGenerator(int width, int height, int seed);
	~MapGenerator();

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
	void loadAltitudeMap(std::string fileName);

private:
	
	Uint32 getPixel(SDL_Surface *surface, int x, int y);

	noise::utils::NoiseMap heightMap_;
	noise::utils::NoiseMapBuilderSphere heightMapBuilder_;
	MapRenderer* mapRenderer_;
	int width_;
	int height_;
	int seed_;
	SDL_Surface* altitudeMap_;
};