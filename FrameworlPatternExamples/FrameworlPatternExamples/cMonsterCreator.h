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
	bool LoadNamesDefault(void);

	// This will make a monster
	// Health 100. It'll pick a ransom first and last name
	// NOTE: We are returning a pointer to the monster, not a stack copy
	cMonster* CreateMonster(void);
	cMonster* CreateMonster(int typeID);

	// NEVER do this in C or C++
	// See below
//	cMonster& CreateMonster(void);

	// 
//	bool CreateMonster(cMonster& theMonster);
//	bool CreateMonster(cMonster* &pMonster);
//	// 0 is OK, anything else means an error
//	int CreateMonster(cMonster& theMonster);
	bool CreteMonster(int typeID, std::vector<cMonster> &vecMonsters);

	// TODO:
	// ?? FindMonstersWithThisFirstName( std::string firstName );

	//std::vector<cMonster> GetAllMonsters(void);
	//bool GetAllMonsters(vector<cMonster> &vecMonsters);
	//bool GetAllMonsters(vector<cMonster> *vecMonsters);

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


//	std::vector< cMonster* > m_vec_pTheMonsters;


};




///// Comments
//// NEVER do this in C or C++
//cMonster& CreateMonster(void)
//{
//	cMonster Frank;
//	return Frank;
//}
//
//// Code
//cMonster Sally = CreateMonster();		// Actually Frank
////
//// ... oh no
//Sally.KillAllHumans();