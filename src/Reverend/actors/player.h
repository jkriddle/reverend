#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "../gameobject.h"
#include "../component/animatedsprite.h"

class Player : public GameObject {

public:
	Player();
	void init(const LoaderParams* pParams);

private:
	AnimatedSprite* sprite_;

};

#endif