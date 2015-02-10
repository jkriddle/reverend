#pragma once

#ifndef TILE_H
#define TILE_H

#include "engine/game.h"

// this will eventually be used for custom game logic (outside of "engine" logic)
// things like loading the map, configuring windows, etc.
class Reverend : public Game {
public:
	void load();
	void close();
};

#endif;