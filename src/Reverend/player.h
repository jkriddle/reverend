#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "object/sdlgameobject.h"
#include "soundmanager.h"

class Player : public SDLGameObject {

public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void handleInput();
	void handleKeyboardInput();
	void getWalkingDirection();
	void updateForwardTexture();

	void move(Vector2d* direction);
	void action();
	void attack();
	void equip(int slot);
	void equipPrev();
	void equipNext();

	int equippedItem_;
	int numBeltSlots_;
	static const int speed_ = 15;
};

#endif