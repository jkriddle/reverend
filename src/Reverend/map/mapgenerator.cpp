#include "mapgenerator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

MapGenerator::MapGenerator(int width, int height, int seed) {
	mapRenderer_ = new MapRenderer();
	width_ = width;
	height_ = height;
	seed_ = seed;
}

void MapGenerator::saveToDisk(std::string fileName) {
	
	/*
	std::ofstream myfile;
	myfile.clear();
	myfile.open(fileName);
	for(int i = 0; i < width_; i++) {
		for(int j = 0; j < height_; j++) {
			double h = heightMap_.GetValue(i, j);
			myfile << std::setw(4) << i << std::setw(4) << j << std::setw(15) << std::setprecision(5) << h << std::endl;
		}
	}
	myfile.close();*/
}


void MapGenerator::readFromDisk(std::string fileName) {
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	pFile = fopen ( fileName.c_str() , "rb" );
	if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	// copy the file into the buffer:
	result = fread (buffer,1,lSize,pFile);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

	/* the whole file is now loaded in the memory buffer. */
	std::string contents(buffer);
	// 4 + 4 + 15 + 2(\r\n)

	// this takes too long. need to just read from raw data
	for(int i = 0; i < result; i+=25) {
		// each line is 15 chars long
		int x = stoi(contents.substr(i, 4));
		int y = stoi(contents.substr(i+4, 4));
		double h = stod(contents.substr(i+8, 15));
		mapPoints_[x][y] = h;
	}
	// terminate
	fclose (pFile);
	free (buffer);
	

	/*std::ifstream is (fileName, std::ifstream::binary);
	if (is) {
		std::string    line;
		while(std::getline(is, line))
		{
			std::string arr[3];
			int i = 0;
			std::stringstream ssin(line);
			while (ssin.good() && i < 3){
				ssin >> arr[i];
				++i;
			}

			mapPoints_[std::stoi(arr[0])][std::stoi(arr[1])] = std::stod(arr[2]);
		}
	}
	is.close();*/
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
	return mapPoints_[x][y];
}
	

void MapGenerator::renderToFile(std::string fileName) {
	mapRenderer_->renderToFile(heightMap_, fileName);
}
void MapGenerator::renderToMemory(std::ostringstream &mem) {
	mapRenderer_->renderToMemory(heightMap_, mem);
}