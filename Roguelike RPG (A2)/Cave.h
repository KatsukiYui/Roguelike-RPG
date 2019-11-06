#ifndef _CAVE_
#define _CAVE_

#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime> 
#include "Map.h"
#include "Room.h"

/*this is the cave or environment class. This class contains a vector of rooms, the functions to create them,
the intersection checks and the functions to draw corridors to connect all the rooms together.
*/


class Cave
{
protected:

	static const int maxRoomSize = 20;
	static const int minRoomSize = 10; //room size in tiles (6*6).. so in pixels.. from 90 to 150 pixels per room
	std::vector<Room> Rooms;// a vector of a max of 9 rooms
	Tile _Empty;//empty tile for the rooms(tile of type(tileType enum) empty basically)
	static const int roomNum = 9;//max number of rooms

public:
	//the constructor calls the makeRooms and makeCorridors functions to place the rooms in the rooms vector
	//then it updates the tile array with the right tiles using the rooms vector
	Cave(Map &_map); 
	~Cave();                   

	//creates and places rooms
	void makeRooms(Map &_map); 

	//collision checks between rooms in the vector
	bool collisionCheck(Room R);

	//makes corridors that connect the rooms
	void makeCorridors(Map &_map); 

	//used to detect what room the player is in
	bool findRoom(int *roomNo, int _xpos, int _ypos);

	//return the room number i from the vector
	Room getRoomAt(int _i);
};



#endif
