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
	std::cout << "A cMonsters is DESTROYED" << std::endl;
}

void cMonster::KillAllHumans(void)
{
	std::cout << "I will hill all the humans!" << std::endl;
	return;
}
