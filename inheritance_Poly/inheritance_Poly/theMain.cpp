#include <iostream>
#include "cMonster.h"
#include "cSuperMonster.h"
#include "cFlyingMonster.h"
#include "cSuperFlyingMonster.h"
#include <vector>

int main(int argc, char* argv[])
{
	cMonster* pFrank = new cMonster("Frank");
	cSuperMonster* pSally = new cSuperMonster("Sally");
	cFlyingMonster* pAli = new cFlyingMonster("Ali");
	std::cout << "----------------------" << std::endl;
	cSuperFlyingMonster* pRobin = new cSuperFlyingMonster("Robin");

//	((cMonster*)pRobin)->MakeNoise();

	// ... a whole lot of various monsters are created...
	// 100s of each monster

	// The monsters are looking for friends...
	std::vector<cMonster*> vec_pMonsters;
//	std::vector<cSuperMonster*> vec_pSuperMonster;
//	std::vector<cFlyingMonster*> vec_pFlyingMonsters;


	vec_pMonsters.push_back(pFrank);
	vec_pMonsters.push_back(pAli);
	vec_pMonsters.push_back(pSally);
//	vec_pMonsters.push_back(pRobin);

	for (unsigned int index = 0; index != vec_pMonsters.size(); index++)
	{
		std::cout << vec_pMonsters[index]->firstName << std::endl;

		// The type of monster we ACTUALLY created 
		//	determins the method that we call 
		// AT RUN TIME
		
		// is virtual, so uses v-table lookup at run time
		vec_pMonsters[index]->Update(1.0);

		// Isn't virtual, so ONLY calls the one that the 
		//	type is referring to (cMonster in this case)
		vec_pMonsters[index]->MakeNoise();

	}



	bool bKeepGoing = true;
	while (bKeepGoing)
	{
		// For each monster:
		//	- Look through the monster vector to find a friend
		//  - Also, look through the supermonster vector to find a friend
		//  - Also, the flying monster


	}





	delete pFrank;
	delete pSally;
	delete pAli;


	return 0;
}




// OLD main
int main_September_30th(int argc, char* argv[])
{
	//	cMonster* pBob = new cMonster("bob");
	//	pBob->KillAllHumans();

	//	cSuperMonster pSally1;
		// What kind of monster is Sally IF this worked??
	//	cSuperMonster* pSally = new cMonster("sally");
	//  void* pOhGawdNo = new cMonster("sally");
	//  ((cSuperMonster*)pOhGawdNo)->GiveBirth(29);
	//  ((cMonster*)pOhGawdNo)->

//	cSuperMonster* pSally = new cSuperMonster("sally");
	cMonster* pSally = new cSuperMonster("sally");
	pSally->MakeNoise();
	//	pSally->GiveBirth();
	//	((cSuperMonster*)pSally)->GiveBirth(45);


	pSally->KillAllHumans();
	pSally->lastName = "Jones";
	//	pSally->GiveBirth(10);

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
