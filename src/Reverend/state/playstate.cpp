#include "playstate.h"
//#include "pausestate.h"

const std::string PlayState::id_ = "PLAY";

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	
	
	// Players
	/*GameObject* player = Object::create<GameObject>();
	player->init(LoaderParams(pX, pY, 64, 64, "player"));

	player->addComponent(new PlayerInput(player));

	AnimatedSprite* sprite = new AnimatedSprite(player);
	sprite->maxFrames = 12;
	sprite->texture = "player";
	player->addComponent(sprite);
	BoxCollider* collider = new BoxCollider(player);
	collider->offset = GameRect(15, 40, 32, 20);
	player->addComponent(collider);
	CameraManager::getMain()->setTarget(player);*/


	/*
	GameObject* e = Object::create<GameObject>();
	e->init(LoaderParams(pX - 100, pY - 100, 64, 64, "enemy"));

	AnimatedSprite* s = new AnimatedSprite(*e);
	s->maxFrames = 12;
	s->texture = "enemy";
	e->addComponent(s);
	BoxCollider* enemyCollider = new BoxCollider(*e);
	e->addComponent(enemyCollider);*/
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