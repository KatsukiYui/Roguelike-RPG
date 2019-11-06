#include "Keyboard.h"

//returns a key ID/name if a key was pressed. Else returns none.
Keys Keyboard::Update()
{
	if (Key[SDL_SCANCODE_W])//scans if the W key was pressed etc and returns the corresponding enum key ID/name 
	{
		return Up;
	}
	if (Key[SDL_SCANCODE_S])
	{
		return Down;
	}
	if (Key[SDL_SCANCODE_D])
	{
		return Right;

	}
	if (Key[SDL_SCANCODE_A])
	{
		return Left;
	}
	if (Key[SDL_SCANCODE_LSHIFT] || Key[SDL_SCANCODE_RSHIFT])
	{
		return Shift;
	}
	
	return None;//return none if no key or none of the above keys were pressed
}