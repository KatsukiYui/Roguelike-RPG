#ifndef _ELEMENTAL_
#define _ELEMENTAL_

/* This class is the parent class for everything with an element that basically attacks. The Sword and Enemy classes 
are derived from this class.*/

#include <iostream>
#include "Vec2.h"

//Type or element Enum

enum Elements
{
	Fire,
	Water,
	Earth,
	NoElement//empty element.. till it is set, used to create a sword then randomly generate its element (for the starter sword)
}; 

#define NoOfElements 3//number of elements (except no element ofc) that are in the enum
#define Weakness 0.5//Damage is multiplied  by it if the opponent is of a stronger element (e.g. Water vs Earth. If the opponenet is an Earth type, this elemenatal's Damage is halved)
#define Strength 2//Damage is multiplied  by it if the opponent is of a weaker element (e.g. Water vs Fire. If the opponenet is an Fire type, this elemenatal's Damage is doubled)

class Elemental
{

protected:

	Elements Element; //creative naming. The element of this elemental (Fire, Water or Earth)
	int Level;//current level of the elemental(cap is 3)
	int DMG;//Damage of the elemental, is fixed according to the elemental's level


public:

	Elemental();

	Elemental(Elements _ele, int _lvl, int _dmg);

	void setElement(Elements _ele); 
	void setLevel(int _lvl);
	void setDMG(int _dmg);

	Elements getElement();
	int getLevel();
	int getDMG();

	//attack function. This is called by both the swords and the Enemies (derived classes), where the opponenet is the other derived class
	void Attack(int *_opponentHp, Elements _opponentEle);


};


#endif