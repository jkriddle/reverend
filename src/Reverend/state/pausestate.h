#pragma once
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "../game.h"
#include "../objects/gameobject.h"
#include "gamestate.h"
#include "../button.h"
#include "../inputhandler.h"
#include "../animatedgraphic.h"
#include <iostream>

class PauseState : public GameState {

public:
	virtual void update();
	virtual void draw();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateId() const { return id_; }
private:
	static const std::string id_;
	std::vector<GameObject*> gameObjects_;

	static void pauseToPlay();
	static void pauseToExit();
};

#endif;