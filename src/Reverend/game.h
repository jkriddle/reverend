#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include "gameobject.h"

enum class GameState {
	PLAY,
	EXIT
};

class Game {
public:
	Game();
	~Game();

	void init();
	void close();
	void update();
	void handleEvents();
	void render();
	bool running() { return gameState_ == GameState::PLAY; }

private:
	bool initSystems();
	
	bool loadMedia();
	SDL_Texture* loadImage(std::string path);

	SDL_Window* window_;
	int screenWidth_;
	int screenHeight_;
	SDL_GLContext context_;
	SDL_Renderer* renderer_;
	SDL_Surface* screen_;
	GameState gameState_;

	GameObject* player_;
};