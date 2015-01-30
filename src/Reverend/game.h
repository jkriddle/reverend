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

enum class GameState {
	PLAY,
	EXIT
};

class Game {
public:

	void init();
	void close();
	void update();
	void handleEvents();
	void draw();
	bool running() { return gameState_ == GameState::PLAY; }

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

private:
	Game() {
		window_ = nullptr;
		screen_ = nullptr;
		screenWidth_ = 640;
		screenHeight_ = 480;
		gameState_ = GameState::PLAY;
	}

	static Game* instance_;

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
	
	std::vector<GameObject*> gameObjects_;

	GameObject* go_;
	GameObject* player_;
	GameObject* enemy_;
	
};

#endif