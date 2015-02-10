#ifndef LOADERPARAMS_H
#define LOADERPARAMS_H

#include <string>

class LoaderParams {
public:

	LoaderParams(int x, int y, int width, int height, std::string textureId) : x(x), y(y), width(width), height(height), texture(textureId) {}


	int x;
	int y;
	int height;
	int width;
	std::string texture;


};

#endif