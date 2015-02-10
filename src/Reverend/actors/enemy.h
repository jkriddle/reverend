#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "../sdlgameobject.h"

class Enemy : public SDLGameObject {
public:
	Enemy(const LoaderParams* pParams);
	virtual void update();
	virtual void clean();
};


#endif