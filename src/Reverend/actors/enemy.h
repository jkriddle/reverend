#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/gameobject.h"

class Enemy : public GameObject {
public:
	Enemy();
	Enemy(const LoaderParams* pParams);
};


#endif