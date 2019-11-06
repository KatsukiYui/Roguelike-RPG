#ifndef _ENEMY_
#define _ENEMY_

#include "Elemental.h"
#include "Player.h"
#include "Sword.h"

class Enemy: public Elemental//manages the enemy's health and exp drop. DMG and attacking is done in the base class.
{
protected:

	int HP;
	int maxHP;//used for for printing the outer HP Bar (empty red rectangle)
	int expDrop;//is added to the player's exp when the player kills the enemy.

public:

	Enemy(Elements _ele, int _lvl);//dmg is calculated from lvl

	void setHP(int _hp);
	void setEXP(int _exp);

	int getHP();
	int getEXP();
	int getMaxHP();

};

#endif // !_ENEMY_

