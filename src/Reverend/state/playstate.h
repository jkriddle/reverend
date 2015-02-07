#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include <iostream>
#include "../object/gameobject.h"
#include "../object/layer.h"
#include "../game.h"
#include "../player.h"
#include "../enemy.h"
#include "../object/objectlayer.h"
#include "../object/terrainlayer.h"
#include "../soundmanager.h"

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