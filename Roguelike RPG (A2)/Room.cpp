#include "Room.h"

Room::Room() 
{
	Vec2 vec2;
	Width = 0;
	Height = 0;
	Corner1 = vec2;
	Corner2 = vec2;
	Center = vec2;
};

Room::Room(int _w, int _h, Vec2 _c1, Vec2 _c2, Vec2 _cntr)
{
	Width = _w;
	Height = _h;
	Corner1 = _c1;
	Corner2 = _c2;
	Center = _cntr;
}


Room::~Room()
{
}

void Room::setWidth(int _w) { Width = _w; };
void Room::setHeight(int _h) { Height = _h; };
void Room::setCorner1(Vec2 _c1) { Corner1 = _c1; };
void Room::setCorner2(Vec2 _c2) { Corner2 = _c2; };
void Room::setCenter(Vec2 _cntr) { Center = _cntr; };

int Room::getWidth() { return Width; };
int Room::getHeight() { return Height; };
Vec2 Room::getCorner1() { return Corner1; };
Vec2 Room::getCorner2() { return Corner2; };
Vec2 Room::getCenter() { return Center; };
