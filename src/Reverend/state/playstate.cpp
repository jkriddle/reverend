#include "playstate.h"
//#include "pausestate.h"

const std::string PlayState::id_ = "PLAY";


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
	Terrain* terrain = new Terrain();
	gameObjects_.push_back(terrain);

	gameObjects_.push_back(ObjectFactory::create("player", new LoaderParams(pX, pY, 64, 64, "player")));
	gameObjects_.push_back(ObjectFactory::create("enemy", new LoaderParams(pX - 128, pY - 128, 64, 64, "enemy")));

	return true;
}

bool PlayState::onExit()
{
	GameState::onExit();

	// TODO - these won't be needed, handled by renderer
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

	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->update();
	
		// check components
		// definitely going to need to find a more efficient way of this
		// if we get a lot of object. Maybe move out of play state and just do it once for
		// all object everywhere.
		for(Component* c : gameObjects_[i]->getComponents())
		{
			c->update();
		}	
	}
}