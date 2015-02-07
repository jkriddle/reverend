#include "playstate.h"
#include "game.h"

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
	
	TextureManager::getInstance()->load("assets/textures/player.png", "player", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/enemy.png", "enemy", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/water.png", "water", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/shallows.png", "shallows", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/sand.png", "sand", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/grass.png", "grass", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/dirt.png", "dirt", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/rock.png", "rock", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/textures/snow.png", "snow", Game::getInstance()->getRenderer());
	SoundManager::getInstance()->load("assets/sounds/fast_swipe.wav", "short_swipe", SoundType::SOUND_SFX);
	
	int pX = 0;
	int pY = 0;

	Player* player_ = new Player(new LoaderParams(pX, pY, 64, 64, "player"));
	//Enemy* enemy_ = new Enemy(new LoaderParams(64*2, 64*2, 64, 64, "enemy"));

	Game::getInstance()->getCamera()->goTo(player_->getX(), player_->getY());

	gameObjects_.push_back(player_);
	//gameObjects_.push_back(enemy_);

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
	TextureManager::getInstance()->clearFromTextureMap("water");
	TextureManager::getInstance()->clearFromTextureMap("shallows");
	TextureManager::getInstance()->clearFromTextureMap("sand");
	TextureManager::getInstance()->clearFromTextureMap("grass");
	TextureManager::getInstance()->clearFromTextureMap("dirt");
	TextureManager::getInstance()->clearFromTextureMap("rock");
	TextureManager::getInstance()->clearFromTextureMap("snow");
	std::cout << "exiting PlayState\n";
	return true;
}