#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include "player.h"
#include "enemy.h"
#include "texturemanager.h"
#include "cleanup.h"
#include "inputhandler.h"
#include "playstate.h"
#include "pausestate.h"
#include "gamestatemachine.h"

class Game {
public:

	void init();
	void close();
	void update();
	void handleEvents();
	void draw();
	bool running() { return isRunning_; }

	static int getTileSize() { return 64; }

	static Game* getInstance()
	{
		if(instance_ == 0)
		{
			instance_ = new Game();
			return instance_;
		}
		return instance_;
	} 

	SDL_Renderer* getRenderer() const { return renderer_; }
	GameStateMachine* getStateMachine(){ return gameStateMachine_; }

private:
	Game() {
		window_ = nullptr;
		screen_ = nullptr;
		screenWidth_ = 640;
		screenHeight_ = 480;
		isRunning_ = true;
	}

	static Game* instance_;

	bool initSystems();

	bool isRunning_;
	
	SDL_Window* window_;
	int screenWidth_;
	int screenHeight_;
	SDL_GLContext context_;
	SDL_Renderer* renderer_;
	SDL_Surface* screen_;
	GameStateMachine* gameStateMachine_;
	
	std::vector<GameObject*> gameObjects_;

	GameObject* player_;
	GameObject* enemy_;
	
};

#endif