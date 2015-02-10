#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include <iostream>
#include "../game.h"
#include "../entities/objectfactory.h"
#include "../entities/terrain.h"
#include "../soundmanager.h"

class PlayState : public GameState {

public:
	virtual void update();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateId() const { return id_; }
private:
	static const std::string id_;
};

#endif;