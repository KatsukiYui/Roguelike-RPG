#include "Cave.h"


//the constructor calls the makeRooms and makeCorridors functions to place the rooms in the rooms vector
//then it updates the tile array with the right tiles using the rooms vector
Cave::Cave(Map &_map)
{
	srand(time(0)); //for the random room generation

	_Empty.setType(Empty);//rooms are made out of tiles of type empty

	makeRooms(_map);//add rooms onto the array

	for (int i = 0; i < Rooms.size(); i++)//sets the room tiles from first to 2nd room corner to empty tiles in the tile map array for each room
	{
		for (int row = Rooms[i].getCorner1().Y; row <= Rooms[i].getCorner2().Y; row++)
		{
			for (int col = Rooms[i].getCorner1().X; col <= Rooms[i].getCorner2().X; col++)
			{

				_map.setTileAt(row, col, _Empty);

			}
		}
	}

	makeCorridors(_map);//connect the rooms with corridors (tiles of type empty)

}


Cave::~Cave()
{

}

//creates and places rooms
void Cave::makeRooms(Map &_map)
{
	for (int i = 0; i < roomNum; i++)//make a number of rooms equal to max roomNum
	{
		Vec2 vec2; //used to pass a point with x and y coords
		Room R;

		bool Collision = true;

		while (Collision)//while the current room is colliding with another room in the rooms vector, make a new room
		{
			//random width and height according to the min and max size variables
			R.setHeight((rand() % ((maxRoomSize - minRoomSize) + 1)) + minRoomSize);
			R.setWidth((rand() % ((maxRoomSize - minRoomSize) + 1)) + minRoomSize);

			vec2.X = ((rand() % (_map.mapC - R.getWidth() - 1)) + 1); //first corner vector
			vec2.Y = ((rand() % (_map.mapR - R.getHeight() - 1)) + 1);
			R.setCorner1(vec2);

			vec2.X = R.getCorner1().X + R.getWidth() - 1; //second corner vector
			vec2.Y = R.getCorner1().Y + R.getHeight() - 1;
			R.setCorner2(vec2);

			vec2.X = (R.getCorner1().X + R.getCorner2().X) / 2; //center vector
			vec2.Y = (R.getCorner1().Y + R.getCorner2().Y) / 2;
			R.setCenter(vec2);

			if (Rooms.size() > 0)//if this isnt the first room
			{
				Collision = collisionCheck(R); //check for room collision with other rooms in the vector
			}
			else if (Rooms.size() == 0)//if this is the first room
			{
				Collision = false; //its the first room just break out of the loop
			}
		}

		Rooms.push_back(R); // add the room to the vector

	}
}

//collision checks between rooms in the vector
bool Cave::collisionCheck(Room R)
{
	bool Hit = false;//if hit == true the room collided with another room on the vector
	int i = 0;

	while(i < Rooms.size() && Hit == false) //exit the loop if there was a collision
	{
		//chec for collision
		if (R.getCorner1().X <= Rooms[i].getCorner2().X +5 && R.getCorner2().X +5 >= Rooms[i].getCorner1().X &&
			R.getCorner1().Y <= Rooms[i].getCorner2().Y +5 && R.getCorner2().Y +5 >= Rooms[i].getCorner1().Y)
		{
			Hit = true;
		}
		else
		{
			Hit = false;
		}

		i++;
	}

	return Hit;
};

//makes corridors that connect the rooms
void Cave::makeCorridors(Map &_map) //makes empty corridors in the array
{

	for (int i = 0; i < Rooms.size() - 1; i++)//connects each room's center with the next room's center
	{
		int Dir = rand() % 2;//this determines the direction the corridor will be made in first, horizontally or vertically

		int row = Rooms[i].getCenter().Y;
		int col = Rooms[i].getCenter().X;

		switch (Dir)//0 for horizontal first and 1 for vertical first
		{
		case 0://horizontally first


			while (col != Rooms[i + 1].getCenter().X)//while this room's center isnt connected to the next one/this corridor isnt at the next room's center
			{
				while (row != Rooms[i + 1].getCenter().Y)
				{
					_map.setTileAt(row, col, _Empty);//coridors are just empty tiles, set the tile map array to empty at this index

					if (Rooms[i].getCenter().Y < Rooms[i + 1].getCenter().Y)//incerement or decrement the  counter based on the rooms positions
					{
						row++;
					}
					else
					{
						row--;
					}

				}

				_map.setTileAt(row, col, _Empty);//coridors are just empty tiles, set the tile map array to empty at this index

				if (Rooms[i].getCenter().X < Rooms[i + 1].getCenter().X)//incerement or decrement the  counter based on the rooms positions
				{
					col++;
				}
				else
				{
					col--;
				}
			}

			break;

		case 1://vertically first


			while (row != Rooms[i + 1].getCenter().Y)//while this room's center isnt connected to the next one/this corridor isnt at the next room's center
			{
				while (col != Rooms[i + 1].getCenter().X)
				{
					_map.setTileAt(row, col, _Empty);//coridors are just empty tiles, set the tile map array to empty at this index

					if (Rooms[i].getCenter().X < Rooms[i + 1].getCenter().X)//incerement or decrement the  counter based on the rooms positions
					{
						col++;
					}
					else
					{
						col--;
					}

				}

				_map.setTileAt(row, col, _Empty);//coridors are just empty tiles, set the tile map array to empty at this index

				if (Rooms[i].getCenter().Y < Rooms[i + 1].getCenter().Y)//incerement or decrement the  counter based on the rooms positions
				{
					row++;
				}
				else
				{
					row--;
				}
			}

			break;
		}

	}
}

//used to detect what room the player is in
bool Cave::findRoom(int *roomNo, int _xpos, int _ypos)
{
	bool found = false;

	for (int i = 0; i < Rooms.size(); i++)//loop through the rooms and do collision checks with the player's position
	{
		if (Rooms[i].getCorner1().X <= _xpos && Rooms[i].getCorner2().X >= _xpos &&
			Rooms[i].getCorner1().Y <= _ypos && Rooms[i].getCorner2().Y >= _ypos)
		{
			found = true;
			*roomNo = i;//update room number with the number of the room the player is in (0-8)
		}
	}

	return found;//return true if player in a room, if in a corridor it returns false
}

//return the room number i from the vector
Room Cave::getRoomAt(int _i)
{
	return Rooms[_i];
};