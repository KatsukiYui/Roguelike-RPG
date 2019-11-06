#ifndef _INVENTORY_
#define _INVENTORY_

#include "Item.h"
#include <vector>

class Inventory//contains and manages the inventory vector (vector of items)
{
protected:

	std::vector<Item*> vInventory;//inventory vector of items
	static const int Slots = 5; //maximum number of inventory items
	int selectedItem; //used to select items to discard or to use in battle
	SDL_Rect slotPositions[Slots]; //used to position each item in the inventory menu
	int slotWidth;//width of each inventory slot in pixels
	int slotHeight;//height of each inventory slot in pixels

public:

	//set the slot positions using the slotPositions array
	Inventory(SDL_Rect _invrec);

	//empty the vectory of items
	~Inventory();

	//return the item at i in the vector
	Item* getItemAt(int _i);

	//get number of slots in the vector.. constant of 5
	int getSlots();

	//get slot position and size from the slotPositions Array
	SDL_Rect getSlotPosAt(int _i);

	int getSlotWidth();
	int getSlotHeight();

	//returns the index of the selected item in the vector
	int getSelectedItem();

	//returns vector size
	int getInventorySize();

	//returns the position of the right sword texture in the texture of 3 swords, according to the element of the sword at index i.
	Vec2 getSwordTextureAt(int _i);
	
	//returns the sword pointer from the item that is currently selected
	Sword* getSelectedSword();
	
	//returns the potion pointer from the item that is currently selected
	Potion* getSelectedPotion();
	
	//returns the type of the currently selected item
	itemType getSelectedItemType();

	void setSlotPosAt(int _i, SDL_Rect _rect);
	void setSelectedItem(int _x);

	//pushes the item onto the inventory vector
	void Add(Item* _item);

	//discards the item at _x from the inventory vector
	void Discard(int _x);


};


#endif // !_INVENTORY_
