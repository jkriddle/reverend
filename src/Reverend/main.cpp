/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "game.h"

int main( int argc, char* args[] )
{
	Game::getInstance()->init();

	while(Game::getInstance()->running()) {
		Game::getInstance()->handleEvents();
		Game::getInstance()->update();
		Game::getInstance()->draw();
	}

	return 0;
}