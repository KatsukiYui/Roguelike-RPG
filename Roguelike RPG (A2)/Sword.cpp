#include "Sword.h"

Sword::Sword()
{
	for (int i = 0; i < 3; i++)
	{
		swordText[i].X = i * 70;//the texture is 210*70 pixels.. it contains 3 swords
		swordText[i].Y = 70;
	}
};

Sword::Sword(Elements _ele, int _lvl)
	:Elemental(_ele, _lvl, (int)(_lvl * 5))
{
	for (int i = 0; i < 3; i++)
	{
		swordText[i].X = i * 70;//the texture is 210*70 pixels.. it contains 3 swords
		swordText[i].Y = 0;
	}
}

Vec2 Sword::getTextAt(int _t)
{
	return swordText[_t];
};