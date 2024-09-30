#include <iostream>
#include "cMonster.h"


int main(int argc, char* argv[])
{

	cMonster Bob("bob");
	cMonster* pSally = new cMonster("sally");


	Bob.KillAllHumans();



	delete pSally;

	return 0;
}
