#include "game.h"

Game* Game::instance_ = 0;

void Game::init() {
	if (initSystems()) {
		loadMedia();
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

	return true;
}

void Game::close() {
	cleanup(screen_, window_, renderer_);
	screen_ = NULL;
	window_ = NULL;
	renderer_ = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadImage(std::string path)
{
	//Load image at specified path
	SDL_Texture* texture; // the new SDL_Texture variable

	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //path.c_str()
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
    // Clear the entire screen to the Renderer's base colour 
		texture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}

bool Game::loadMedia()
{
	//Loading success flag
	TextureManager::getInstance()->load("assets/textures/player.png", "player", renderer_);
	TextureManager::getInstance()->load("assets/textures/enemy.png", "enemy", renderer_);
	
	player_ = new Player(new LoaderParams(64*5, 64*5, 64, 64, "player"));
	go_ = new Player(new LoaderParams(64*3, 64*3, 64, 64, "player"));
	enemy_ = new Player(new LoaderParams(64*2, 64*2, 64, 64, "enemy"));
	
	gameObjects_.push_back(go_);
	gameObjects_.push_back(player_);
	gameObjects_.push_back(enemy_);

	return true;
}

/**
 * Main game loop, where all the magic happens.
 */
void Game::update() {
	while(gameState_ != GameState::EXIT) {
		handleEvents();
		
		for(std::vector<GameObject*>::size_type i = 0; i != gameObjects_.size(); i++) {
			gameObjects_[i]->update();
		}

		draw();
		SDL_Delay(10); // cap frame rate
	}
	close();
}

void Game::handleEvents() {
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
						//player_->setPos(player_->getX() - Game::getTileSize(), player_->getY());
						//player_->setDirection(GameDirection::WEST);
                        break;
                    case SDLK_d:
						//player_->setPos(player_->getX() + Game::getTileSize(), player_->getY());
						//player_->setDirection(GameDirection::EAST);
                        break;
                    case SDLK_w:
						//player_->setPos(player_->getX(), player_->getY() - Game::getTileSize());
						//player_->setDirection(GameDirection::NORTH);
                        break;
                    case SDLK_s:
						//player_->setPos(player_->getX(), player_->getY() + Game::getTileSize());
						//player_->setDirection(GameDirection::SOUTH);
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

void Game::draw() {
	SDL_RenderClear(renderer_);
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

	for(std::vector<GameObject*>::size_type i = 0; i != gameObjects_.size(); i++) {
		gameObjects_[i]->draw();
	}

	//TextureManager::getInstance()->drawFrame("player", 100, 100, 64, 64, 1, player_->currentFrame, renderer_);


	/*
	SDL_Rect sourceRectangle; // the first rectangle
	SDL_Rect destinationRectangle; // another rectangle
	sourceRectangle.w = 64;
	sourceRectangle.h = 64;
	sourceRectangle.x = (64*0) + (64 * int(((SDL_GetTicks() / 100) % 12))); // 100 = switch frames every 100ms, 3 = # of frames
	sourceRectangle.y = 64 * 4; // 100 = switch frames every 100ms, 3 = # of frames

	destinationRectangle.x = sourceRectangle.x;
	destinationRectangle.y = sourceRectangle.y;

	destinationRectangle.x = player_->getX();
	destinationRectangle.y = player_->getY();
	destinationRectangle.w = sourceRectangle.w;
	destinationRectangle.h = sourceRectangle.h;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (player_->getDirection() == GameDirection::WEST) flip = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(renderer_, player_->getTexture(), &sourceRectangle, &destinationRectangle, 0, 0, flip); // pass in the horizontal flip
	*/

    SDL_RenderPresent(renderer_); 
}