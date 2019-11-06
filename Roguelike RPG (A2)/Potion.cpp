#include "Potion.h"

Potion::Potion() {}


Potion::Potion(int _l)
{
	Level = _l;

	Heal = (Level - 1) * 25 + 50;//heal equal to the hp of the player at same level (used same formula)
};

int Potion::getHeal()
{
	return Heal;
}

int Potion::getLevel()
{
	return Level;
}

void Potion::setHeal(int _h)
{
	Heal = _h;
}

void Potion::setLevel(int _l)
{
	Level = _l;
}

//adds HP to the player equal to the potion's heal. Avoids overhealing the player by doing a check against maxHP
void Potion::healPlayer(Player * _play)
{
	int temp = _play->getHP();

	if (temp + Heal >= _play->getMaxHP())//is it gonna exceed the max HP?
	{
		temp = _play->getMaxHP();//set current HP to max HP
	}
	else
	{
		temp += Heal;//otherwise add heal
	}

	_play->setHP(temp);
}
