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
	map_ = NULL;
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


void Game::draw() {
	SDL_RenderClear(renderer_);
	gameStateMachine_->draw();
    SDL_RenderPresent(renderer_); 
}