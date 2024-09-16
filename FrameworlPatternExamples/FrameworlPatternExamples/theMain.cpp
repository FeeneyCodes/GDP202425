#include <iostream>
#include <string>

#include "cMonster.h"

// argc : How many parameters were passed. 
//        (at leat 1 always)
// argv : Is a 1D array of string of what was passed.
//        Separated by 'whitespace' (space, tab, etc.)
//        C has no strings, and a string is a char* 
//        It's really a 2D array of char
//         char** argv;
int main( int argc, char* argv[] )
{
	std::cout << "argc = " << argc << std::endl;

	for (unsigned int index = 0; index != argc; index++)
	{
//		std::cout << index << " : " << argv[index] << std::endl;
	}

//	system("pause");

	std::cout << "Hey..." << std::endl;
	{
//		cMonster monster;  // Stack variable (no "new")
		cMonster* pMonster = new cMonster();		// HEAP

//		cMonster* pMosnter = (cMonster*)malloc((size_t)sizeof(cHuman));

		std::cout << "the air show was fun." << std::endl;
		
		delete pMonster;
//		free(pMosnter);
	}
	std::cout << "you." << std::endl;

	//cMonster Fred;
	//cMonster Mary = Fred;
	//cMonster Sally(Fred);

	return 0;
}