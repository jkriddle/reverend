#include "game.h"
#include <time.h>

Game* Game::instance_ = 0;

bool Game::initWorld() {
	srand(static_cast<int>(time(0)));
	unsigned int a = (rand() % (int)(RAND_MAX + 1));
	unsigned int b = (rand() % (int)(RAND_MAX + 1));
	seed_ = a*(RAND_MAX+1)+b;
	
	seed_ = 0; // testing only	
	srand(seed_);

	map_ = new MapGenerator(screenWidth_, screenHeight_, seed_);
	map_->loadAltitudeMap("overworld.bmp");
	return true;
}

void Game::init() {
	if (initSystems()) {

		initWorld();

		gameStateMachine_ = new GameStateMachine();
		gameStateMachine_->changeState(new PlayState());
	} else {
		SDL_Quit();
	}
}

bool Game::initSystems() {
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	//Create window
	window_ = SDL_CreateWindow("Reverend", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth_, screenHeight_, SDL_WINDOW_OPENGL); // SDL_WINDOW_FULLSCREEN
	if( window_ == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	context_ = SDL_GL_CreateContext(window_);
	if (context_ == nullptr) {
		std::cout << "SDL_GL context could not be created!";
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr){
		SDL_DestroyWindow(window_);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	//Get window surface
	screen_ = SDL_GetWindowSurface(window_);

	InputHandler::getInstance()->initialiseJoysticks();

	return true;
}

void Game::close() {
	isRunning_ = false;
	cleanup(screen_, window_, renderer_);
	screen_ = NULL;
	window_ = NULL;
	renderer_ = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void Game::update() {
	gameStateMachine_->update();
	camera_->update();
}

void Game::handleEvents() {
	InputHandler::getInstance()->update();
}

void Game::renderTileMap() {
	int tileSize = 32;
	int scale = 1;

	/*
	int startX = (-1 * tileSize) + camera->getPosition().getX();
	int startY = (-1 * tileSize) + camera->getPosition().getY();

	// always render one extra tile since movement is non-tile based. Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX + windowX_ + (2 * tileSize);
	int mY = startY + windowY_ + (2 * tileSize);
	*/
	
	int startX = (-1*tileSize) + camera_->getPosition().getX(); // (-1 * tileSize) + camera->getPosition().getX();
	int startY = (-1*tileSize) + camera_->getPosition().getY(); //(-1 * tileSize) + camera->getPosition().getY();

	// always render one extra tile since movement is non-tile based. Thus we could have half of a tile shown (or up to 31 pixels of the prev/next tile)
	int mX = startX + screenWidth_ + (1 * tileSize);
	int mY = startY + screenHeight_ + (1 * tileSize);

	// if we are showing tiles
	// 100, 100, 120, 120
	// we want to actualy load 80, 80, 140, 140
	
	for(int i = startX; i <= mX; i+=tileSize) { // for 0 through 720, every 32 px
		for(int j = startY; j <= mY; j+=tileSize) { // for 0 through 360, every 32 px

			int mapAltX = i;
			int mapAltY =  j;
			
			if (mapAltX != 0) mapAltX = i / tileSize / scale;
			if (mapAltY != 0) mapAltY = j / tileSize / scale;
			double height = map_->getAltitude(mapAltX, mapAltY);

			// we have this tile, but we need to shift the position based on the camera position
			int offsetX = (startX % tileSize);
			int offsetY = (startY % tileSize);
			int cX = i - camera_->getPosition().getX() - offsetX;
			int cY = j - camera_->getPosition().getY() - offsetY;
			
			// an equator bug exists where when you are within a few "tileSize" Y values of 0, the lower tiles are drawn a tilesize too high.

			/*if (lm != pX || rm != pY) {
				std::cout << "x, y: " << camera_->getPosition().getX() << "," << camera_->getPosition().getY() << std::endl;
				std::cout << "startX, startY: " << startX << "," << startY << std::endl;
				std::cout << "mX, mY: " << mX << "," << mY << std::endl;
				//std::cout << "mapAltX, mapAltX: " << mapAltX << "," << mapAltY << std::endl;
				std::cout << "offsetX: " << offsetX << std::endl;
				std::cout << "offsetY: " << offsetY << std::endl;
				std::cout << "cX, cY: " << cX << "," << cY << std::endl << std::endl;
				lm = pX;
				rm = pY;
			}*/

			// Height goes 0 to 255
			int max = 255;
			
			std::string texture = "water";
			if (height > 120) texture = "shallows";
			if (height > 130) texture = "sand";
			if (height > 140) texture = "grass";
			if (height > 210) texture = "dirt";
			if (height > 230) texture = "rock";
			if (height > 250) texture = "snow";
			
			TextureManager::getInstance()->draw(texture.c_str(), cX, cY, tileSize, tileSize, renderer_);
		}
	}
}

void Game::draw() {
	SDL_RenderClear(renderer_);
	renderTileMap();
	gameStateMachine_->draw();
    SDL_RenderPresent(renderer_); 
}