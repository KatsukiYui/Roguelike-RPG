#include "Text.h"


//initializing all static properties
SDL_Color Text::Color = { 0,0,0,0 };
SDL_Rect Text::textRect{ 0, 0, 0, 0 };
TTF_Font* Text::textFont = nullptr;
SDL_Texture* Text::Texture = nullptr;

//writes the string onto the renderer using this rectangle
void Text::writeText(std::string _text, SDL_Renderer *_renderer, SDL_Rect _rect)
{
	textFont = TTF_OpenFont("ariblk.ttf", 25); //set the font to arial black

	Color = { 20, 80, 100, 255 };//set text color

	const char * text = _text.c_str(); //convert the string to cstring

	SDL_Surface *Surface = TTF_RenderText_Solid(textFont, text, Color);//create a surface from the font, cstring and color

	Texture = SDL_CreateTextureFromSurface(_renderer, Surface);

	textRect = _rect;
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &textRect);//filling the rectangle around the text with black
	SDL_RenderCopy(_renderer, Texture, NULL, &textRect);//print the text onto the rectangle

	SDL_FreeSurface(Surface);
}


//destroys SDL things
void Text::cleanUp()
{
	TTF_CloseFont(textFont);

	SDL_DestroyTexture(Texture);
}
