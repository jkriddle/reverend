#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "../engine/state/gamestate.h"
#include <iostream>
#include "../engine/game.h"
#include "../engine/object.h"
#include "../engine/soundmanager.h"

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