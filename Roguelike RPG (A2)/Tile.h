#ifndef _TILE_
#define _TILE_

#include <SDL.h>

enum tileType { Wall, Empty, PlayerSp, ChestSp }; //empty is where rooms and corridors are since its empty spaces 
                                                  //player and chest sprites

class Tile//used to make the map 2D array. A tile is just a type/enum currently.
{
protected:
	tileType Type;
	
public:
	
	Tile();
	Tile(tileType _type);

	~Tile();

	void setType(tileType _type);

	tileType getType();

 };


#endif // !_TILE_

