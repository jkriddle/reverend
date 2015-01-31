#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "sdlgameobject.h"

class Player : public SDLGameObject {

public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	GameDirection currentDirection_;
	void handleInput();
	void handleKeyboardInput();
	GameDirection getWalkingDirection();
	void updateInputTexture(GameDirection direction);
};

#endif