#ifndef LOADERPARAMS_H
#define LOADERPARAMS_H

#include <string>

class LoaderParams {
public:

	LoaderParams(int x, int y, int width, int height, std::string textureId) : x_(x), y_(y), width_(width), height_(height), textureId_(textureId) {}
	int getX() const { return x_; }
	int getY() const { return y_; }
	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
	std::string getTextureId() const { return textureId_; }

private:

	int x_;
	int y_;

	int height_;
	int width_;

	std::string textureId_;

};

#endif