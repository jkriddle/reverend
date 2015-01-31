#include "game.h"

Game* Game::instance_ = 0;

void Game::init() {
	if (initSystems()) {
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
	/*
	while(gameState_ != GS::EXIT) {
		handleEvents();
		
		for(std::vector<GameObject*>::size_type i = 0; i != gameObjects_.size(); i++) {
			gameObjects_[i]->update();
		}

		draw();
		SDL_Delay(10); // cap frame rate
	}
	close();*/
}

void Game::handleEvents() {
	InputHandler::getInstance()->update();
	gameStateMachine_->update();
}

void Game::draw() {
	SDL_RenderClear(renderer_);
	gameStateMachine_->render();
    SDL_RenderPresent(renderer_); 
}