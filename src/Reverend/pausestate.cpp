#include "pausestate.h"

const std::string PauseState::id_ = "PAUSE";

void PauseState::update()
{
	if(InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_R)) {
	}

	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->update();
	}
}

void PauseState::draw()
{
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->draw();
	}
}

void PauseState::pauseToPlay() {
	Game::getInstance()->getStateMachine()->popState();
}

void PauseState::pauseToExit() {
	Game::getInstance()->close();
}

bool PauseState::onEnter()
{
	if(!TextureManager::getInstance()->load("assets/textures/resume.png", "resumeButton", Game::getInstance()->getRenderer())) {
		return false;
	}

	if(!TextureManager::getInstance()->load("assets/textures/restart.png", "restartButton", Game::getInstance()->getRenderer())) {
		return false;
	}

	if(!TextureManager::getInstance()->load("assets/textures/exit.png", "exitButton", Game::getInstance()->getRenderer())) {
		return false;
	}

	//GameObject* button1 = new Button(new LoaderParams(100, 100, 200, 100, "restartButton"));
	GameObject* button2 = new Button(new LoaderParams(100, 200, 200, 100, "resumeButton"), pauseToPlay);
	GameObject* button3 = new Button(new LoaderParams(100, 300, 200, 100, "exitButton"), pauseToExit);
	//gameObjects_.push_back(button1);
	gameObjects_.push_back(button2);
	gameObjects_.push_back(button3);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->clean();
	}
	
	gameObjects_.clear();
	TextureManager::getInstance()->clearFromTextureMap("restartbutton");
	TextureManager::getInstance()->clearFromTextureMap("resumeButton");
	TextureManager::getInstance()->clearFromTextureMap("exitButton");

	std::cout << "exiting PauseState\n";
	return true;
}