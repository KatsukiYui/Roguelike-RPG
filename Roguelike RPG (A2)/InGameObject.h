#ifndef _IN_GAME_OBJ_
#define _IN_GAME_OBJ_

/*this class is the base/parent class for game Objects that have an X and Y position and actually appear ingame and not only
have stats. This doesn't include the enemies as they only appear in the turn based combat screen with constant positions. 
The Player and the Chest classes inherit from this class*/

#include <iostream>

class InGameObject
{
protected:
	int xPos;//coordinates on the tile map (map class with 2D array of tiles)
	int yPos;
	int Level;//current level


public:

	InGameObject(int _x, int _y, int _lvl);

	void setLevel(int _lvl);
	void setX(int _x);
	void setY(int _y);

	int getLevel();
	int getX();
	int getY();

};



#endif // !_IN_GAME_OBJ_
