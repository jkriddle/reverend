#include "playstate.h"
//#include "pausestate.h"

const std::string PlayState::id_ = "PLAY";

void PlayState::update() {
	if(InputHandler::getInstance()->getButtonState(0, 4) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RETURN)) {
		//Game::getInstance()->getStateMachine()->pushState(new PauseState());
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
	
	// check collisions
	/*for(unsigned int i = 0; i < layers_.size(); i++) {
		std::vector<GameObject*>* gameObjects = layers_[i]->getGameObjects();
		for(unsigned int j = 0; j < gameObjects->size(); j++) {

		}
	}*/
}

void PlayState::draw() {

	for(unsigned int i = 0; i < layers_.size(); i++) {
		layers_[i]->draw();
	}
}

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	
	// Load Textures
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

	// Load Objects
	ObjectFactory::registerType("player", new PlayerCreator());
	ObjectFactory::registerType("enemy", new EnemyCreator());
	
	int pX = 9000;
	int pY = 9000;

	// Player init
	Game::getInstance()->getCamera()->goTo(pX, pY);
	
	// Setup layers - first is lowest in z-index
	TerrainLayer* terrainLayer = new TerrainLayer();
	layers_.push_back(terrainLayer);

	ObjectLayer* actorLayer = new ObjectLayer();
	actorLayer->add(ObjectFactory::create("player", new LoaderParams(pX, pY, 64, 64, "player")));
	actorLayer->add(ObjectFactory::create("enemy", new LoaderParams(pX, pY, 64, 64, "enemy")));
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