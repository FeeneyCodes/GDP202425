#pragma once

#include <string>
// vector (aka "smart array")
#include <vector>
#include "cMonster.h"

class cMonsterCreator
{
public:
	cMonsterCreator();
	~cMonsterCreator();

	// Pass the 3 US census file names
	bool LoadNames(std::string lastnameFile, std::string boys, std::string girls);

	// This will make a monster
	// Health 100. It'll pick a ransom first and last name
	// NOTE: We are returning a pointer to the monster, not a stack copy
	cMonster* CreateMonster(void);

//	void AttackMonster(unsigned int targetID, float damage);


//	static const unsigned int MAX_SIZE_OF_ARRAY = 100'000;
//	std::string lastNames[MAX_SIZE_OF_ARRAY];
//	unsigned int numberOfNamesInArray = 0;
//
//	std::string lastNames[??];
private:
	std::vector<std::string> m_vecLastNames;
	std::vector<std::string> m_vecBoysNames;
	std::vector<std::string> m_vecGirlsNames;


	std::vector< cMonster* > m_vec_pTheMonsters;


};

