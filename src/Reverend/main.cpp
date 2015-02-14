#include "reverend.h"
#include "state/playstate.h"
#include "engine/ltimer.h"

const int MAX_FPS = 30;

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

	float dt; //delta time in seconds
	Uint32 clock; //last time sample in seconds
	float render_timer; //time control for rendering

	dt = 0.0;
	render_timer = 0.0; //init the render timer
	clock = SDL_GetTicks(); //API callback to get the current time in seconds
	
	Uint32 startTime = SDL_GetTicks();
	int numFrames = 0;

	while(reverend->running()) {
		++numFrames;
		dt = SDL_GetTicks() - clock; //get the current delta time for this frame
		clock = SDL_GetTicks(); //updates the clock to check the next delta time
		
		Uint32 elapsedMS = SDL_GetTicks() - startTime; // Time since start of loop
		if (elapsedMS) { // Skip this the first frame
			double elapsedSeconds = elapsedMS / 1000.0; // Convert to seconds
			double fps = numFrames / elapsedSeconds; // FPS is Frames / Seconds
			std::cout << fps << std::endl; 
		}

		reverend->handleEvents();
		reverend->update();

		if(render_timer >= (1.0f/MAX_FPS)) //checks if the frame is ready to render
		{
			reverend->render();
			render_timer -= (1.0f/MAX_FPS); //do not set to zero, remove the accumulated frame time to avoid skipping
		}

		render_timer += dt; //updates the render timer
	}
	delete reverend;
	reverend = NULL;
	return 0;
}