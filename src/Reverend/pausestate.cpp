#include "pausestate.h"

const std::string PauseState::id_ = "PAUSE";

void PauseState::update()
{
	if(InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_R)) {
		Game::getInstance()->getStateMachine()->popState();
	}

	for(int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->update();
	}
}

void PauseState::draw()
{
// nothing for now
}

bool PauseState::onEnter()
{
	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	std::cout << "exiting PauseState\n";
	return true;
}