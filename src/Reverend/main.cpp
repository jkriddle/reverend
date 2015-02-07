#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "game.h"
#include "ltimer.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
const int SCREEN_TICKS_PER_FRAME = 1000 / FPS;

int main(int argc,char **argv) 
{	
    //The frames per second timer
    LTimer fpsTimer;

    //The frames per second cap timer
    LTimer capTimer;
	
    //Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();
	bool quit = false;
	SDL_Event e;

	Game::getInstance()->init();

	while(Game::getInstance()->running()) {
		
        //Calculate and correct fps
        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }
       
		++countedFrames;

		Game::getInstance()->handleEvents();
		Game::getInstance()->update();
		Game::getInstance()->draw();

		//If frame finished early
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }
		
	}
	return 0;
}