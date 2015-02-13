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
	
	// Load Objects - rendered in order they are added
	GameObject* terrain = Object::create<GameObject>();
	Terrain* tr = new Terrain(terrain);
	terrain->addComponent(tr);
	
	// Load items
	std::ifstream t("data/items.json");
	std::stringstream buffer;
	buffer << t.rdbuf();
	const std::string itemData = buffer.str();
	
	/*"name" : "Rock",
		"description" : "Your run of the mill rock. Bash things with it or make it a pet.",
		"collision" : false,
		"texture" : "assets/textures/stone.png",
		"h" : 32,
		"w" : 32*/

    rapidjson::Document document;
	if ( document.Parse<0>( itemData.c_str() ).HasParseError() ) {
		std::cout << "Error parsing" << std::endl;
	} else if ( document.IsArray() ) {
		for (rapidjson::SizeType i = 0; i < document.Size(); i++) {
			std::string texture = document[i]["name"].GetString();
			int w = document[i]["w"].GetInt();
			int h = document[i]["h"].GetInt();
			GameObject* item = Object::create<GameObject>();
			item->init(LoaderParams(9100, 9100, w, h, texture));
			RenderingComponent* r = new RenderingComponent(item);
			r->texture = texture;
			item->addComponent(r);

			if (document[i]["collider"] != NULL) {
				BoxCollider* c = new BoxCollider(item);
				c->offset = GameRect(document[i]["collider"]["x"].GetInt(),
									document[i]["collider"]["y"].GetInt(),
									document[i]["collider"]["w"].GetInt(),
									document[i]["collider"]["h"].GetInt());
				item->addComponent(c);
			}

		}
	}

	
	// Players
	GameObject* player = Object::create<GameObject>();
	player->init(LoaderParams(pX, pY, 64, 64, "player"));

	player->addComponent(new PlayerInput(player));

	AnimatedSprite* sprite = new AnimatedSprite(player);
	sprite->maxFrames = 12;
	sprite->texture = "player";
	player->addComponent(sprite);
	BoxCollider* collider = new BoxCollider(player);
	collider->offset = GameRect(15, 40, 32, 20);
	player->addComponent(collider);
	CameraManager::getMain()->setTarget(player);
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