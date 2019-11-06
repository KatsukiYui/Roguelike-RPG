#include "Elemental.h"

Elemental::Elemental() {};

Elemental::Elemental(Elements _ele, int _lvl, int _dmg)
{
	Element =_ele;
	Level = _lvl;
	DMG = _dmg;
};

//attack function. This is called by both the swords and the Enemies (derived classes), where the opponenet is the other derived class
void Elemental::Attack(int *_opponentHp, Elements _opponentEle)
{
	switch (Element)//if this elemental's element is:
	{
	case Fire:
		switch (_opponentEle)//if the opponent elemental's element is:
		{
		case Fire:
			*_opponentHp -= DMG;//same element so no dmg buff/debuff
			break;

		case Water:
			*_opponentHp -= (int)(DMG * Weakness);//fire is weak against water so half the damage
			break;

		case Earth:
			*_opponentHp -= (DMG * Strength);//fire is strong against earth to double the damage
			break;

		case NoElement:
			std::cout << "Opponent has no element" << std::endl;
			break;
		}
		break;

	case Water:
		switch (_opponentEle)
		{
		case Fire:
			*_opponentHp -= (DMG * Strength);
			break;

		case Water:
			*_opponentHp -= DMG;
			break;

		case Earth:
			*_opponentHp -= (int)(DMG * Weakness);
			break;

		case NoElement:
			std::cout << "Opponent has no element" << std::endl;
			break;
		}
		break;

	case Earth:
		switch (_opponentEle)
		{
		case Fire:
			*_opponentHp -= (int)(DMG * Weakness);
			break;

		case Water:
			*_opponentHp -= (DMG * Strength);
			break;

		case Earth:
			*_opponentHp -= DMG;
			break;

		case NoElement:
			std::cout << "Opponent has no element" << std::endl; //error if there isnt an element
			break;
		}
		break;

	case NoElement:
		std::cout << "Attacker has no element" << std::endl; //error if there isnt an element
		break;
	}

};


void Elemental::setElement(Elements _ele) { Element = _ele; }; 
void Elemental::setLevel(int _lvl) { Level = _lvl; };
void Elemental::setDMG(int _dmg) { DMG = _dmg; };

Elements Elemental::getElement() { return Element; };
int Elemental::getLevel() { return Level; };
int Elemental::getDMG() { return DMG; }
