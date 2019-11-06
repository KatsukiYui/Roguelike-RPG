#ifndef _ITEM_
#define _ITEM_

#include "Sword.h"
#include "Potion.h"
#include "SDL.h"

enum itemType {emptyT=0, swordT, potionT};//type of item

class Item//used to make the inventory vector.. each slot or index should contain either a sword or potion
{

protected:

	itemType Type;
	Sword *swordPtr;
	Potion *potionPtr;

public:

	//creates an mepty item with 2 null ptrs
	Item();

	//creates an item of type sword with a null potion pointer and a sword ptr.
	Item(Sword _s);

	//creates an item of type potion with a null sword pointer and a potion ptr.
	Item(Potion _p);

	//deletes any pointer that is not null
	~Item();

	void setType(itemType _t);


	Sword* getSword();
	Potion* getPotion();
	itemType getType();


};

#endif // !_ITEM_
