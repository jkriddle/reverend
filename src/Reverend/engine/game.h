#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include "texturemanager.h"
#include "cleanup.h"
#include "input.h"
#include "state/gamestatemachine.h"

class GameObject;

class Game {
public:

	void init();
	void quit();
	virtual void update();
	virtual void handleEvents();
	virtual void render();
	virtual void load() = 0;
	virtual void close() = 0;
	bool running() { return isRunning_; }

	SDL_Renderer* getRenderer() const { return renderer_; }
	GameStateMachine* getStateMachine(){ return gameStateMachine_; }
	int getScreenWidth() { return screenWidth_; }
	int getScreenHeight() { return screenHeight_; }

	static const int getTileSize() { return 32; }
	static const int getScale() { return 4; }

protected:
	Game() {
		window_ = nullptr;
		screen_ = nullptr;
		screenWidth_ = 640;
		screenHeight_ = 480;
		isRunning_ = true;
		gameStateMachine_ = new GameStateMachine();
	}

private:
	bool initSystems();
	
	bool isRunning_;
	int seed_;
	SDL_Window* window_;
	int screenWidth_;
	int screenHeight_;
	SDL_GLContext context_;
	SDL_Renderer* renderer_;
	SDL_Surface* screen_;
	GameStateMachine* gameStateMachine_;
};

#endif