#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include "../objects/gameobject.h"
#include "../objects/layer.h"
#include "../player.h"
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
	void renderTileMap();
	std::vector<Layer*> layers_;
	Player* player_;
};

#endif;