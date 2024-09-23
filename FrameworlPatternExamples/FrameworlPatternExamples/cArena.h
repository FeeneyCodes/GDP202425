#pragma once

#include <vector>
#include "cMonsterCreator.h"

// This represnet the level of our game 
// which is the arena where we fight the monsters
class cArena
{
public:
	// TODO: We might want to pass other info?
	bool InitLevel(unsigned int numberOfMonsters, cVector3 arenaSize);

	void PrintMonsters(void);

private:
	std::vector<cMonster*> m_vec_pTheMonsters;
};

