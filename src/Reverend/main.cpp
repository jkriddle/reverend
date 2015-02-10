#include "reverend.h"
#include "state/playstate.h"
#include "engine/ltimer.h"

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
	
	Reverend* reverend = new Reverend();
	reverend->init();
	reverend->getStateMachine()->changeState(new PlayState());

	while(reverend->running()) {
		
        //Calculate and correct fps
        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }
       
		++countedFrames;

		reverend->handleEvents();
		reverend->update();
		reverend->render();

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