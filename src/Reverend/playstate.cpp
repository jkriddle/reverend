#include "playstate.h"

const std::string PlayState::id_ = "PLAY";

void PlayState::update() {
	if(InputHandler::getInstance()->getButtonState(0, 4) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RETURN)) {
		Game::getInstance()->getStateMachine()->pushState(new PauseState());
	}

	// Inventory
	if(InputHandler::getInstance()->getButtonState(0, 11) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_I)) {
		std::cout << "show inventory" << std::endl;
	}
		
	if(InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		Game::getInstance()->close();
	}

	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->update();
	}
}

void PlayState::draw() {
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->draw();
	}
}

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	
	//Loading success flag
	TextureManager::getInstance()->load("assets/textures/player.png", "player", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/enemy.png", "enemy", Game::getInstance()->getRenderer());
	
	Player* player_ = new Player(new LoaderParams(64*5, 64*5, 64, 64, "player"));
	Enemy* enemy_ = new Enemy(new LoaderParams(64*2, 64*2, 64, 64, "enemy"));
	
	gameObjects_.push_back(player_);
	gameObjects_.push_back(enemy_);

	return true;
}

bool PlayState::onExit()
{
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->clean();
	}
	gameObjects_.clear();
	TextureManager::getInstance()->clearFromTextureMap("player");
	TextureManager::getInstance()->clearFromTextureMap("enemy");
	std::cout << "exiting PlayState\n";
	return true;
}