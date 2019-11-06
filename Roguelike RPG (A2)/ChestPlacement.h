#ifndef _CHEST_PLACE_
#define _CHEST_PLACE_

#include <iostream>
#include <vector>
#include "Chest.h"
#include "SwordChest.h"
#include "PotionChest.h"
#include "LegendaryChest.h"
#include "Cave.h"
#include "Map.h"

#define LevelCap 3 //max chest level

class ChestPlacement
{
protected:
	std::vector<Chest*> Chests;//vector of chest pointers. 3 different child class pointers are pushed onto this vector
	const int maxChests = 15; //9 swords(player is spawned with 1).. 1 legendary and 6 potions
	const int maxPotionChests = 6;//max number for spawned potion chests
	const int maxSwordChests = 8;//max number for spawned potion chests

public:

	//creates all chests and places them onto the vector
	ChestPlacement(Sword _sword);

	//empties the vector
	~ChestPlacement();

	//places the chests in order in the rooms according to the room number and updates te map array with chest tiles
	void placeChests(Cave _cave, Map *_map);

	//returns chest number i from the vector
	Chest* getChestAt(int _i);

	int getMaxChests();

	//return the current size of the chests vector
	int getChestsSize();

	//if the player level is 3. Spawns the legendary chest in the 9th room in the cave and updates te map array with a chest tile
	void spawnLegendaryChest(Cave _cave, Map *_map);


};


#endif // !_CHEST_PLACE_
