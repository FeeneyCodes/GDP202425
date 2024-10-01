#include <iostream>
#include "cMonster.h"
#include "cSuperMonster.h"
#include <vector>

int main(int argc, char* argv[])
{
	//	cMonster* pBob = new cMonster("bob");
	//	pBob->KillAllHumans();

	//	cSuperMonster pSally1;
		// What kind of monster is Sally IF this worked??
	//	cSuperMonster* pSally = new cMonster("sally");
	//  void* pOhGawdNo = new cMonster("sally");
	//  ((cSuperMonster*)pOhGawdNo)->GiveBirth(29);
	//  ((cMonster*)pOhGawdNo)->

	cSuperMonster* pSally = new cSuperMonster("sally");

	pSally->KillAllHumans();
	pSally->lastName = "Jones";
	pSally->GiveBirth(10);

//	std::vector<cMonster* > vecMonsters;
//	std::vector<cSuperMonster*> vecSuperMonsters;

	std::vector< cMonster* > vecAllMonsters;
//	std::vector< cSuperMonster* > vecAllMonsters;

	cMonster* pMatt = new cMonster("Matt");
	vecAllMonsters.push_back(pMatt);

	cSuperMonster* pAli = new cSuperMonster("Ali");
	vecAllMonsters.push_back(pAli);

	vecAllMonsters[0]->MakeNoise();		// Matt
	vecAllMonsters[1]->MakeNoise();		// Ali
	((cSuperMonster*)vecAllMonsters[1])->MakeNoise();		// Ali


	vecAllMonsters[0]->KillAllHumans();		// Matt (monster)

	vecAllMonsters[1]->KillAllHumans();		// Ali (Super Monster)
	pAli->GiveBirth(10);
	// This will NOT work, because this is non-polymorphic inheritance
	// That's not something that's in C# or Java or anything else.
//	vecAllMonsters[1]->GiveBirth(10);

	((cSuperMonster*)vecAllMonsters[1])->GiveBirth(556);


	delete pSally;

	return 0;
}
