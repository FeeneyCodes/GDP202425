#include "cMonsterFactory.h"

#include "cMonster.h"
#include "cSuperMonster.h"
#include "cFlyingMonster.h"

iMonster* cMonsterFactory::createMonster(std::string monsterType)
{
	if (monsterType == "Super Duper Monster")
	{
		return new cSuperMonster();
	}
	if (monsterType == "Boring regular monster")
	{
		return new cMonster();
	}
	if (monsterType == "Monster that flies")
	{
		return new cFlyingMonster();
	}

	
	// What are you talking about??? 
	return NULL;
}