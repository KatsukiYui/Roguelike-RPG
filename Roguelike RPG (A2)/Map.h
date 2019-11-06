#ifndef _MAP_
#define _MAP_

#include "Tile.h"
#include <iostream>

class Map//makes and manages both the full tile map and view map
{
public:
	
	static const int mapC = 100;//number of columns in full map
	static const int mapR = 100;//number of rows in full map

	static const int viewC = mapC/10 + 1;//number of columns in the view map (currently 11*11 map surrounding the player)
	static const int viewR = mapR/10 + 1;//number of rows in the view map (currently 11*11 map surrounding the player)

	//return the tile at this index
	Tile getTileAt(const int _r, const int _c);

	//set the tile at this index to this tile
	void setTileAt(const int _r, const int _c, Tile _t); 

	//same as above but for the viewing map tiles.
	Tile getViewTileAt(const int _r, const int _c);
	void setViewTileAt(const int _r, const int _c, Tile _t);

	//moves the camera. Makes the viewing map according to the full map and the player's x and y positions
	void View(int _x, int _y);

protected:

	Tile tileMap[mapC][mapR];//full map of the cave with all the rooms etc. Made with tiles which are techincally a type. Empty tiles are rooms, player tile is the player etc
	Tile viewMap[viewC][viewR];//acts as a camera that follows the player
};


#endif // !_MAP_
