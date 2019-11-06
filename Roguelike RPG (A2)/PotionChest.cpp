#include "PotionChest.h"

PotionChest::PotionChest()
{
	P = nullptr;
}

PotionChest::PotionChest(Potion _p)
{
	P = new Potion(_p.getLevel());//initialize the potion pointer based on the passed potion's property values
	Level = _p.getLevel();//set the chest's level according to the content's level
}

PotionChest::~PotionChest()
{
	if (P != nullptr)
	{
		delete P;
	}
}

//makes an item out of the potion pointer inside the chest. Then pushes it onto the inventory vector by calling inventory add function.
void PotionChest::openChest(bool *_end, Inventory *_I)
{
	if (_I->getInventorySize() < _I->getSlots())//if the inventory isnt full
	{
		if (Opened == false)//if the chest hasnt been opened
		{
			Item *_It = new Item(*P);//make an item out of the potion in the chest
			_I->Add(_It);//add the item to the inventory
			Opened = true;
		}
	}
}
