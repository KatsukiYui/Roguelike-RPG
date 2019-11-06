#include "ChestPlacement.h"


//creates all chests and places them onto the vector
ChestPlacement::ChestPlacement(Sword _sword)//sword passed is the starter sword
{
	//making sword chests and pushing them onto the vector
	for (int i = 1; i <= LevelCap; i++)//3 of each type/element and 1 of each level(1-3).. ommiting the random starter sword
	{
		for (int j = 0; j < NoOfElements; j++)
		{
			//checking for the random starter sword and ommitting it
			if (!(_sword.getElement() == j && i == 1))
			{
				Sword tmpS(Elements(j), i);//temporary sword of element j and level i
				SwordChest *tmpSC;

				if (Chests.size() < maxChests)
				{
					tmpSC = new SwordChest(tmpS);//make a sword chest using the temp sword
					Chests.push_back(tmpSC);//add chest to vector
				}
			}

		}
	}

	//making potion chests and pushing them onto the vector
	for (int i = 1; i <= LevelCap; i++)//2 potions chests of each level(1-3)
	{
		Potion tmpP(i);//temporary potion of level i
		PotionChest *tmpPC1;
		PotionChest *tmpPC2;


		if (Chests.size() < maxChests)
		{
			tmpPC1 = new PotionChest(tmpP);//making 2 potion chests that contain the same properties as the temporary potion
			tmpPC2 = new PotionChest(tmpP);

			Chests.push_back(tmpPC1);//pushing back 2 cuz i want 2 potion chests of each level
			Chests.push_back(tmpPC2);

		}
	}


}

//empties the vector
ChestPlacement::~ChestPlacement()
{
	std::vector<Chest*>::iterator itr;
	for (itr = Chests.begin(); itr != Chests.end();)
	{
		delete *itr;//delete the pointer
		itr = Chests.erase(itr);//erase the vector element
	}
}

//places the chests in order in the rooms according to the room number and updates te map array with chest tiles
void ChestPlacement::placeChests(Cave _cave, Map *_map)
{

	srand(time(0));

	//place the chests in the rooms according to room no. and chest level
	for (int i = 0; i < maxSwordChests; i++)//placing sword chests in the middle of the rooms
	{
		Chests[i]->setY(_cave.getRoomAt(i).getCenter().Y);
		Chests[i]->setX(_cave.getRoomAt(i).getCenter().X);
	}

	//place potion chests

	int i = maxSwordChests;
	// make sure the chest is placed in 2nd corner cuz player spawns in 1st corner of room 0
	Chests[i]->setY(_cave.getRoomAt(0).getCorner2().Y);
	Chests[i]->setX(_cave.getRoomAt(0).getCorner2().X);

	i++;

	int Corner;
	int roomNo = 1;

	while (i < maxChests - 1)
	{
		Corner = (int)(rand() % 2 + 1);
		switch (Corner)//placing the potion chests in a random corner of the room
		{
		case 1:
			Chests[i]->setY(_cave.getRoomAt(roomNo).getCorner1().Y);
			Chests[i]->setX(_cave.getRoomAt(roomNo).getCorner1().X);
			break;
		case 2:
			Chests[i]->setY(_cave.getRoomAt(roomNo).getCorner2().Y);
			Chests[i]->setX(_cave.getRoomAt(roomNo).getCorner2().X);
			break;
		}


		if (roomNo == 1 || roomNo == 2)//placing the next 2 potion chests in the 2nd and 3rd room's corners randomly .. dont ask why.. just embrace it
		{
			roomNo++;
		}

		else { roomNo += 2; }  //placing the rest of potion chests in one of 2 corners of every other room

		i++;
	}

	//update the map with chest tiles according to the chest positions
	for (int i = 0; i < maxChests - 1; i++)
	{
		_map->setTileAt(Chests[i]->getY(), Chests[i]->getX(), ChestSp);
	}
}

//returns chest number i from the vector
Chest* ChestPlacement::getChestAt(int _i)
{
	return Chests[_i];
}

int ChestPlacement::getMaxChests()
{
	return maxChests;
}

//return the current size of the chests vector
int ChestPlacement::getChestsSize()
{
	return Chests.size();
}

//if the player level is 3. Spawns the legendary chest in the 9th room in the cave and updates te map array with a chest tile
void ChestPlacement::spawnLegendaryChest(Cave _cave, Map * _map)
{
	if (Chests.size() < maxChests)
	{
		LegendaryChest *tempL;
		tempL = new LegendaryChest();//create legendary chest
		tempL->setX(_cave.getRoomAt(8).getCenter().X);
		tempL->setY(_cave.getRoomAt(8).getCenter().Y);//set position to the center of the 9th (last) room

		_map->setTileAt(tempL->getY(), tempL->getX(), ChestSp);//update map with a chest tile

		Chests.push_back(tempL);//add chest to the vector
	}
}
