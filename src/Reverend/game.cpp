#include "game.h"
#include "cleanup.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

Game::Game() {
	window_ = nullptr;
	screen_ = nullptr;
	screenWidth_ = 640;
	screenHeight_ = 480;
	gameState_ = GameState::PLAY;
}

Game::~Game() {
}

void Game::run() {
	if (initSystems()) {
		loadMedia();
		gameLoop();
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
	window_ = SDL_CreateWindow("Reverend", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth_, screenHeight_, SDL_WINDOW_OPENGL);
	if( window_ == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	SDL_Renderer *gRenderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr){
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

	return true;
}

void Game::close() {
	cleanup(screen_, window_);
	screen_ = NULL;
	window_ = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* Game::loadImage(std::string path)
{
	//Load image at specified path
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		std::cout << "Bliting surface" << std::endl;
		//Convert surface to screen format
		SDL_BlitSurface( loadedSurface, NULL, screen_, NULL );
	}
	
	//Update the surface
	SDL_UpdateWindowSurface( window_ );

	return loadedSurface;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	loadImage( "player.png" );

	return success;
}

/**
 * Main game loop, where all the magic happens.
 */
void Game::gameLoop() {
	while(gameState_ != GameState::EXIT) {
		processInput();
	}
	close();
}

void Game::processInput() {
	SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch(ev.type) {
			case SDL_QUIT:
				gameState_ = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch(ev.key.keysym.sym) {
                    case SDLK_a:
						std::cout << "a key down" << std::endl;
                        break;
                    case SDLK_d:
						std::cout << "d key down" << std::endl;
                        break;
                    case SDLK_w:
						std::cout << "w key down" << std::endl;
                        break;
                    case SDLK_s:
						std::cout << "s key down" << std::endl;
                        break;
                }
				break;
            case SDL_MOUSEBUTTONDOWN:
				switch(ev.button.button) {
					case SDL_BUTTON_LEFT:
						std::cout << "Left mouse click" << std::endl;
						break;
					case SDL_BUTTON_RIGHT:
						std::cout << "Right mouse click" << std::endl;
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				std::cout << ev.motion.x << " " << ev.motion.y << std::endl;
				break;
		}
    }
}