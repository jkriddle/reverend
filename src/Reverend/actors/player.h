#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/gameobject.h"
#include "../engine/component/animatedsprite.h"

class Player : public GameObject {

public:
	Player();
	void init(const LoaderParams* pParams);

private:
	AnimatedSprite* sprite_;

};

#endif