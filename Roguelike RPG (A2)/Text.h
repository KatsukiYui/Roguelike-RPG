#ifndef _TEXT_
#define _TEXT_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <cstring>

class Text//sdl text manager.. wanted to try creating a fully static class
{

public:

	static SDL_Color Color;//text color
	static SDL_Rect textRect;//rectangle used to draw the text
	static TTF_Font *textFont;//font used
	static SDL_Texture *Texture;//texture used to draw the text onto the renderer

	//writes the string onto the renderer using this rectangle
	static void writeText(std::string _text, SDL_Renderer *_renderer, SDL_Rect _rect);
	
	//destroys SDL things
	static void cleanUp();

};





#endif