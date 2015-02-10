#include "playstate.h"
//#include "pausestate.h"
#include "../engine/component/animatedsprite.h"

const std::string PlayState::id_ = "PLAY";


bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	

	int pX = 9000;
	int pY = 9000;

	// Load Objects
	GameObject* player = Object::create<GameObject>();
	AnimatedSprite* sprite = new AnimatedSprite(*player);
	sprite->maxFrames = 12;
	sprite->texture = "player";
	player->addComponent(sprite);
	player->init(new LoaderParams(pX, pY, 64, 64, "player"));

	//
	//// Setup layers - first is lowest in z-index
	//Terrain* terrain = new Terrain();
	//gameObjects_.push_back(terrain);
	//
	//gameObjects_.push_back(ObjectFactory::create("player", new LoaderParams(pX, pY, 64, 64, "player")));
	//gameObjects_.push_back(ObjectFactory::create("enemy", new LoaderParams(pX - 128, pY - 128, 64, 64, "enemy")));

	return true;
}

bool PlayState::onExit()
{
	GameState::onExit();
	
	
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
		InputHandler::getInstance()->onQuit();
	}
}