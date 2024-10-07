#include "cSword.h"
#include <iostream>

float size;
std::string colour;
void cSword::Swing(void)
{
	std::cout << "The "
		<< this->colour << " sword "
		<< "woshes though the air causing "
		<< this->size << " damage!" << std::endl;
	return;
}

cSword::cSword()
{
	std::cout << "cSword::cSword()" << std::endl;
}

cSword::~cSword()
{
	std::cout << "cSword::~cSword()" << std::endl;
}

