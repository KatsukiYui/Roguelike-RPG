#include "Map.h"


//return the tile at this index
Tile Map::getTileAt(const int _r, const int _c)
{
	if (_r <= mapR && _r >= 0 && _c <= mapC && _c >= 0)
	{
		return tileMap[_r][_c];
	}
	else
	{
		std::cout << "index provided is outside array bounds" << std::endl;
	}
};

//set the tile at this index to this tile
void Map::setTileAt(const int _r, const int _c, Tile _t)
{

	if (_r <= mapR && _r >= 0 && _c <= mapC && _c >= 0)
	{
		tileMap[_r][_c] = _t;
	}
	else
	{
		std::cout << "index provided is outside array bounds" << std::endl;
	}
};

//same as above but for the viewing map tiles.
Tile Map::getViewTileAt(const int _r, const int _c)
{
	if (_r <= viewR && _r >= 0 && _c <= viewC && _c >= 0)
	{
		return viewMap[_r][_c];
	}
	else
	{
		std::cout << "index provided is outside array bounds" << std::endl;
	}

};

void Map::setViewTileAt(const int _r, const int _c, Tile _t)
{
	if (_r <= viewR && _r >= 0 && _c <= viewC && _c >= 0)
	{
		viewMap[_r][_c] = _t;
	}
	else
	{
		std::cout << "index provided is outside array bounds" << std::endl;
	}
};

//moves the camera. Makes the viewing map according to the full map and the player's x and y positions
void Map::View(int _x, int _y)
{
	int r;
	int c;

	//setting the view so that the player is at the centre of the screen

	//first the min Y
	if (_y < (int)(viewR / 2))//if Y is < 5 .. first extreme if player is super close to the map's edges
	{
		r = 0;
	}
	else if (_y >= (mapR - (int)(viewR / 2) - 1))//if Y is >= 94 .. if player is super close to the map's edge
	{
		r = mapR - (int)(viewR) - 1;//start view at 89
	}
	else //if they arent just calculate it normally
	{
		r = _y - (viewR / 2);
	}

	//now the min X

	if (_x < (int)(viewC / 2))//if X is < 5.. if player is super close to the map's edge
	{
		c = 0;
	}
	else if (_x >= (mapC - (int)(viewC / 2) - 1))//if X is >= 94.. if player is super close to the map's edge
	{
		c = mapC - (int)(viewC) - 1;//start view at 89
	}
	else //if they arent just calculate it normally
	{
		c = _x - (viewC / 2);
	}


	//now make the view map
	for (int vr = 0; vr < viewR; vr++)//draw rows
	{
		//resetting C or X at extremes/edges of the tile map
		if (_x < (int)(viewC / 2))//if X is < 5
		{
			c = 0;
		}
		else if (_x >= (mapC - (int)(viewC / 2) - 1))//if X is >= 94
		{
			c = mapC - (int)(viewC)-1;
		}
		else
		{
			c = _x - (viewC / 2);
		}

		for (int vc = 0; vc < viewC; vc++)//draw columns
		{
			viewMap[vr][vc] = tileMap[r][c];

			c++;

		}


		r++;

	}

};