#include "playstate.h"
//#include "pausestate.h"
#include "../engine/component/animatedsprite.h"
#include "../engine/component/boxcollider.h"
#include "../component/playerinput.h"
#include "../engine/camera.h"
#include "../component/terrain.h"
#include <rapidjson\document.h>
#include <rapidjson\stringbuffer.h>
#include <rapidjson\writer.h>
#include <iostream>
#include <fstream>

const std::string PlayState::id_ = "PLAY";

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	
	int pX = 9000;
	int pY = 9000;

	std::ifstream t("data/items.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();
	const std::string tmp = buffer.str();
	/*rapidjson::Document d;
    d.Parse<0>(tmp.c_str());*/
	
    rapidjson::Document document;
	std::string test =  "{\"a\":[{\"z\":21}, {\"z\":22}] }";
	if ( document.Parse<0>( test.c_str() ).HasParseError() ) {
		std::cout << "Error parsing" << std::endl;
	} else if ( document[ "a" ].IsArray() ) {
		std::cout << document["a"][0]["z"].GetInt() << std::endl;
		std::cout << document["a"][1]["z"].GetInt() << std::endl;
		/*rapidjson::StringBuffer sb;
		rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
		document[ "a" ].Accept( writer );
		std::cout << sb.GetString() << std::endl;*/
	}
	

	// Load Objects - rendered in order they are added
	GameObject* terrain = Object::create<GameObject>();
	Terrain* tr = new Terrain(*terrain);
	terrain->addComponent(tr);

	GameObject* player = Object::create<GameObject>();
	player->addComponent(new PlayerInput(*player));

	AnimatedSprite* sprite = new AnimatedSprite(*player);
	sprite->maxFrames = 12;
	sprite->texture = "player";
	player->addComponent(sprite);
	BoxCollider* collider = new BoxCollider(*player);
	player->addComponent(collider);
	player->init(LoaderParams(pX, pY, 64, 64, "player"));
	CameraManager::getMain()->setTarget(player);

	GameObject* e = Object::create<GameObject>();
	AnimatedSprite* s = new AnimatedSprite(*e);
	s->maxFrames = 12;
	s->texture = "enemy";
	e->addComponent(s);
	e->init(LoaderParams(pX - 100, pY - 100, 64, 64, "enemy"));


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