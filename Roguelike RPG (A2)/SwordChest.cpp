#include "SwordChest.h"

SwordChest::SwordChest()
{
	S = nullptr;
}

SwordChest::SwordChest(Sword _s)
{
	S = new Sword(_s.getElement(), _s.getLevel());//initialize the sword pointer based on the passed sword's property values
	Level = _s.getLevel();//set the chest's level according to the content's level
}

SwordChest::~SwordChest()
{
	if (S != nullptr)
	{
		delete S;
	}
}

//makes an item out of the sword pointer and call inventory add to push it onto the inventory vector.
void SwordChest::openChest(bool *_end, Inventory *_I)
{
	if (_I->getInventorySize() < _I->getSlots())//if the inventory isnt full
	{
		if (Opened == false)//if the chest hasnt been opened
		{
			Item *_It = new Item(*S);//make an item out of the sword in the chest
			_I->Add(_It);//add the item to the inventory
			Opened = true;
		}
	}
}


