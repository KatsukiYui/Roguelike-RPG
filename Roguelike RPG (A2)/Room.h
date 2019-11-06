#ifndef _ROOM_
#define _ROOM_

#include "Vec2.h"
#include <SDL.h>
#include <vector>

class Room//represents the empty spaces in the cave. The cave is made out of 9 rooms currently.
{

protected:
	int Width;
	int Height;
	Vec2 Corner1;//coordinates of the top left corner of the room
	Vec2 Corner2;//coordinates of the bottom right corner of the room
	Vec2 Center;//coordinates of the center of the room

public:
	Room();
	Room(int _w, int _h, Vec2 _c1, Vec2 _c2, Vec2 _cntr);
	~Room();

	void setWidth(int _w);
	void setHeight(int _h);
	void setCorner1(Vec2 _c1);
	void setCorner2(Vec2 _c2);
	void setCenter(Vec2 _cntr);

	int getWidth();
	int getHeight();
	Vec2 getCorner1();
	Vec2 getCorner2();
	Vec2 getCenter();



};

#endif