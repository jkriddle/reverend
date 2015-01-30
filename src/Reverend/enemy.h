#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"

class Enemy : public GameObject {
public:
	void load(int x, int y, int width, int height, std::string textureId);
	void draw(SDL_Renderer* renderer);
	void update();
	void clean();
};

#endif