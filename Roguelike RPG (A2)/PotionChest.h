#ifndef _PCHEST_
#define _PCHEST_

//this is a class for chests with potion drops in them .. the open chest function just increments the 

#include "Chest.h"


class PotionChest: public Chest//contains a potion. Opening it add potion to inventory
{
protected:

	Potion *P;//the potion inside the chest. This is made into an item then pushed onto the inventory vector when the chest is opened.

public:

	PotionChest();

	PotionChest(Potion _p);

	~PotionChest();

	//makes an item out of the potion pointer inside the chest. Then pushes it onto the inventory vector by calling inventory add function.
	void openChest(bool *_end, Inventory *_I);

};


#endif // !_PCHEST_
