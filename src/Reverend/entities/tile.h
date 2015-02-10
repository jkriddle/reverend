#pragma once

#ifndef TILE_H
#define TILE_H

#include "../gameobject.h"

class Tile : public GameObject {

public:
	Tile(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual int getX() { return (int)position_.getX(); }
	virtual int getY() { return (int)position_.getX(); }
private:
	Vector2d position_;
};

#endif