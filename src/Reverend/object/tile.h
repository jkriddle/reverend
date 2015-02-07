#pragma once
#ifndef TILE_H
#define TILE_H

#include "sdlgameobject.h"

class Tile : public SDLGameObject {

public:
	Tile(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual int getX() { return position_.getX(); }
	virtual int getY() { return position_.getX(); }
private:
	Vector2d position_;
};

#endif