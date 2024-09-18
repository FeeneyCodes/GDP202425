#include <iostream>
#include <string>

#include "cMonster.h"
#include "cMonsterCreator.h"



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
	cMonster Monster_01 = pMC->CreateMonster();

	Monster_01.PrintStats();

	// What do I do with this monster?? 
	std::vector<cMonster> vecTheMonsters;
	vecTheMonsters.push_back(Monster_01);

	Monster_01.health = 50.0f;

	vecTheMonsters[0].PrintStats();




	// TODO:
//	pMC->CreateMonster();

	//std::vector<int> myVector;
	//int x = myVector.size();
	//std::size_t y = myVector.size();
	////     typedef unsigned __int64 size_t;


	delete pMC;

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