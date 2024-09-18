#include "cMonster.h"
#include <iostream>

// constructor (c'tor)
cMonster::cMonster()
{
	std::cout << "A cMonster is created!" << std::endl;

//	health = defaultHealth;
}

// destructor (d'tor)
cMonster::~cMonster()
{
	// 1. Find the monster in the vector...
	// 2. Remove it from the vector..

	std::cout << "A cMonsters is DESTROYED" << std::endl;
}

void cMonster::KillAllHumans(void)
{
	std::cout << "I will hill all the humans!" << std::endl;
	return;
}

void cMonster::PrintStats(void)
{
	std::cout << this->name << " : " << this->health << std::endl;
	// TODO: Print location, too? 
	return;
}

void cMonster::AttackThisMonster(cMonster* pTarget)
{
	pTarget->health -= 25.0f;
	return;
}
