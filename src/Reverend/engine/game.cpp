#include "game.h"
#include <time.h>
#include "component/renderingcomponent.h"
#include "object.h"

void Game::init() {
	if (initSystems()) {
		// do other stuff
		load();
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

void Game::quit() {
	close();
	isRunning_ = false;
	cleanup(screen_, window_, renderer_);
	screen_ = NULL;
	window_ = NULL;
	renderer_ = NULL;
//	map_ = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void Game::update() {
	// Update all components
	std::vector<GameObject*> objects = Object::getObjects();
	for(unsigned int i = 0; i < objects.size(); i++) {
		// check components
		// definitely going to need to find a more efficient way of this
		// if we get a lot of object. Maybe move out of play state and just do it once for
		// all object everywhere.
		for(Component* c : objects[i]->getComponents())
		{
			c->update();
		}	
	}

	gameStateMachine_->update();
}

void Game::handleEvents() {
	InputHandler::getInstance()->update();
	if (InputHandler::getInstance()->isQuitting()) quit();
}


void Game::render() {
	SDL_RenderClear(renderer_);
	// TODO loop through components, find renderers, and render them
	std::vector<GameObject*> gameObjects = Object::getObjects();
	for(GameObject* o : gameObjects) {
		std::vector<RenderingComponent*> renderers = o->getComponents<RenderingComponent>();
		for(RenderingComponent* r : renderers) {
			r->render(renderer_);
		}
	}

    SDL_RenderPresent(renderer_); 
}