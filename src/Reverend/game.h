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
#include "camera.h"
#include "gamestatemachine.h"
#include "map/mapgenerator.h"

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
	Camera* getCamera(){ return camera_; }
	MapGenerator* getMap(){ return map_; }
	int getScreenWidth() { return screenWidth_; }
	int getScreenHeight() { return screenHeight_; }

private:
	Game() {
		window_ = nullptr;
		screen_ = nullptr;
		screenWidth_ = 640;
		screenHeight_ = 480;
		isRunning_ = true;
		camera_ = new Camera(screenWidth_, screenHeight_, 1.0f);
	}

	static Game* instance_;

	bool initSystems();
	bool initWorld();
	
	bool isRunning_;
	int seed_;
	SDL_Window* window_;
	int screenWidth_;
	int screenHeight_;
	SDL_GLContext context_;
	SDL_Renderer* renderer_;
	SDL_Surface* screen_;
	GameStateMachine* gameStateMachine_;
	Camera* camera_;
	MapGenerator* map_;

	std::vector<GameObject*> gameObjects_;
};

#endif