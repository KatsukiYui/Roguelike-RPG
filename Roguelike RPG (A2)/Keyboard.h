#ifndef _KEYBOARD_
#define _KEYBOARD_

#include <SDL.h>

enum Keys{ Up, Down, Right, Left, Shift, None};//used to return the key that was pressed

class Keyboard//keyboard controller
{
protected:
	const Uint8 *Key = SDL_GetKeyboardState(NULL);//used to scan keycodes


public:

	//returns a key ID/name if a key was pressed. Else returns none.
	Keys Update();

};


#endif // !_KEYBOARD_
