#include "game.h"
#include <time.h>
#include "component/renderingcomponent.h"
#include "object.h"
#include "soundmanager.h"
#include "component/boxcollider.h"
#include "camera.h"

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
	window_ = SDL_CreateWindow("Reverend", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth_, screenHeight_, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // SDL_WINDOW_FULLSCREEN
	if( window_ == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
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

	Input::getInstance().initialiseJoysticks();

	SDL_Surface* tempSurface = IMG_Load("assets/textures/terrain/grass.png");
	if(tempSurface == 0) {
		return false;
	}

	pTexture = SDL_CreateTextureFromSurface(renderer_, tempSurface);
	SDL_FreeSurface(tempSurface);

	return true;
}

void Game::quit() {
	gameStateMachine_->clean();
	Object::cleanup();
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
	Input::getInstance().update();

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
	Input::getInstance().update();
	if (Input::getInstance().isQuitting()) quit();
}


void Game::render() {
	SDL_RenderClear(renderer_);


	std::vector<GameObject*> gameObjects = Object::getObjects();

	for(GameObject* o : gameObjects) {
		std::vector<RenderingComponent*> renderers = o->getComponents<RenderingComponent>();
		for(RenderingComponent* r : renderers) {
			r->render(renderer_);
		}
		
		// This is just for testing
		if (showColliders_) {
			std::vector<BoxCollider*> colliders = o->getComponents<BoxCollider>();
			for(BoxCollider* c : colliders) {
				SDL_Rect destRect;
				Vector2d pos = CameraManager::getMain()->translate(c->getBounds().x, c->getBounds().y);
				destRect.x = pos.x;
				destRect.y = pos.y;
				destRect.w = c->getBounds().w;
				destRect.h = c->getBounds().h;
				SDL_RenderDrawRect(renderer_, &destRect);
			}
		}
		
	}

	/*

	for(int i = 0; i < screenWidth_; i+= 32)
		for(int j = 0; j < screenHeight_; j+= 32) {
			SDL_Rect srcRect;
			SDL_Rect destRect;
			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = destRect.w = 32;
			srcRect.h = destRect.h = 32;
			destRect.x = i;
			destRect.y = j;
			SDL_RenderCopy(renderer_, pTexture, &srcRect, &destRect);
		}

		*/

    SDL_RenderPresent(renderer_); 
}