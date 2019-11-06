#include "Mouse.h"

//initializes booleans to false
Mouse::Mouse()
{
	isDown = false;
	Clicked = false;

}


//updates the mouse position and button clicks..called once per frame
void Mouse::updateInput()
{
	Clicked = false;//reset clicked

	//updates mouse position and checks if it was left clicked
	if ((SDL_GetMouseState(&(Position.X), &(Position.Y)) && SDL_BUTTON(SDL_BUTTON_LEFT)))
	{
		if (!isDown)//if the mouse button wasnt clicked/down on the previous frame
		{
			Clicked = true;//then yeah mouse is clicked on this one
			isDown = true;//set down to true cuz then next frame itd be down
		}
	}
	else
	{
		isDown = false;//if the mouse was never clicked or down this frame then it wont be down next frame
	}
}


//returns true if the mouse was between these 2 coordinates
bool Mouse::leftClick(Vec2 _corner1, Vec2 _corner2)
{
	//test if mouse position is between the button corners aka on the button
	if ( ( Position.X >= _corner1.X) && (Position.X <= _corner2.X)
			&& (Position.Y >= _corner1.Y) && (Position.Y <= _corner2.Y))
	{	
		return true;
	}
	else
	{
		return false;
	}

}

Vec2 Mouse::getPosition()
{
	return Position;
}

bool Mouse::getMouseDown() { return isDown; }

bool Mouse::getMouseClicked() { return Clicked; };