#include "Inventory.h"

//set the slot positions using the slotPositions array
Inventory::Inventory(SDL_Rect _invrec)
{
	//setting inventory slot places according to the inventory window position.. theyre all fixed positions that scale as the window does
	for (int i = 0; i < Slots; i++)
	{
		SDL_Rect slotRect;
		slotWidth = (_invrec.w - (10 * _invrec.w / 600) * 2) / 5;
		slotHeight = _invrec.h - (75 * _invrec.h / 200) - (25 * _invrec.h / 200);
		slotRect.x = _invrec.x + slotWidth*i + (10 * _invrec.w / 600) + (slotWidth*0.35);//starts at the 0.35 of the slot
		//slots start at pixel 10 when the menu size is 600
		slotRect.y = _invrec.y + (75*_invrec.h/ 200) + (slotHeight*0.25);//starts at the 1/4 of the slot..
		slotRect.h =  slotHeight*0.5; // making it 1/2 the size of the slot
		slotRect.w = slotWidth* 0.3;// making it 1/3 the size of the slot
		slotPositions[i] = slotRect;
	}

	//set selected item to the first item
	selectedItem = 0;
}

//empty the vectory of items
Inventory::~Inventory() 
{
	std::vector<Item*>::iterator itr;
	for (itr = vInventory.begin(); itr != vInventory.end();)
	{
		(*itr)->setType(emptyT);
		delete *itr;//delete item pointer
		itr = vInventory.erase(itr);//erase vector element
	}
};

//return the item at i in the vector
Item* Inventory::getItemAt(int _i)
{
	if (_i < vInventory.size())//index within range check
	{
		return vInventory[_i];
	}
}

//get slot position and size from the slotPositions Array
SDL_Rect Inventory::getSlotPosAt(int _i)
{
	return slotPositions[_i];
}

int Inventory::getSlotWidth()
{
	return slotWidth;
}

int Inventory::getSlotHeight()
{
	return slotHeight;
}

//returns the index of the selected item in the vector
int Inventory::getSelectedItem()
{
	return selectedItem;
}

//returns vector size
int Inventory::getInventorySize()
{
	return vInventory.size();
}

//returns the position of the right sword texture in the texture of 3 swords, according to the element of the sword at index i.
Vec2 Inventory::getSwordTextureAt(int _i)
{
	return vInventory[_i]->getSword()->getTextAt(vInventory[_i]->getSword()->getElement());
}

//returns the sword pointer from the item that is currently selected
Sword* Inventory::getSelectedSword()
{
	if (vInventory[selectedItem]->getType() == swordT && vInventory.size() > 0)//if current selected item is a sword
	{
		return vInventory[selectedItem]->getSword();
	}
}

//returns the potion pointer from the item that is currently selected
Potion* Inventory::getSelectedPotion()
{
	if (vInventory[selectedItem]->getType() == potionT && vInventory.size() > 0)//if current selected item is a potion
	{
		return vInventory[selectedItem]->getPotion();
	}
}

//returns the type of the currently selected item
itemType Inventory::getSelectedItemType()
{
	if (vInventory.size() > 0)
	{
		return vInventory[selectedItem]->getType();
	}
}

//get number of slots in the vector.. constant of 5
int Inventory::getSlots()
{
	return Slots;
}

//pushes the item onto the inventory vector
void Inventory::Add(Item* _item)
{
	
	if (vInventory.size() < Slots)//if the inventory isnt full
	{

		vInventory.push_back(_item);

	}
}

//discards the item at _x from the inventory vector
void Inventory::Discard(int _x)
{
	//preventing the player from discarding the last sword in their inventory.. cuz dumb
	if (vInventory[selectedItem]->getType() == swordT)//if the item selected to discard is a sword
	{
		int swordCntr = 0;
		for (int i = 0; i < vInventory.size(); i++)
		{
			if (vInventory[i]->getType() == swordT)
			{
				swordCntr++;//count the number of swords in inventory
			}
		}

		if (swordCntr > 1)//only discard this sword (at _x) if it is not the last sword in inventory
		{
			delete vInventory[_x];//delete item pointer
			vInventory.erase(vInventory.begin() + _x);//empty vector slot
			selectedItem = 0;//reset selected item to the first one
		}
	}

	else if (vInventory[selectedItem]->getType() == potionT)//if item selected to discard is a potion, just discard it
	{
		delete vInventory[_x];//delete item pointer
		vInventory.erase(vInventory.begin() + _x);//empty vector slot
		selectedItem = 0;//reset selected item to the first one
	}

}


void Inventory::setSlotPosAt(int _i, SDL_Rect _rect)
{
	slotPositions[_i]= _rect;
}

void Inventory::setSelectedItem(int _x)
{
	selectedItem = _x;
}

