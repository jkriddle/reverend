#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include <iostream>
#include "../game.h"
#include "../object/objectfactory.h"
#include "../object/layer.h"
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
	std::vector<ObjectLayer*> layers_;
};

#endif;