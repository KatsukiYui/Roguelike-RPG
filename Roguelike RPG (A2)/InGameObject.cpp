#include "InGameObject.h"

InGameObject::InGameObject(int _x, int _y, int _lvl) 
{
	xPos = _x;
	yPos = _y;
	Level = _lvl;

};


void InGameObject::setLevel(int _lvl) { Level = _lvl; };
void InGameObject::setX(int _x) { xPos = _x; };
void InGameObject::setY(int _y) { yPos = _y; };

int InGameObject::getLevel() { return Level; };
int InGameObject::getX() { return xPos; };
int InGameObject::getY() { return yPos; };