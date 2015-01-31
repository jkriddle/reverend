#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "game.h"
#include "gameobject.h"
#include "gamestate.h"
#include "inputhandler.h"
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
};

#endif;