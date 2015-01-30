#pragma once

#include <SDL/SDL.h>
#include <iostream>

enum class GameState {
	PLAY,
	EXIT
};

class Game {
public:
	Game();
	~Game();

	void run();
	void close();

private:
	bool initSystems();
	void gameLoop();
	void processInput();
	
	bool loadMedia();
	SDL_Surface* loadImage(std::string path);

	SDL_Window* window_;
	int screenWidth_;
	int screenHeight_;
	SDL_Surface* screen_;
	GameState gameState_;
};