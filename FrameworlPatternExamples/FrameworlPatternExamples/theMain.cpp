#include <iostream>
#include <string>

//#include "cMonster.h"
//#include "cMonsterCreator.h"
#include "cArena.h"
#include <algorithm>
#include <iterator>			// For the back inserter
#include <sstream>		// string stream or string builder
#include <map>
#include <list>



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

template <class T>
T addTwoThings(T a, T b)
{
	T result = a + b;
	return result;
}


// HOW you overload an operator
// NOTE: You almost NEVER really want to do this!!
//bool operator<(cMonster& A, cMonster& B)
//{
//	if (A.age < B.age)
//	{
//		return true;
//	}
//	return false;
//}

bool compareByAgeLessThan(cMonster& A, cMonster& B)
{
	if (A.age < B.age)
	{
		return true;
	}
	return false;
}

//cMonster& operator<<(cMonster& A)
////{
////	if (A.age < B.age)
////	{
////		return true;
////	}
////	return false;
////}
//cout << myMonster

// argc : How many parameters were passed. 
//        (at leat 1 always)
// argv : Is a 1D array of string of what was passed.
//        Separated by 'whitespace' (space, tab, etc.)
//        C has no strings, and a string is a char* 
//        It's really a 2D array of char
//         char** argv;
//
// Param 1: Number of monsters	 (argv[1])
// Param 2: Width of arena		(argv[2])
// Param 3: Depth of arena		(argv[3])
int main(int argc, char* argv[])
{
	// Check the params
	if (argc != 4)
	{
		std::cout << "Usage: Game.exe n x y " << std::endl;
		std::cout << "(read the documentation" << std::endl;
		return -1;
	}
	//"50"   "1000"  "2000"
	// c: atoi()  atof()

	unsigned int numberOfMonsters = atoi(argv[1]);
	cVector3 arenaSize;
	arenaSize.x = (float)atof(argv[2]);						// "C style"
	arenaSize.y = static_cast<float>( atof(argv[3]) );		// "C++ style"
	arenaSize.z = 0.0f;


//	std::cout << argv[1];
//	std::cin >> numberOfMonsters;
	std::stringstream ssNumber;
	ssNumber << argv[1];
	ssNumber >> numberOfMonsters;


	cArena* pTheArena = new cArena();

	pTheArena->InitLevel( numberOfMonsters, arenaSize);

	pTheArena->PrintMonsters();


	delete pTheArena;


	// LIST
	std::list<int> myListInts;
	myListInts.insert(myListInts.end(), 54);
	myListInts.insert(myListInts.end(), 77);
	myListInts.insert(myListInts.end(), 135);
	myListInts.insert(myListInts.end(), 5);


	// Will return an iterator either:
	// - pointing to the thing it found
	// - pointing to the .end() location
	std::list<int>::iterator it135 = std::find(myListInts.begin(), myListInts.end(), 135);

	it135++;
	it135--;
	std::advance(it135, 4);
//	it135 += 4;

	if (it135 != myListInts.end())
	{
		// found it!
		myListInts.insert(it135, 99);
	}
	if (it135 == myListInts.end())
	{
		// DIDN'T find it
		std::cout << "Didn't find the number" << std::endl;
	}


	for (std::list<int>::iterator it = myListInts.begin();
		it != myListInts.end();
		it++)
	{
		std::cout << *it << std::endl;
	}





	// We'd like to store out monsters by full name
	// pMonster->name = pMonster->firstName + " " + pMonster->lastName;

	cMonsterCreator* MC = new cMonsterCreator();
	MC->LoadNamesDefault();

	//std::map< unsigned int, cMonster* > mapLikeAVector;
	//for (unsigned int index = 0; index != 10; index++)
	//{
	//	mapLikeAVector[index] = MC->CreateMonster();
	//}
	//mapLikeAVector[3]->

	std::map<std::string, cMonster*> map_pMonstersByName;

	cMonster* pM1 = MC->CreateMonster();
	map_pMonstersByName[pM1->name] = pM1;

	for (unsigned int index = 0; index != 10; index++)
	{
		cMonster* pNewMonster = MC->CreateMonster();
		map_pMonstersByName[pNewMonster->name] = pNewMonster;
	}

	// Get this monster 
	cMonster* pLB = map_pMonstersByName["LORENA BANGS"];
//	cMonster* pLB = map_pMonstersByName["MICHAEL FEENEY"];
	std::cout << pLB->age << std::endl;


//	cMonster* pLB = map_pMonstersByName["MICHAEL FEENEY"];
	std::map<std::string, cMonster*>::iterator itMF
		= map_pMonstersByName.find("MICHAEL FEENEY");
	// found it? 
	if (itMF != map_pMonstersByName.end())
	{
		// DID find it
		cMonster* pMF = itMF->second;
		std::cout << pMF->name << std::endl;
	}
	itMF++;
//	itMF += 5;	// Not OK
	std::advance(itMF, 4);

	for (std::map<std::string, cMonster*>::iterator itMon = map_pMonstersByName.begin();
		itMon != map_pMonstersByName.end();
		itMon++)
	{
		cMonster* pMF = itMF->second;
		std::cout << pMF->name << std::endl;
	}


	// Log() search speed    O(log) or O(ln)
	// CPU bound (memory access was zero)
	// memory bound (CPU is nothing)
	// 
	// Each doubling is one more search
	// 2 -> 1 
	// 4 -> 2
	// 8 -> 3
	// 16 -> 4
	// 32 -> 5
	// 64 -> 6
	// 128 -> 7		as opposed to 128
	// 256 -> 8     
	// 4 billion --> 32 searches   (125 million times faster)


	std::map<unsigned int /*SN*/, cMonster*> map_pMonstersBySN;

//	map_pMonstersBySN[173883] = MC->CreateMonster();











	std::vector<cMonster> vecMonsters_A;
	// Add some monsters
	vecMonsters_A.push_back(cMonster());
	vecMonsters_A.push_back(cMonster());
	// .. and so on

//	std::sort(vecMonsters_A.begin(), vecMonsters_A.end());
	std::sort(vecMonsters_A.begin(), vecMonsters_A.end(), compareByAgeLessThan);


	//cMonster bob;
	//cMonster sally;
	//if ( bob < sally )


	std::vector<cMonster> vecMonsters_copy;

//	vecMonsters_copy = vecMonsters_A;
	//for (int index = 0; index != vecMonsters_A.size(); index++)
	//{
	//	vecMonsters_copy[index] = vecMonsters_A[index];
	//}
	for (int index = 0; index != vecMonsters_A.size(); index++)
	{
		vecMonsters_copy.push_back( vecMonsters_A[index] );
	}

	// This will only work if the "copy" vector
	// ALREADY has enough space for the original
//	std::copy(vecMonsters_A.begin(),
//	          vecMonsters_A.end(),
//	          vecMonsters_copy.begin());

	// You need to use a "back inserter" for vector
	// 
	std::copy(vecMonsters_A.begin(),
	          vecMonsters_A.end(),
			  std::back_inserter(vecMonsters_copy));



	return 0;
}





void OldCodeMain()
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
//		return 1;
	}

	// Assume that the monster loader has loaded the files OK.

	// On the stack (stack based variable)
	// Returning by copying on the stack
	cMonster* pMonster_01 = pMC->CreateMonster();
	cMonster* pMonster_02 = pMC->CreateMonster();

//	cMonster myMonster;
//	pMC->CreateMonster(myMonster);
//
//	cMonster Ted = pMC->CreateMonster();

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
	//	std::vector<int> myVec = { -1, 3, 6, 2, 4, 7, 2, 16, -9, 99 };

	std::vector<int>::iterator myIterator = myVec.begin();
	//myIterator++;
	//myIterator++;
	//myIterator += 4;
	//myIterator--;
	//myVec.erase(myIterator);

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

//	return 0;
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