#ifndef _SWORD_
#define _SWORD_

#include "Elemental.h"

class Sword : public Elemental//an item used to attack enemies. A swords has an element, damage and a level, all inherited from the Elemental Parent class
{
protected:

	Vec2 swordText[3];//used to save x and y positions to access the individual sword textures

public:
	Sword();

	//dmg is calculated from lvl
	Sword(Elements _ele, int _lvl);

	//returns the position of the texture at i in the swords texture(texture with 3 swords)
	Vec2 getTextAt(int _t);

};

#endif // !_SWORD_
