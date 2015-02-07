#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include "../objects/gameobject.h"
#include <iostream>

class PlayState : public GameState {

public:
	virtual void update();
	virtual void draw();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateId() const { return id_; }
private:
	static const std::string id_;
	std::vector<GameObject*> gameObjects_;
	void renderTileMap();
};

#endif;