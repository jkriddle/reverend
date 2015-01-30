#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL/SDL.h>
#include "cleanup.h"
#include <string>
#include "texturemanager.h"

/*
enum GameDirection {
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST
};
*/

class GameObject {
public:
	virtual void load(int x, int y, int width, int height, std::string textureID);
	virtual void draw(SDL_Renderer* pRenderer);
	virtual void update();
	virtual void clean();
protected:
	std::string textureId_;
	
	int currentTextureFrame_;
	int currentTextureRow_;

	int x_;
	int y_;

	int width_;
	int height_;
};

#endif