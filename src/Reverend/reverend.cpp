#include "reverend.h"
#include "engine/texturemanager.h"
#include "engine/soundmanager.h"
#include "engine/camera.h"

#include "engine/component/animatedsprite.h"
#include "engine/component/boxcollider.h"
#include "component/playerinput.h"
#include "engine/camera.h"
#include "component/terrain.h"
#include <rapidjson\document.h>
#include <rapidjson\stringbuffer.h>
#include <rapidjson\writer.h>
#include <iostream>
#include <fstream>

void Reverend::load() {

	TextureManager::getInstance().load("assets/textures/water.png", "water", getRenderer());
	TextureManager::getInstance().load("assets/textures/shallows.png", "shallows", getRenderer());
	TextureManager::getInstance().load("assets/textures/sand.png", "sand", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass.png", "grass", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-n.png", "grass-n", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-ne.png", "grass-ne", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-e.png", "grass-e", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-se.png", "grass-se", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-s.png", "grass-s", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-sw.png", "grass-sw", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-w.png", "grass-w", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-nw.png", "grass-nw", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/dirt.png", "dirt", getRenderer());
	TextureManager::getInstance().load("assets/textures/rock.png", "rock", getRenderer());
	TextureManager::getInstance().load("assets/textures/snow.png", "snow", getRenderer());
	TextureManager::getInstance().load("assets/textures/stone.png", "Stone", getRenderer());


	// Setup camera
	CameraManager::mainCamera = new Camera(getScreenWidth(), getScreenHeight());

	// Load Textures
	// TODO - move this to PlayState once we have the whole texture management/component renderer figured out.
	int pX = 9000;
	int pY = 9000;
	
	// Terrain
	GameObject* terrain = Object::create<GameObject>();
	Terrain* tr = new Terrain(terrain);
	terrain->addComponent(tr);

	
	std::ifstream gameFile("data/game.json");
	std::stringstream gameBuff;
	gameBuff << gameFile.rdbuf();
	const std::string gameData = gameBuff.str();
    rapidjson::Document gameDocument;
	
	if ( gameDocument.Parse<0>( gameData.c_str() ).HasParseError() ) {
		std::cout << "Error parsing game document" << std::endl;
		return;
	}
	
	
	// First load all the item instances
	std::ifstream itemFile("data/items.json");
	std::stringstream itemBuff;
	itemBuff << itemFile.rdbuf();
	const std::string itemData = itemBuff.str();
    rapidjson::Document itemDocument;
	if ( itemDocument.Parse<0>( itemData.c_str() ).HasParseError() ) {
		std::cout << "Error parsing item document" << std::endl;
		return;
	}
	

	for (rapidjson::SizeType j = 0; j < gameDocument["entities"].Size(); j++) {
		
		if (gameDocument["entities"][j].HasMember("type")) {

			// Find this item (inefficient)
			for (rapidjson::SizeType i = 0; i < itemDocument.Size(); i++) {
				
				std::string gameType = gameDocument["entities"][j]["type"].GetString();
				std::string itemType = itemDocument[i]["name"].GetString();
				if (gameType.compare(itemType) != 0) continue;
				
				int x = gameDocument["entities"][j]["x"].GetInt();
				int y = gameDocument["entities"][j]["y"].GetInt();
				int w = 32;
				int h = 32;

				if (itemDocument[i].HasMember("w")) 
					w = itemDocument[i]["w"].GetInt();
				if (itemDocument[i].HasMember("h")) 
					h = itemDocument[i]["h"].GetInt();
					
				GameObject* item = Object::create<GameObject>();
			
				if (itemDocument[i]["name"] == "Player") {
					CameraManager::getMain()->setTarget(item);
				}
		
				item->init(LoaderParams(x, y, w, h, ""));
			
				// Components
				if (itemDocument[i].HasMember("components")) {
					for (rapidjson::SizeType j = 0; j < itemDocument[i]["components"].Size(); j++) {
						if (itemDocument[i]["components"][j]["type"]  == "Collider") {
							BoxCollider* c = new BoxCollider(item);
							c->offset = GameRect(itemDocument[i]["components"][j]["x"].GetInt(),
												itemDocument[i]["components"][j]["y"].GetInt(),
												itemDocument[i]["components"][j]["w"].GetInt(),
												itemDocument[i]["components"][j]["h"].GetInt());
							item->addComponent(c);
						}
				
						if (itemDocument[i]["components"][j]["type"]  == "RenderingComponent") {
							RenderingComponent* r = new RenderingComponent(item);
							r->texture = itemDocument[i]["components"][j]["texture"].GetString();
							item->addComponent(r);
						}
				
						if (itemDocument[i]["components"][j]["type"]  == "AnimatedSprite") {
							AnimatedSprite* r = new AnimatedSprite(item);
							r->maxFrames = itemDocument[i]["components"][j]["maxFrames"].GetInt();
							r->texture = itemDocument[i]["components"][j]["texture"].GetString();
							item->addComponent(r);
						}
				
						if (itemDocument[i]["components"][j]["type"] == "PlayerInput") {
							PlayerInput* r = new PlayerInput(item);
							item->addComponent(r);
						}

						if (itemDocument[i]["components"][j].HasMember("texture")) {
							TextureManager::getInstance().load(itemDocument[i]["components"][j]["texture"].GetString(), 
																itemDocument[i]["components"][j]["texture"].GetString(), getRenderer());
						}
					}
				}
			}
		}
	}

	SoundManager::getInstance().load("assets/sounds/fast_swipe.wav", "short_swipe", SoundType::SOUND_SFX);
}

void Reverend::close() {
	TextureManager::getInstance().clearFromTextureMap("player");
	TextureManager::getInstance().clearFromTextureMap("enemy");
	TextureManager::getInstance().clearFromTextureMap("water");
	TextureManager::getInstance().clearFromTextureMap("shallows");
	TextureManager::getInstance().clearFromTextureMap("sand");
	TextureManager::getInstance().clearFromTextureMap("grass");
	TextureManager::getInstance().clearFromTextureMap("dirt");
	TextureManager::getInstance().clearFromTextureMap("rock");
	TextureManager::getInstance().clearFromTextureMap("snow");
	CameraManager::cleanup();
}