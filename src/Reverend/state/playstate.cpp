#include "playstate.h"
//#include "pausestate.h"

const std::string PlayState::id_ = "PLAY";

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	GameState::onExit();
	Object::cleanup();
	
	std::cout << "exiting PlayState\n";
	return true;
}


void PlayState::update() {
	if(Input::getInstance().getButtonState(0, 4) || Input::getInstance().isKeyDown(SDL_SCANCODE_RETURN)) {
		//Game::getStateMachine()->pushState(new PauseState());
	}

	// Inventory
	if(Input::getInstance().getButtonState(0, 11) || Input::getInstance().isKeyDown(SDL_SCANCODE_I)) {
		std::cout << "show inventory" << std::endl;
	}
		
	if(Input::getInstance().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		Input::getInstance().onQuit();
	}
}