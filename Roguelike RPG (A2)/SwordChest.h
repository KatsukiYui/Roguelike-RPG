#ifndef _SCHEST_
#define _SCHEST_



#include "Chest.h"

class SwordChest : public Chest //this is a class for chests with Sword drops in them.. open sword function adds a sword to the inventory
{
protected:

	//sword pointer that is changed into an item and added to the inventory, when the chest is opened.
	Sword* S;

public:
	SwordChest();
	SwordChest(Sword _s);
	~SwordChest();

	//makes an item out of the sword pointer and call inventory add to push it onto the inventory vector.
	void openChest(bool *_end, Inventory *_I);

};


#endif // !_SCHEST_

