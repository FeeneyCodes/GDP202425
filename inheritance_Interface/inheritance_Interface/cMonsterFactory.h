#pragma once

#include "iMonster.h"
#include <string>

class cMonsterFactory
{
public:
	//	cMonsterFactory();

	// Factory method
	// The type I pass has to be a known type.
	// Don't use an enum or something like that...
	iMonster* createMonster(std::string monsterType);
};
