#ifndef _CHEST_
#define _CHEST_

#include "InGameObject.h"
#include "Sword.h"
#include "Inventory.h"
class Chest : public InGameObject//base class for the 3 types of chests. Used to create a vector of chest pointers butpush different child class ptrs onto it.
{

protected:
	bool Opened;//is set to false when the chests are spawned, set to true when opened by player to prevent duplicate items/opening the chest twice

public:

	Chest();

	Chest(int _x, int _y, int _lvl);

	//based on which chest child class, this function has a different outcome.
	//e.g. if sword chest is opened a sword is added to the inventory. 
	//This function is virtual so that it can be called by the vector of chest ptrs. Chests[i]->openChest() ..opens the right type of chest
	virtual void openChest(bool *_end, Inventory *_I) = 0; 

};
#endif
