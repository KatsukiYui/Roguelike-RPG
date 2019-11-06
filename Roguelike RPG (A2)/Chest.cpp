#include "Chest.h"


Chest::Chest() : InGameObject(0, 0, 0)  {};

Chest::Chest(int _x, int _y, int _lvl)
	:InGameObject(_x, _y, _lvl)//call base class constructor
{
	Opened = false;//opened is set to false on creation. Set to true when the player opens chest
};

