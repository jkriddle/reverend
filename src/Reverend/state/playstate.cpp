#include "playstate.h"
#include "../game.h"
#include "../player.h"
#include "../enemy.h"
#include "../object/objectlayer.h"
#include "../object/terrainlayer.h"
#include "../soundmanager.h"

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

	for(unsigned int i = 0; i < layers_.size(); i++) {
		layers_[i]->update();
	}
}


void PlayState::renderTileMap() {
	
}

void PlayState::draw() {
	renderTileMap();

	for(unsigned int i = 0; i < layers_.size(); i++) {
		layers_[i]->draw();
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
	
	int pX = 9000;
	int pY = 9000;

	// Player init
	player_ = new Player(new LoaderParams(pX, pY, 64, 64, "player"));
	Game::getInstance()->getCamera()->goTo(pX, pY);
	
	// Setup layers - first is lowest in z-index
	TerrainLayer* terrainLayer = new TerrainLayer();
	layers_.push_back(terrainLayer);

	ObjectLayer* actorLayer = new ObjectLayer();
	actorLayer->add(player_);
	actorLayer->add(new Enemy(new LoaderParams(64*2, 64*2, 64, 64, "enemy")));
	layers_.push_back(actorLayer);

	return true;
}

bool PlayState::onExit()
{
	for(unsigned int i = 0; i < layers_.size(); i++) {
		layers_[i]->clean();
	}
	layers_.clear();
	
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