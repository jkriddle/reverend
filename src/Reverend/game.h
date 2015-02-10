#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include "texturemanager.h"
#include "cleanup.h"
#include "inputhandler.h"
#include "state/gamestatemachine.h"
#include "camera.h"
#include "map/mapgenerator.h"

class GameObject;

class Game {
public:

	void init();
	void close();
	void update();
	void handleEvents();
	void render();
	bool running() { return isRunning_; }

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

	static const int getTileSize() { return 32; }
	static const int getScale() { return 4; }

private:
	Game() {
		window_ = nullptr;
		screen_ = nullptr;
		screenWidth_ = 640;
		screenHeight_ = 480;
		isRunning_ = true;
		camera_ = new Camera(screenWidth_, screenHeight_, 1.0f);
		gameStateMachine_ = new GameStateMachine();
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