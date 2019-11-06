#include <iostream>

#include "Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)//initialize sdl
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		std::cout << "SDL initialization succeeded!";
	}

	TTF_Init();//initialize sdl ttf for text

	//Initialize SDL_mixer 
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) { return -1; }


	Game game;//make a game object, starting the game loops


	//quit sdl 
	Mix_CloseAudio();

	TTF_Quit();

	SDL_Quit();

	return 0;
}