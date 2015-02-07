#include "playstate.h"
#include "../game.h"
#include "../player.h"
#include "../enemy.h"
#include "../soundmanager.h"

const std::string PlayState::id_ = "PLAY";

void PlayState::update() {
	if(InputHandler::getInstance()->getButtonState(0, 4) || InputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RETURN)) {
		Game::getInstance()->getStateMachine()->pushState(new PauseState());
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
	}
}


void PlayState::renderTileMap() {
	int tileSize = 32;
	int scale = 4;

	/*
	int startX = (-1 * tileSize) + camera->getPosition().getX();
	int startY = (-1 * tileSize) + camera->getPosition().getY();

	// always render one extra tile since movement is non-tile based. Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX + windowX_ + (2 * tileSize);
	int mY = startY + windowY_ + (2 * tileSize);
	*/

	int cameraX = Game::getInstance()->getCamera()->getPosition().getX();
	int cameraY = Game::getInstance()->getCamera()->getPosition().getY();
	
	int startX = cameraX - tileSize;
	int startY =  cameraY - tileSize;
	
	// Always render one extra tile since movement is non-tile based. 
	// Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX +  Game::getInstance()->getScreenWidth() + tileSize;
	int mY = startY +  Game::getInstance()->getScreenHeight() + tileSize;

	int mapAltX, mapAltY, offsetX, offsetY, cX, cY;
	double height;
			
	std::string texture = "water";
	
	for(int i = startX; i <= mX; i+=tileSize) { // for 0 through 720, every 32 px
		for(int j = startY; j <= mY; j+=tileSize) { // for 0 through 360, every 32 px
			//srand(seed_ + i + j);
			mapAltX = i;
			mapAltY =  j;
			
			if (mapAltX != 0) mapAltX = i / tileSize / scale;
			if (mapAltY != 0) mapAltY = j / tileSize / scale;
			
			height = Game::getInstance()->getMap()->getAltitude(mapAltX, mapAltY);

			// we have this tile, but we need to shift the position based on the camera position
			offsetX = (startX % tileSize);
			offsetY = (startY % tileSize);
			cX = i - cameraX - offsetX;
			cY = j - cameraY - offsetY;

			// an equator bug exists where when you are within a few "tileSize" X or Y values of 0, the map gets pretty crazy
			// also a low Y value seems to cause the map generator to crash because it is trying to get a negative pixel value
			// (like it isn't being translated accordingly)

			// Height goes 0 to 255
			if (height > 120) texture = "shallows";
			if (height > 130) texture = "sand";
			if (height > 140) texture = "grass";
			if (height > 210) texture = "dirt";
			if (height > 230) texture = "rock";
			if (height > 250) texture = "snow";
			
			TextureManager::getInstance()->draw(texture, cX, cY, tileSize, tileSize, Game::getInstance()->getRenderer());
		}
	}
}

void PlayState::draw() {
	renderTileMap();

	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->draw();
	}
}

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	
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
	
	int pX = 9000;
	int pY = 9000;

	Player* player_ = new Player(new LoaderParams(pX, pY, 64, 64, "player"));
	//Enemy* enemy_ = new Enemy(new LoaderParams(64*2, 64*2, 64, 64, "enemy"));

	Game::getInstance()->getCamera()->goTo(player_->getX(), player_->getY());

	gameObjects_.push_back(player_);
	//gameObjects_.push_back(enemy_);

	return true;
}

bool PlayState::onExit()
{
	for(unsigned int i = 0; i < gameObjects_.size(); i++) {
		gameObjects_[i]->clean();
	}
	gameObjects_.clear();
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