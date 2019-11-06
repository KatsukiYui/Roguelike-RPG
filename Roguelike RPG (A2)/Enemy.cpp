#include "Enemy.h"

Enemy::Enemy(Elements _ele, int _lvl)
	:Elemental(_ele, _lvl, (int)(_lvl*6))//dmg is calculated from lvl
{
	HP = _lvl * 30;//hp and expDrop are based on level
	maxHP = HP;
	expDrop = _lvl * 25;
};

void Enemy::setHP(int _hp) { HP = _hp; };
void Enemy::setEXP(int _exp) { expDrop = _exp; };

int Enemy::getHP() { return HP; };
int Enemy::getEXP() { return expDrop; }
int Enemy::getMaxHP()
{
	return maxHP;
}

