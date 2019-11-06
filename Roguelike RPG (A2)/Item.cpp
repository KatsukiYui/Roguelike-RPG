#include "Item.h"

//creates an mepty item with 2 null ptrs
Item::Item()
{
	swordPtr = nullptr;
	potionPtr = nullptr;
	Type = emptyT;
}

//creates an item of type sword with a null potion pointer and a sword ptr.
Item::Item(Sword _s)
{
	swordPtr = new Sword(_s.getElement(), _s.getLevel());//used the passed sword's property values to make the pointer
	potionPtr = nullptr;
	Type = swordT;
}

//creates an item of type potion with a null sword pointer and a potion ptr.
Item::Item(Potion _p)
{
	potionPtr = new Potion(_p.getLevel());//used the passed potion's property values to make the pointer
	swordPtr = nullptr;
	Type = potionT;
}


//deletes any pointer that is not null
Item::~Item()
{
	if (swordPtr != nullptr)
	{
		delete swordPtr;
	}


	if (potionPtr != nullptr)
	{
		delete potionPtr;
	}

}


void Item::setType(itemType _t)
{
	Type = _t;
}

Sword* Item::getSword()
{
	return swordPtr;
}

Potion* Item::getPotion()
{
	return potionPtr;
}

itemType Item::getType()
{
	return Type;
}




