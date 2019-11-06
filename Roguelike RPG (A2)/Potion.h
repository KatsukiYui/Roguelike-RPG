#ifndef _POTION_
#define _POTION_

#include "Player.h"

class Potion//an item type that heals the player
{
protected:

	int Heal;//hp regained from the potion
	int Level;//the Hp the potion heals is calculated from level


public:

	Potion();

	Potion(int _l);

	int getHeal();
	int getLevel();

	void setHeal(int _h);
	void setLevel(int _l);

	//adds HP to the player equal to the potion's heal. Avoids overhealing the player by doing a check against maxHP
	void healPlayer(Player *_play);
};


#endif // !_POTION_
