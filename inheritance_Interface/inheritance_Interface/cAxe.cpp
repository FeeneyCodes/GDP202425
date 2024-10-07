#include "cAxe.h"
#include <iostream>

void cAxe::Chop(void)
{
	if (this->bIsBattleAxe)
	{
		std::cout << "The "
			<< this->type << " BATTLE AXE "
			<< "comes down with force "
			<< this->size << std::endl;
	}
	else
	{
		std::cout << "The "
			<< this->type << " axe "
			<< "comes down with force "
			<< this->size << std::endl;
	}

	return;
}

cAxe::cAxe()
{
	std::cout << "cAxe::cAxe()" << std::endl;
}

cAxe::~cAxe()
{
	std::cout << "cAxe::~cAxe()" << std::endl;
}
