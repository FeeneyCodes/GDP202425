#include <iostream>
#include <string>

#include "cMonster.h"
#include "cMonsterCreator.h"
#include <algorithm>



//int addTwoThings(int a, int b)
//{
//	int result = a + b;
//	return result;
//}
//
//double addTwoThings(double a, double b)
//{
//	double result = a + b;
//	return result;
//}

template <class HelloKitty>
HelloKitty addTwoThings(HelloKitty a, HelloKitty b)
{
	HelloKitty result = a + b;
	return result;
}


// argc : How many parameters were passed. 
//        (at leat 1 always)
// argv : Is a 1D array of string of what was passed.
//        Separated by 'whitespace' (space, tab, etc.)
//        C has no strings, and a string is a char* 
//        It's really a 2D array of char
//         char** argv;
int main( int argc, char* argv[] )
{
//	int x = 9;	int y = 17;
//	int z = addTwoThings(x,y);
//	int z = addTwoThings<int>(x, y);
//	std::cout << "argc = " << argc << std::endl;
//	for (unsigned int index = 0; index != argc; index++)
//	{
//		std::cout << index << " : " << argv[index] << std::endl;
//	}

	cMonsterCreator* pMC = new cMonsterCreator();

	if (!pMC->LoadNames("USCen/US_LastNames.txt",
	                    "USCen/dist.male.first.txt",
	                    "USCen/dist.female.first.txt"))
	{
		std::cout << "ERROR: Didn't load the census files." << std::endl;
		return 1;
	}

	// Assume that the monster loader has loaded the files OK.

	// On the stack (stack based variable)
	// Returning by copying on the stack
	cMonster* pMonster_01 = pMC->CreateMonster();
	cMonster* pMonster_02 = pMC->CreateMonster();

	pMonster_01->PrintStats();
	pMonster_02->PrintStats();

	// What do I do with this monster?? 
	std::vector< cMonster* > vec_pTheMonsters;
	//vec_pTheMonsters.push_back(pMonster_01);
	//vec_pTheMonsters.push_back(pMonster_02);
//
	//pMonster_01->health = 50.0f;
//
	//vec_pTheMonsters[0]->PrintStats();

	int count = 0; 
	do
	{
		cMonster* pNewMon = pMC->CreateMonster();
		vec_pTheMonsters.push_back(pNewMon);
	} while (count != 1000);

	// Do something with the monsters
	for (int index = 0; index != 1000; index++)
	{
		std::cout << vec_pTheMonsters[index]->name << std::endl;
	}

	for (std::vector< cMonster* >::iterator itMon = vec_pTheMonsters.begin(); 
		 itMon != vec_pTheMonsters.end();
		 itMon++)
	{
//		std::cout << vec_pTheMonsters[index]->name << std::endl;
		cMonster* pCM = *itMon;
		pCM->name;

		std::cout << (*itMon)->name << std::endl;
	}

	// How to sort
//	std::sort(vec_pTheMonsters.begin(), vec_pTheMonsters.end(), ??);

	std::vector< cMonster > vecMonsters;
//	std::sort(vecMonsters.begin(), vecMonsters.end());


	pMonster_01->AttackThisMonster(pMonster_02);
	if (pMonster_02->health <= 0.0f)
	{
		// 1. Find the monster in the vector...
		// 2. Remove it from the vector..
		delete pMonster_02;
	}

	delete pMC;


	// TODO:
//	pMC->CreateMonster();

	//std::vector<int> myVector;
	//int x = myVector.size();
	//std::size_t y = myVector.size();
	////     typedef unsigned __int64 size_t;


	int myNumbers[10] = { 1, 3, 6, 2, 4, 7, 2, 16, -9, 99 };
//	qsort(myNumbers, 10);

	//for (unsigned int index = 0; index != 10; index++)
	//{
	//	std::cout << index << " : " << myNumbers[index] << std::endl;
	//}
	//                         V                                  V
	std::vector<int> myVec = { -1, 3, 6, 2, 4, 7, 2, 16, -9, 99 };
//	myVec.push_back(1);
//	myVec.push_back(3);

	for (unsigned int index = 0; 
		 index != 10;		// the biggest index is really 9
		 index++)
	{
		std::cout << index << " : " << myVec[index] << std::endl;
	}

	for (std::vector<int>::iterator itVec = myVec.begin();
		 itVec != myVec.end();
		 itVec++)
		 
	{
		//std::cout << index << " : " << myVec[index] << std::endl;
		std::cout << *itVec << std::endl;
	}

	//for (std::vector<int>::reverse_iterator itVec = myVec.rbegin();
	//	itVec != myVec.rend();
	//	itVec++)

	//{
	//	//std::cout << index << " : " << myVec[index] << std::endl;
	//	std::cout << *itVec << std::endl;
	//}

	std::cout << "*************" << std::endl;
	std::sort(myVec.begin(), myVec.end());

	for (std::vector<int>::iterator itVec = myVec.begin();
		 itVec != myVec.end();
		 itVec++)
		 
	{
		//std::cout << index << " : " << myVec[index] << std::endl;
		std::cout << *itVec << std::endl;
	}

	std::cout << "*************" << std::endl;
//	std::vector<int>::iterator it99 = std::find(myVec.begin(), myVec.end(), 99);
	std::vector<int>::iterator it99 = std::find(myVec.begin(), myVec.end(), 7);
	// Found it? 
	if (it99 == myVec.end())
	{
		std::cout << "didn't find it" << std::endl;
	}
	else
	{
		// FOund it!
		std::cout << *it99 << std::endl;
		// remove it
		myVec.erase(it99);
	}

	return 0;
}




























//// OLD code we aren't using and will delete
////	system("pause");
//
//std::cout << "Hey..." << std::endl;
//{
//	//		cMonster monster;  // Stack variable (no "new")
//	cMonster* pMonster = new cMonster();		// HEAP
//
//	//		cMonster* pMosnter = (cMonster*)malloc((size_t)sizeof(cHuman));
//
//	std::cout << "the air show was fun." << std::endl;
//
//	delete pMonster;
//	//		free(pMosnter);
//}
//std::cout << "you." << std::endl;
//
////cMonster Fred;
////cMonster Mary = Fred;
////cMonster Sally(Fred);