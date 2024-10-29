#pragma once

#include "cSword.h"

class cMonster
{
public:
	cSword* pSword;
	void Attack(cMonster *EnemyMonster);
	float health;
};
