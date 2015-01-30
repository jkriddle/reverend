/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "game.h"

//Loads individual image
SDL_Surface *loadImage( std::string path );

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

// Renderer
SDL_Renderer *gRenderer;
	
//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface *playerImage = NULL;


int main( int argc, char* args[] )
{
	Game* game = new Game();
	game->run();

	/*//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					} else if ( e.type == SDL_SCANCODE_A) {
						std::cout << "A pressed";
					}
				}

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	//Free resources and close SDL
	close();*/

	return 0;
}