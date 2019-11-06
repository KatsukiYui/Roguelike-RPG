#ifndef _MOUSE_
#define _MOUSE_

#include "Vec2.h"
#include "SDL.h"

class Mouse//mouse controller
{
protected:

	Vec2 Position;//position of the mouse on screen.. updated every frame
	bool isDown; // Boolean for the current mouse held state. returns true if the mouse is held down
	bool Clicked; // Boolean for if the mouse i clicked, this only returns true for the first frame the mouse is clicked.



public:

	//initializes booleans to false
	Mouse();

	//updates the mouse position and button clicks
	void updateInput();

	//returns true if the mouse was between these 2 coordinates
	bool leftClick(Vec2 _corner1, Vec2 _corner2); 


	Vec2 getPosition();
	bool getMouseDown();
	bool getMouseClicked();


};
#endif // !_MOUSE_
